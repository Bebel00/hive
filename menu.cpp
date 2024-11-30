#include "mainmenu.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>

MainMenu::MainMenu(QWidget* parent) : QGraphicsView(parent) {
    mainMenuScene = new QGraphicsScene(this);
    newGameScene = new QGraphicsScene(this);

    setupMainMenu();
    setupNewGameScene();

    setScene(mainMenuScene);
}

void MainMenu::setupMainMenu() {
    // Ajouter le titre
    QGraphicsTextItem* title = new QGraphicsTextItem("Menu Principal");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    mainMenuScene->addItem(title);

    // Bouton Nouvelle Partie
    QPushButton* newGameButton = new QPushButton("Nouvelle Partie");
    QGraphicsProxyWidget* newGameButtonProxy = mainMenuScene->addWidget(newGameButton);
    newGameButtonProxy->setPos(100, 150);

    // Bouton Quitter
    QPushButton* quitButton = new QPushButton("Quitter");
    QGraphicsProxyWidget* quitButtonProxy = mainMenuScene->addWidget(quitButton);
    quitButtonProxy->setPos(100, 200);

    // Connexions pour les boutons
    connect(newGameButton, &QPushButton::clicked, this, &MainMenu::goToNewGame);
    connect(quitButton, &QPushButton::clicked, this, &MainMenu::quitApplication);
}

void MainMenu::setupNewGameScene() {
    // Ajouter le titre de la scène de nouvelle partie
    QGraphicsTextItem* newGameTitle = new QGraphicsTextItem("Nouvelle Partie");
    newGameTitle->setFont(QFont("Arial", 24));
    newGameTitle->setPos(100, 50);
    newGameScene->addItem(newGameTitle);

    // Bouton Retour
    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = newGameScene->addWidget(backButton);
    backButtonProxy->setPos(100, 150);

    // Connexion pour revenir au menu principal
    connect(backButton, &QPushButton::clicked, [=]() {
        setScene(mainMenuScene);
    });
}

void MainMenu::goToNewGame() {
    emit nouvellePartieDemandee(); // Émet un signal pour démarrer une nouvelle partie
}

void MainMenu::quitApplication() {
    emit applicationQuitRequested(); // Émet un signal pour quitter l'application
}
