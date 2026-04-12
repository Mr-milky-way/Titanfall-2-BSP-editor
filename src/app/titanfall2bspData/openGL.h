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

#include "structs.h"
#include "helperfunctions.h"

extern BSPFILE mainBSP;
extern SettingsStruct settings;

#ifndef OPENGL_H
#define OPENGL_H


class BSPVisualizer : public QOpenGLWidget, protected QOpenGLFunctions {
    QOpenGLBuffer vbo{ QOpenGLBuffer::VertexBuffer };
    QOpenGLBuffer ibo{ QOpenGLBuffer::IndexBuffer };
    int indexCount = 0;
    int vertexCount = 0;


    float rotationX = -90.0f;
    float rotationY = 0.0f;
    float zoom = -5000.0f;
    QPoint lastMousePos;

public:
    BSPVisualizer(QWidget* parent = nullptr) : QOpenGLWidget(parent) {}


    struct RenderVertex {
        float x, y, z;
        float nx, ny, nz;
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


        uint32_t startLitFlat = 0;
        uint32_t startUnlit = 0;
        uint32_t startLitBump = 0;
        uint32_t startUnlitTS = 0;

        if (settings.renderLitFlat) {
            startLitFlat = renderPool.size();
            for (const auto& vtx : mainBSP.VertexLitFlat) {
                renderPool.push_back({
                    mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
                    mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z
                    });
            }
        }
        if (settings.renderUnlit) {
            startUnlit = renderPool.size();
            for (const auto& vtx : mainBSP.VertexUnlit) {
                renderPool.push_back({
                    mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
                    mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z
                    });
            }
        }

        if (settings.renderLitBump) {
            startLitBump = renderPool.size();
            for (const auto& vtx : mainBSP.VertexLitBump) {
                renderPool.push_back({
                    mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
                    mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z
                    });
            }
        }
        if (settings.renderUnlitTS) {
            startUnlitTS = renderPool.size();
            for (const auto& vtx : mainBSP.VertexUnlitTS) {
                renderPool.push_back({
                    mainBSP.vertices[vtx.position_index].vertex.x, mainBSP.vertices[vtx.position_index].vertex.y, mainBSP.vertices[vtx.position_index].vertex.z,
                    mainBSP.vertex_normals[vtx.normal_index].normal.x, mainBSP.vertex_normals[vtx.normal_index].normal.y, mainBSP.vertex_normals[vtx.normal_index].normal.z
                    });
            }
        }

        vbo.bind();
        vbo.allocate(renderPool.data(), (int)(renderPool.size() * sizeof(RenderVertex)));
        vbo.release();

        
        std::vector<unsigned int> validatedIndices;
        for (const auto& tfMesh : mainBSP.Meshes) {

            unsigned int triOffset = mainBSP.MaterialSorts[tfMesh.material_sort].vertex_offset;

            // Apply block offsets based on flags
            uint32_t f = (uint32_t)tfMesh.flags;
            if (f & (uint32_t)TextureDataFlags::VERTEX_UNLIT && settings.renderLitFlat == true) {
                triOffset += mainBSP.VertexLitFlat.size();
            }  
            if (f & (uint32_t)TextureDataFlags::VERTEX_LIT_BUMP && settings.renderUnlit == true) {
                triOffset += (mainBSP.VertexLitFlat.size() + mainBSP.VertexUnlit.size());
            }
            if (f & (uint32_t)TextureDataFlags::VERTEX_UNLIT_TS && settings.renderUnlitTS == true) {
                triOffset += (mainBSP.VertexLitFlat.size() + mainBSP.VertexUnlit.size() + mainBSP.VertexLitBump.size());
            }

            for (uint32_t i = 0; i < (uint32_t)tfMesh.num_triangles * 3; i++) {
                if (tfMesh.first_mesh_index + i < mainBSP.MeshIndices.size()) {
                    unsigned int rawIdx = mainBSP.MeshIndices[tfMesh.first_mesh_index + i].Indices;
                    unsigned int finalIdx = rawIdx + triOffset;
                    if (finalIdx < renderPool.size()) {
                        validatedIndices.push_back(finalIdx);
                    }
                    else {
                        qDebug() << "Invalid finalIdx" << finalIdx << "vs pool" << renderPool.size();
                    }
                }
                else {
                    qDebug() << "Invalid mesh index" << (tfMesh.first_mesh_index + i);
                }
            }
        }

        ibo.bind();
        ibo.allocate(validatedIndices.data(), (int)(validatedIndices.size() * sizeof(unsigned int)));
        indexCount = (int)validatedIndices.size();
        ibo.release();

        doneCurrent();
        update();
    }

protected:

    void mousePressEvent(QMouseEvent* event) override {
        lastMousePos = event->pos();
    }


    void mouseMoveEvent(QMouseEvent* event) override {
        int dx = event->x() - lastMousePos.x();
        int dy = event->y() - lastMousePos.y();

        if (event->buttons() & Qt::LeftButton) {
            rotationX += dy * 0.5f;
            rotationY += dx * 0.5f;
            update();
        }
        lastMousePos = event->pos();
    }


    void wheelEvent(QWheelEvent* event) override {
        float delta = event->angleDelta().y();
        zoom += delta * 5.0f;
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

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, zoom);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 0, 1);

        vbo.bind();
        ibo.bind();

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(RenderVertex), (void*)0);

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(RenderVertex), (void*)(3 * sizeof(float)));

        
        glColor3f(0.6f, 0.6f, 0.6f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

        
        glColor3f(0, 0, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

        
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
