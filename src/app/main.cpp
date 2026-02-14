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

        for (int m = model.first_mesh; m < model.first_mesh + model.num_meshes; m++)
        {
            Mesh &mesh = bsp.Meshes[m];

            switch ((int)mesh.vertex_type)
            {
            case 0:
                for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                {
                    int idx0 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                    int idx1 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                    int idx2 = bsp.VertexUnlit[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                    file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                }
                break;
            case 1:
                for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                {
                    int idx0 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                    int idx1 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                    int idx2 = bsp.VertexLitFlat[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                    file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                }
                break;
            case 2:
                for (int t = 0; t < mesh.num_triangles * 3; t += 3)
                {
                    int idx0 = bsp.VertexLitBump[bsp.MeshIndices[mesh.first_mesh_index + t].Indices].position_index + 1;
                    int idx1 = bsp.VertexLitBump[bsp.MeshIndices[mesh.first_mesh_index + t + 1].Indices].position_index + 1;
                    int idx2 = bsp.VertexLitBump[bsp.MeshIndices[mesh.first_mesh_index + t + 2].Indices].position_index + 1;

                    file << "f " << idx0 << " " << idx1 << " " << idx2 << endl;
                }
                break;
            case 3:
                //skyboxes?
                //VertexUnlitTS
                break;
            case 4:
                break;
            default:
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    string filename;
    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        cout << "Please provide a filename as an argument." << endl;
        return 1;
    }

    mainBSP = readFullBSP(filename);
    createOBJfile(mainBSP);

    QApplication app(argc, argv);

    QAction *OpenAct;
    OpenAct = new QAction(
        QObject::tr("&Open"));
    OpenAct->setShortcuts(QKeySequence::Open);
    OpenAct->setStatusTip(QObject::tr("Open a file"));

    QWidget window;

    // make top file thingy
    QMenuBar *menuBar = new QMenuBar(&window);
    QMenu *fileMenu;
    fileMenu = menuBar->addMenu(QObject::tr("&File"));
    fileMenu->addAction(OpenAct);

    window.show();
    return app.exec();
}