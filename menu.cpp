#include "mainmenu.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>

MainMenu::MainMenu(QWidget* parent) : QGraphicsView(parent) {
    mainMenuScene = new QGraphicsScene(this);
    newGameScene = new QGraphicsScene(this);
    settingsScene = new QGraphicsScene(this);

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

void MainMenu::setupSettingsScene() {
    QGraphicsTextItem* settingsTitle = new QGraphicsTextItem("Paramètres du Jeu");
    settingsTitle->setFont(QFont("Arial", 24));
    settingsTitle->setPos(100, 50);
    settingsScene->addItem(settingsTitle);

    QGraphicsTextItem* player1Label = new QGraphicsTextItem("Nom du Joueur 1:");
    player1Label->setPos(100, 120);
    settingsScene->addItem(player1Label);

    QLineEdit* player1Input = new QLineEdit();
    QGraphicsProxyWidget* player1InputProxy = settingsScene->addWidget(player1Input);
    player1InputProxy->setPos(250, 120);

    QGraphicsTextItem* opponentLabel = new QGraphicsTextItem("Choisissez l'adversaire:");
    opponentLabel->setPos(100, 180);
    settingsScene->addItem(opponentLabel);

    QRadioButton* vsPlayerButton = new QRadioButton("Contre un autre joueur");
    QRadioButton* vsIAButton = new QRadioButton("Contre l'IA");
    QGraphicsProxyWidget* vsPlayerButtonProxy = settingsScene->addWidget(vsPlayerButton);
    QGraphicsProxyWidget* vsIAButtonProxy = settingsScene->addWidget(vsIAButton);
    vsPlayerButtonProxy->setPos(250, 200);
    vsIAButtonProxy->setPos(250, 230);

    QButtonGroup* opponentGroup = new QButtonGroup(this);
    opponentGroup->addButton(vsPlayerButton);
    opponentGroup->addButton(vsIAButton);

    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = settingsScene->addWidget(backButton);
    backButtonProxy->setPos(100, 300);

    connect(backButton, &QPushButton::clicked, [=]() {
        setScene(mainMenuScene);
    });

   
    QPushButton* saveButton = new QPushButton("Sauvegarder");
    QGraphicsProxyWidget* saveButtonProxy = settingsScene->addWidget(saveButton);
    saveButtonProxy->setPos(250, 300);

    connect(saveButton, &QPushButton::clicked, [=]() {
        if (player1Input->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer le nom du Joueur 1.");
            return;
        }

        QString joueur1 = player1Input->text();
        QString joueur2 = (vsPlayerButton->isChecked()) ? "Joueur 2" : "IA";
        bool contreIA = vsIAButton->isChecked();

        emit nouvellePartieDemandee(joueur1, joueur2, contreIA);
        setScene(mainMenuScene);
    });
}

void MainMenu::goToNewGame() {
    emit nouvellePartieDemandee(); 
}

void MainMenu::goToSettings() {
    setScene(settingsScene);
}
void MainMenu::quitApplication() {
    emit quitapplication(); 
}
