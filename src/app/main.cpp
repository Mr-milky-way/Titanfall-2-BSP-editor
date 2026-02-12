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

    QApplication app(argc, argv);

    QAction *OpenAct;
    OpenAct = new QAction(
                         QObject::tr("&Open"));
    OpenAct->setShortcuts(QKeySequence::Open);
    OpenAct->setStatusTip(QObject::tr("Open a file"));

    QWidget window;

    //make top file thingy
    QMenuBar *menuBar = new QMenuBar(&window);
    QMenu *fileMenu;
    fileMenu = menuBar->addMenu(QObject::tr("&File"));
    fileMenu->addAction(OpenAct);

    window.show();
    return app.exec();
}