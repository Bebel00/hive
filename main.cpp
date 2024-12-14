#include "mainwindow.h"
#include "partie.h"

#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Partie partie("Bebel", "Léo");
    w.setPartie(&partie);

    return a.exec();
}
