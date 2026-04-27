#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QObject>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QWidget>
#include <cmath>
#include <Qt>

#include "structs.h"
#include "helperfunctions.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "VTFLib.h"

extern BSPFILE mainBSP;
extern SettingsStruct settings;
extern filesystem::path WorkingFolder;
extern filesystem::path modelsFolder;



#ifndef OPENGL_H
#define OPENGL_H

struct MeshDraw { // might be able to swap to the raw Mesh pulled 
	uint32_t indexOffset;
	uint32_t indexCount;
	uint32_t textureID;
};

class BSPVisualizer : public QOpenGLWidget, protected QOpenGLFunctions {

	QOpenGLBuffer vbo{ QOpenGLBuffer::VertexBuffer };
	QOpenGLBuffer ibo{ QOpenGLBuffer::IndexBuffer };
	int indexCount = 0;
	int vertexCount = 0;

	float zoom = -5000.0f;
	QPoint lastMousePos;


	QVector3D cameraPos = QVector3D(0.0f, 0.0f, 5000.0f);
	QVector3D cameraFront = QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D cameraUp = QVector3D(0.0f, 0.0f, 1.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float movementSpeed = 50.0f;
	float mouseSensitivity = 0.2f;

	unsigned int texture;

	std::vector<MeshDraw> meshes;

public:
	BSPVisualizer(QWidget* parent = nullptr) : QOpenGLWidget(parent) {
		setFocusPolicy(Qt::StrongFocus);
	}



	struct RenderVertex {
		float x, y, z;
		float nx, ny, nz;
		float u, v;
	};

	void uploadBSPData() {
		makeCurrent();

		if (!context() || !QOpenGLContext::currentContext()) {
			doneCurrent();
			return;
		}

		if (!vbo.isCreated()) vbo.create();
		if (!ibo.isCreated()) ibo.create();

		std::vector<RenderVertex> renderPool;

		meshes.clear();
		uint32_t startLitFlat = UINT32_MAX;
		uint32_t startUnlit = UINT32_MAX;
		uint32_t startLitBump = UINT32_MAX;
		uint32_t startUnlitTS = UINT32_MAX;

		if (settings.renderLitFlat) {
			startLitFlat = renderPool.size();
			for (const auto& vtx : mainBSP.VertexLitFlat) {
				renderPool.push_back({
					mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
					mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z,
					vtx.albedo_uv.x, vtx.albedo_uv.y
					});
			}
		}
		if (settings.renderUnlit) {
			startUnlit = renderPool.size();
			for (const auto& vtx : mainBSP.VertexUnlit) {
				renderPool.push_back({
					mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
					mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z,
					vtx.albedo_uv.x, vtx.albedo_uv.y
					});
			}
		}

		if (settings.renderLitBump) {
			startLitBump = renderPool.size();
			for (const auto& vtx : mainBSP.VertexLitBump) {
				renderPool.push_back({
					mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
					mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z,
					vtx.albedo_uv.x, vtx.albedo_uv.y
					});
			}
		}
		if (settings.renderUnlitTS) {
			startUnlitTS = renderPool.size();
			for (const auto& vtx : mainBSP.VertexUnlitTS) {
				renderPool.push_back({
					mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
					mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z,
					vtx.albedo_uv.x, vtx.albedo_uv.y
					});
			}
		}

		vbo.bind();
		vbo.allocate(renderPool.data(), (int)(renderPool.size() * sizeof(RenderVertex)));
		vbo.release();

		std::vector<unsigned int> validatedIndices;



		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char* data = stbi_load("resources/missing_texture.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);


		std::vector<GLuint> materialTextures;

		materialTextures.resize(mainBSP.texture_data.size());


		if (vlInitialize()) {
			VTFLib::CVTFFile vtfFile;

			if (filesystem::exists(modelsFolder)) {
			for (size_t i = 0; i < materialTextures.size(); i++) {
				std::string matLower = mainBSP.TextureDataStringData[0].strings[i];
				std::transform(matLower.begin(), matLower.end(), matLower.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::filesystem::path temp = modelsFolder / matLower;
				temp += "_col.png";

				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				unsigned char* data = stbi_load(temp.string().c_str(), &width, &height, &nrChannels, 0);
				if (data)
				{
					GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

					glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
					glGenerateMipmap(GL_TEXTURE_2D);
					materialTextures[i] = tex;
				}
				else
				{
					std::cout << "Failed to load texture: " << temp.string() << std::endl;
				}
				stbi_image_free(data);

			}
			}
			else {
				for (size_t i = 0; i < materialTextures.size(); i++) {
					vlByte tempColor[4] = {
						static_cast<vlByte>((i * 70) % 256),
						static_cast<vlByte>((i * 140) % 256),
						static_cast<vlByte>((i * 210) % 256),
						255
					};

					const vlUInt width = 64;
					const vlUInt height = 64;

					std::vector<vlByte> dst(width * height * 4);

					for (size_t p = 0; p < dst.size(); p += 4) {
						dst[p + 0] = tempColor[0];
						dst[p + 1] = tempColor[1];
						dst[p + 2] = tempColor[2];
						dst[p + 3] = tempColor[3];
					}

					GLuint tex;
					glGenTextures(1, &tex);
					glBindTexture(GL_TEXTURE_2D, tex);

					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
						0, GL_RGBA, GL_UNSIGNED_BYTE, dst.data());

					glGenerateMipmap(GL_TEXTURE_2D);

					materialTextures[i] = tex;

					const auto& mat = mainBSP.TextureDataStringData[0].strings[i];
					std::cout << "Using temp texture for: " << mat << std::endl;
				}
			}


			/*
			//For VTF
			for (size_t i = 0; i < materialTextures.size(); i++) {
				const auto& mat = mainBSP.TextureDataStringData[0].strings[i];
				std::filesystem::path temp = modelsFolder / mat;
				temp += ".vtf";
				if (vtfFile.Load(temp.string().c_str())) {
					vlUInt width = vtfFile.GetWidth();
					vlUInt height = vtfFile.GetHeight();

					vlByte* src = vtfFile.GetData(0, 0, 0, 0);
					std::vector<vlByte> dst(width * height * 4);

					vlImageConvert(src, dst.data(), width, height,
						vtfFile.GetFormat(), IMAGE_FORMAT_RGBA8888);

					GLuint tex;
					glGenTextures(1, &tex);
					glBindTexture(GL_TEXTURE_2D, tex);

					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
						0, GL_RGBA, GL_UNSIGNED_BYTE, dst.data());

					glGenerateMipmap(GL_TEXTURE_2D);

					materialTextures[i] = tex;
				} else {
					std::cout << "Failed to load texture:" << temp.string().c_str() << std::endl;
					materialTextures[i] = 0;
				}
			}*/
			vlShutdown();
		}

		for (const auto& mesh : mainBSP.Meshes) {

			if (mesh.material_sort >= mainBSP.MaterialSorts.size())
				continue;

			uint32_t startIndex = validatedIndices.size();

			uint32_t materialOffset =
				mainBSP.MaterialSorts[mesh.material_sort].vertex_offset;

			uint32_t typeOffset = UINT32_MAX;

			switch (mesh.vertex_type) {
			case 0: typeOffset = startLitFlat; break;
			case 1: typeOffset = startUnlit; break;
			case 2: typeOffset = startLitBump; break;
			case 3: typeOffset = startUnlitTS; break;
			default: continue;
			}

			if (typeOffset == UINT32_MAX)
				continue;

			uint32_t base = materialOffset + typeOffset;

			for (uint32_t i = 0; i < mesh.num_triangles * 3; i++) {

				uint32_t idx = mesh.first_mesh_index + i;

				if (idx >= mainBSP.MeshIndices.size())
					continue;

				uint16_t raw = mainBSP.MeshIndices[idx].Indices;
				uint32_t finalIdx = raw + base;

				if (finalIdx >= renderPool.size())
					continue;

				validatedIndices.push_back(finalIdx);
			}

			MeshDraw draw;
			draw.indexOffset = startIndex;
			draw.indexCount = mesh.num_triangles * 3;
			if (mesh.material_sort < mainBSP.texture_data.size()) {
				draw.textureID = materialTextures[mesh.material_sort];
			} else {
				cout << mesh.material_sort << endl;
				draw.textureID = texture;
			}
			

			meshes.push_back(draw);
		}
		for (const auto& mesh : mainBSP.TextureDataStringTable) {
			cout << mesh.something << endl;
		}

		ibo.bind();
		ibo.allocate(validatedIndices.data(), (int)(validatedIndices.size() * sizeof(unsigned int)));
		indexCount = (int)validatedIndices.size();
		ibo.release();

		doneCurrent();
		update();
	}

protected:

	void keyPressEvent(QKeyEvent* event) override {
		float velocity = movementSpeed;

		QVector3D right = QVector3D::crossProduct(cameraFront, cameraUp).normalized();

		if (event->key() == Qt::Key_W)
			cameraPos += velocity * cameraFront;
		if (event->key() == Qt::Key_S)
			cameraPos -= velocity * cameraFront;
		if (event->key() == Qt::Key_A)
			cameraPos -= right * velocity;
		if (event->key() == Qt::Key_D)
			cameraPos += right * velocity;
		if (event->key() == Qt::Key_Q)
			cameraPos -= cameraUp * velocity;
		if (event->key() == Qt::Key_E)
			cameraPos += cameraUp * velocity;

		update();
	}

	void mousePressEvent(QMouseEvent* event) override {
		lastMousePos = event->pos();
	}


	void mouseMoveEvent(QMouseEvent* event) override {
		float dx = event->x() - lastMousePos.x();
		float dy = lastMousePos.y() - event->y();

		lastMousePos = event->pos();

		dx *= mouseSensitivity;
		dy *= mouseSensitivity;

		yaw -= dx;
		pitch += dy;

		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;

		QVector3D front;
		front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
		front.setY(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
		front.setZ(sin(qDegreesToRadians(pitch)));
		cameraFront = front.normalized();

		update();
	}


	void wheelEvent(QWheelEvent* event) override {
		float delta = event->angleDelta().y();
		movementSpeed += delta * 0.1f;

		if (movementSpeed < 1.0f) movementSpeed = 1.0f;
		if (movementSpeed > 1000.0f) movementSpeed = 1000.0f;

		update();
	}

	void initializeGL() override {
		initializeOpenGLFunctions();
		glClearColor(0.05f, 0.05f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		//QTimer* timer = new QTimer(this);
		//connect(timer, &QTimer::timeout, this, QOverload<>::of(&BSPVisualizer::update));
		//timer->start(16); // ~60 FPS
	}

	void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float aspect = (float)width() / height();
		glFrustum(-aspect, aspect, -1.0f, 1.0f, 1.0f, 100000.0f);


		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-1.0f, -1.0f);

		QMatrix4x4 view;
		view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(view.constData());

		vbo.bind();
		ibo.bind();

		glEnable(GL_TEXTURE_2D);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(RenderVertex), (void*)(6 * sizeof(float)));

		glEnable(GL_MULTISAMPLE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(RenderVertex), (void*)0);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(RenderVertex), (void*)(3 * sizeof(float)));


		for (const auto& mesh : meshes) {
			glColor3f(0.6f, 0.6f, 0.6f);
			glBindTexture(GL_TEXTURE_2D, mesh.textureID);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void*)(mesh.indexOffset * sizeof(unsigned int)));

			glColor3f(0, 0, 0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void*)(mesh.indexOffset * sizeof(unsigned int)));
		}

		/*glColor3f(0.6f, 0.6f, 0.6f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);


		glColor3f(0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);*/


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		ibo.release();
		vbo.release();
	}

	void resizeGL(int w, int h) override {
		glViewport(0, 0, w, h);
	}
};
#endif