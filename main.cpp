#include "mainwindow.h"
#include "menu.h"
#include "partie.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainMenu menu;

    MainWindow w;
    Partie* partie = nullptr;

     QObject::connect(&menu, &MainMenu::nouvellePartieDemandee, [&w](QString joueur1, QString joueur2, bool contreIA) {
        w.demarrerNouvellePartie(joueur1, joueur2);
    });

    // connecte le menu pour quitter l'application
    QObject::connect(&menu, &MainMenu::quitApplication, &a, &QApplication::quit);

    // affiche le menu principal
    menu.show();

    return a.exec();
}
  
