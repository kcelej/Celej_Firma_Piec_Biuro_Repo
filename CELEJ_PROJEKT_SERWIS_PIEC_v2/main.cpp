#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    w.setWindowTitle("Celej Piece");
    w.show();
    
    return a.exec();
}
