#include "mainwindow.h"
#include "partie.h"
#include "plateau.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout<<"a";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Partie partie("Bebel", "Léo",6);
    w.setPartie(&partie);

    return a.exec();
}
