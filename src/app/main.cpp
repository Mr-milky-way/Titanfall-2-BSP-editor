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

#include "titanfall2bspData/structs.h"
#include "titanfall2bspData/helperfunctions.h"

using namespace std;

BSPFILE mainBSP;

void createOBJfile(BSPFILE bsp)
{
    ofstream file("test.obj");

    for (const auto &v : bsp.vertices)
    {
        file << "v " << v.vertex.x << " " << v.vertex.y << " " << v.vertex.z << endl;
    }

    for (int i = 0; i < bsp.models.size(); i++)
    {
        Models &model = bsp.models[i];

        file << "g model" << i << endl;

        for (int m = model.first_mesh; m < model.first_mesh + model.num_meshes; m++)
        {
            Mesh &mesh = bsp.Meshes[m];

            int e = 0;
            switch ((int)mesh.vertex_type)
            {
            case 0:
                // cout << "new VertexUnlit" << endl;
                /*
                for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                {
                    int idx0 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                    int idx1 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                    int idx2 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                    file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                }*/
                // also some sort of boxes
                break;
            case 1:
                /*
                    cout << "new VertexLitFlat" << endl;
                    for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                    {
                        int idx0 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                        int idx1 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                        int idx2 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                        file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                    }*/
                break;
            case 2:
                // seems to have most map data
                cout << "new VertexLitBump" << endl;
                cout << mesh.num_triangles << endl
                     << mesh.num_vertices << endl;
                for (int t = 0; t < (int)mesh.num_triangles * 3; t += 3)
                {

                    int idx0 = bsp.VertexLitBump[(int)bsp.MeshIndices[(int)mesh.first_mesh_index + t].Indices].position_index + 1;
                    int idx1 = bsp.VertexLitBump[(int)bsp.MeshIndices[(int)mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                    int idx2 = bsp.VertexLitBump[(int)bsp.MeshIndices[(int)mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                    file << "f " << idx2 << " " << idx1 << " " << idx0 << endl;
                }
                break;
            case 3:
                // skyboxes?
                // VertexUnlitTS
                break;
            case 4:
                /*
                    cout << "new VertexBlinnPhong" << endl;
                    for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                    {
                        int idx0 = bsp.VertexBlinnPhong[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                        int idx1 = bsp.VertexBlinnPhong[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                        int idx2 = bsp.VertexBlinnPhong[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                        file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                    }*/
                break;
            default:
                break;
            }
        }
    }

    file.close();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    
    QMainWindow window;
    window.setWindowTitle("BSP Viewer");
    window.resize(800, 600);

    
    QAction *openAct = new QAction(QObject::tr("&Open"), &window);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(QObject::tr("Open a file"));

    
    QMenu *fileMenu = window.menuBar()->addMenu(QObject::tr("&File"));
    fileMenu->addAction(openAct);

    QObject::connect(openAct, &QAction::triggered, [&window]()
                     {
    
    QString fileName = QFileDialog::getOpenFileName(
        &window,
        QObject::tr("Open BSP File"),
        "",
        QObject::tr("BSP Files (*.bsp);;All Files (*)")
    );


    if (!fileName.isEmpty()) {
        string stdFileName = fileName.toStdString();
        
        mainBSP = readFullBSP(stdFileName);
        createOBJfile(mainBSP);
        
        qDebug() << "Loaded new file:" << fileName;
    } });

    window.show();
    return app.exec();
}