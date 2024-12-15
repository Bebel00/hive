#include "mainwindow.h"
#include "partie.h"
#include "graphicspartie.h"

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

    partie.jouer_tour_cli("place abeille 0 0");
    partie.jouer_tour_cli("place abeille 2 0");
    partie.jouer_tour_cli("place sauterelle -2 0");
    partie.jouer_tour_cli("place scarabe 4 0");

    std::cout << partie.jouer_tour_cli("undo") << std::endl;

    return a.exec();
}
