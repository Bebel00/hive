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
    
    QGraphicsTextItem* title = new QGraphicsTextItem("Menu Principal");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    mainMenuScene->addItem(title);

 
    QPushButton* newGameButton = new QPushButton("Nouvelle Partie");
    QGraphicsProxyWidget* newGameButtonProxy = mainMenuScene->addWidget(newGameButton);
    newGameButtonProxy->setPos(100, 150);


    QPushButton* quitButton = new QPushButton("Quitter");
    QGraphicsProxyWidget* quitButtonProxy = mainMenuScene->addWidget(quitButton);
    quitButtonProxy->setPos(100, 200);

 
    connect(newGameButton, &QPushButton::clicked, this, &MainMenu::goToNewGame);
    connect(quitButton, &QPushButton::clicked, this, &MainMenu::quitApplication);
}

void MainMenu::setupNewGameScene() {
    
    QGraphicsTextItem* newGameTitle = new QGraphicsTextItem("Nouvelle Partie");
    newGameTitle->setFont(QFont("Arial", 24));
    newGameTitle->setPos(100, 50);
    newGameScene->addItem(newGameTitle);

   
    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = newGameScene->addWidget(backButton);
    backButtonProxy->setPos(100, 150);

    
    connect(backButton, &QPushButton::clicked, [=]() {
        setScene(mainMenuScene);
    });
}

void MainMenu::goToNewGame() {
    emit nouvellePartieDemandee(); 
}

void MainMenu::quitApplication() {
    emit quitapplication(); 
}
