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

  QObject::connect(&menu, &MainMenu::nouvellePartieDemandee, [&]() {
      QString joueur1 = QInputDialog::getText(nullptr, "Joueur 1", "Entrez le nom du joueur 1 :");
      QString joueur2 = QInputDialog::getText(nullptr, "Joueur 2", "Entrez le nom du joueur 2 :");
       
      if (joueur1.isEmpty() || joueur2.isEmpty()) {
            QMessageBox::warning(nullptr, "Erreur", "Les noms des joueurs ne peuvent pas être vides !");
            return; 
        }

      
        if (partie) {
            delete partie;
            partie = nullptr;
        }

  
        partie = new Partie(joueur1.toStdString(), joueur2.toStdString());
        w.setPartie(partie);


    
        menu.hide();
        w.show();
    });

   
    QObject::connect(&menu, &MainMenu::quitApplication, [&]() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Quitter", "Êtes-vous sûr de vouloir quitter ?",
                                       QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            a.quit();
        }
    });

    QObject::connect(&w, &MainWindow::menuFerme, [&]() {
        if (partie) {
            delete partie;
            partie = nullptr;
        }
        w.hide();
        menu.show();
    });

   
    QObject::connect(&w, &MainWindow::nouvellePartieDemandee, [&]() {
        if (partie) {
            delete partie;
            partie = nullptr;
        }

       
        QString joueur1 = QInputDialog::getText(nullptr, "Joueur 1", "Entrez le nom du joueur 1 :");
        QString joueur2 = QInputDialog::getText(nullptr, "Joueur 2", "Entrez le nom du joueur 2 :");
        if (joueur1.isEmpty() || joueur2.isEmpty()) {
            QMessageBox::warning(nullptr, "Erreur", "Les noms des joueurs ne peuvent pas être vides !");
            return; 
        }
        partie = new Partie(joueur1.toStdString(), joueur2.toStdString());
        w.setPartie(partie);

        // Rester dans la fenêtre principale
    });

    // Lancer le menu principal
    menu.show();
    return a.exec();
}
    // Boucle CLI pour tester les commandes (désactivée en mode GUI)
    /*
    while (partie) {
        std::string cmd;
        std::getline(std::cin, cmd);
        std::cout << partie->jouer_tour_cli(cmd) << std::endl;
    }
    */



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
