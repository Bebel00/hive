#include "mainwindow.h"
#include "partie.h"
#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // w.show();

    Partie partie("Bebel", "Léo");
    w.setPartie(&partie);

    while (true)
    {
        std::string cmd;
        std::getline(std::cin, cmd);
        std::cout << partie.jouer_tour_cli(cmd) << std::endl;
    }

    return a.exec();
}
