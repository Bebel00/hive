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

//QObject::connect(&menu, &MainMenu::quitApplication, [&]() {
        // Afficher une boîte de dialogue de confirmation avant de quitter
        //QMessageBox::StandardButton reply;
        //reply = QMessageBox::question(nullptr, "Quitter", "Êtes-vous sûr de vouloir quitter?",
          //                            QMessageBox::Yes | QMessageBox::No);
        //if (reply == QMessageBox::Yes) {
          //  app.quit();
        //}
    //});

    // Connexion pour réinitialiser la fenêtre de jeu et recommencer une nouvelle partie
    //QObject::connect(&w, &MainWindow::nouvellePartieDemandee, [&]() {
        // Supprimer l'ancienne partie si elle existe
       // delete partie;
        //partie = nullptr; // Réinitialiser la partie
       // menu.show();  // Afficher de nouveau le menu principal
       //w.hide();     // Cacher la fenêtre de jeu
 //   });//*
