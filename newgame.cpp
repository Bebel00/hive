#include "newgame.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>

NewGame::NewGame(QWidget* parent) : QGraphicsView(parent) {
    newGameScene = new QGraphicsScene(this);
    setupNewGameScene();
    setScene(newGameScene);
}

void NewGame::setupNewGameScene() {
    QGraphicsTextItem* title = new QGraphicsTextItem("Nouvelle Partie");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    newGameScene->addItem(title);

    QPushButton* startButton = new QPushButton("Démarrer");
    QGraphicsProxyWidget* startProxy = newGameScene->addWidget(startButton);
    startProxy->setPos(100, 200);

    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backProxy = newGameScene->addWidget(backButton);
    backProxy->setPos(100, 250);

    connect(startButton, &QPushButton::clicked, this, &NewGame::startGame);
    connect(backButton, &QPushButton::clicked, this, &NewGame::backToMainMenu);
}
