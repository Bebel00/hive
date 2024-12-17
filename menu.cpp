#include "mainmenu.h"
#include "settings.h"
#include "newgame.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QMessageBox>

MainMenu::MainMenu(QWidget* parent) : QGraphicsView(parent) {
    mainMenuScene = new QGraphicsScene(this);
    settingsWindow = new Settings(this);
    newGameWindow = new NewGame(this);

    settingsWindow = new Settings(this);

    setupMainMenu();
    
    
    setScene(mainMenuScene);
    connect(settingsWindow, &Settings::saveSettings, this, &MainMenu::appliquerSettings);
    connect(newGameWindow, &NewGame::startGame, this, &MainMenu::nouvellePartieDemandee);
    connect(newGameWindow, &NewGame::backToMainMenu, [=]() { setScene(mainMenuScene); });
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


void MainMenu::goToNewGame() {
    newGameWindow->show(); 
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
   
 
