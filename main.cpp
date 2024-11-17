#include "mainwindow.h"
#include "mainmenu.h"
#include "partie.h"
#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainMenu menu;

    MainWindow w;
    Partie* partie = nullptr;

    // Connexion pour lancer une nouvelle partie depuis le menu
    QObject::connect(&menu, &MainMenu::nouvellePartieDemandee, [&]() {
        // Création d'une nouvelle partie si celle ci est nécessaire
        if (!partie) {
            partie = new Partie("Leo", "Abel"); 
            w.setPartie(partie);
        }

        //pour cacher le menu et afficher la fenêtre principale
        menu.hide();
        w.show();
    });

    // connexion pour quitter l'application depuis le menu
    QObject::connect(&menu, &MainMenu::quitApplication, [&]() {
        a.quit();
    });

    // pour lancer  le menu principal
    menu.show();

   
    while (partie) {
        std::string cmd;
        std::getline(std::cin, cmd);
        std::cout << partie->jouer_tour_cli(cmd) << std::endl;
    }

    return a.exec();
}
