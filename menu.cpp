#include "mainmenu.h"
#include "settings.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QMessageBox>

MainMenu::MainMenu(QWidget* parent) : QGraphicsView(parent) {
    mainMenuScene = new QGraphicsScene(this);
    newGameScene = new QGraphicsScene(this);
    settingsScene = new QGraphicsScene(this);

    settingsWindow = new Settings(this);

    setupMainMenu();
    setupNewGameScene();
    
    setScene(mainMenuScene);
    connect(settingsWindow, &Settings::saveSettings, this, &MainMenu::appliquerSettings);
}

void MainMenu::setupMainMenu() {
    
    QGraphicsTextItem* title = new QGraphicsTextItem("Menu Principal");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    mainMenuScene->addItem(title);

 
    QPushButton* newGameButton = new QPushButton("Nouvelle Partie");
    QGraphicsProxyWidget* newGameButtonProxy = mainMenuScene->addWidget(newGameButton);
    newGameButtonProxy->setPos(100, 150);

    QPushButton* settingsButton = new QPushButton("Paramètres");
    QGraphicsProxyWidget* settingsButtonProxy = mainMenuScene->addWidget(settingsButton);
    settingsButtonProxy->setPos(100, 200);


    QPushButton* quitButton = new QPushButton("Quitter");
    QGraphicsProxyWidget* quitButtonProxy = mainMenuScene->addWidget(quitButton);
    quitButtonProxy->setPos(100, 250);

 
    connect(newGameButton, &QPushButton::clicked, this, &MainMenu::goToNewGame);
    connect(settingsButton, &QPushButton::clicked, this, &MainMenu::goToSettings);
    connect(quitButton, &QPushButton::clicked, this, &MainMenu::quitApplication);
}

void MainMenu::setupNewGameScene() {
    
    QGraphicsTextItem* newGameTitle = new QGraphicsTextItem("Nouvelle Partie");
    newGameTitle->setFont(QFont("Arial", 24));
    newGameTitle->setPos(100, 50);
    newGameScene->addItem(newGameTitle);
    
     // affiche les paramètres du jeu 
    QGraphicsTextItem* playerInfo = new QGraphicsTextItem("Joueur 1: [Nom]\nJoueur 2: [Nom ou IA]");
    playerInfo->setFont(QFont("Arial", 16));
    playerInfo->setPos(100, 120);
    newGameScene->addItem(playerInfo);

    QPushButton* startButton = new QPushButton("Démarrer");
    QGraphicsProxyWidget* startButtonProxy = newGameScene->addWidget(startButton);
    startButtonProxy->setPos(100, 200);
    
    connect(startButton, &QPushButton::clicked, [=]() {
        emit nouvellePartieDemandee();  
    });
    
    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = newGameScene->addWidget(backButton);
    backButtonProxy->setPos(100, 250);

    
    connect(backButton, &QPushButton::clicked, [=]() {
        setScene(mainMenuScene);
    });
}


void MainMenu::goToNewGame() {
    setScene(newGameScene);
}

void MainMenu::goToSettings() {
    settingsWindow->show();  // Affiche la fenêtre Settings
}

void MainMenu::quitApplication() {
    emit quitApplication();
}

void MainMenu::appliquerSettings(QString joueur1, QString joueur2, bool contreIA, QSet<QString> extensions, int nbUndo) {
    QMessageBox::information(this, "Paramètres Appliqués", 
                             QString("Joueur 1 : %1\nJoueur 2 : %2\nIA : %3\nExtensions : %4\nTours annulables : %5")
                             .arg(joueur1)
                             .arg(joueur2)
                             .arg(contreIA ? "Oui" : "Non")
                             .arg(extensions.join(", "))
                             .arg(nbUndo));

    setScene(mainMenuScene);
}
   
 
