#include "settings.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>

Settings::Settings(QWidget* parent) : QGraphicsView(parent) {
    settingsScene = new QGraphicsScene(this);
    setupSettingsScene();
    setScene(settingsScene);
}

void Settings::setupSettingsScene() {
    QGraphicsTextItem* title = new QGraphicsTextItem("Paramètres");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    settingsScene->addItem(title);

    QGraphicsTextItem* player1Label = new QGraphicsTextItem("Nom du Joueur 1:");
    player1Label->setPos(100, 120);
    settingsScene->addItem(player1Label);

    QLineEdit* player1Input = new QLineEdit();
    QGraphicsProxyWidget* player1InputProxy = settingsScene->addWidget(player1Input);
    player1InputProxy->setPos(250, 120);

    QGraphicsTextItem* opponentLabel = new QGraphicsTextItem("Adversaire:");
    opponentLabel->setPos(100, 180);
    settingsScene->addItem(opponentLabel);

    QRadioButton* vsPlayerButton = new QRadioButton("Contre un autre joueur");
    QRadioButton* vsIAButton = new QRadioButton("Contre l'IA");
    QGraphicsProxyWidget* vsPlayerProxy = settingsScene->addWidget(vsPlayerButton);
    QGraphicsProxyWidget* vsIAProxy = settingsScene->addWidget(vsIAButton);
    vsPlayerProxy->setPos(250, 200);
    vsIAProxy->setPos(250, 230);

    QButtonGroup* opponentGroup = new QButtonGroup(this);
    opponentGroup->addButton(vsPlayerButton);
    opponentGroup->addButton(vsIAButton);

    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = settingsScene->addWidget(backButton);
    backButtonProxy->setPos(100, 300);

    QPushButton* saveButton = new QPushButton("Sauvegarder");
    QGraphicsProxyWidget* saveButtonProxy = settingsScene->addWidget(saveButton);
    saveButtonProxy->setPos(250, 300);

    connect(backButton, &QPushButton::clicked, this, &Settings::backToMainMenu);

    connect(saveButton, &QPushButton::clicked, [=]() {
        if (player1Input->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer le nom du Joueur 1.");
            return;
        }
        QString joueur1 = player1Input->text();
        QString joueur2 = vsPlayerButton->isChecked() ? "Joueur 2" : "IA";
        emit saveSettings(joueur1, joueur2, vsIAButton->isChecked());
    });
}
