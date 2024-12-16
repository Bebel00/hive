#include "headers/mainwindow.h"
#include "headers/partie.h"
#include "headers/graphics/graphicspartie.h"

#include <QApplication>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Partie partie("Bebel", "Léo");
    GraphicsPartie graphics(&partie);
    w.setPartie(&graphics);

    return a.exec();
}
