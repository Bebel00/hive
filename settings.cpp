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

    // cocher les extensions 
    QGraphicsTextItem* extensionsLabel = new QGraphicsTextItem("Extensions disponibles:");
    extensionsLabel->setPos(100, 260);
    settingsScene->addItem(extensionsLabel);  

    QCheckBox* moustiqueBox = new QCheckBox("Moustique");
    QCheckBox* coccinelleBox = new QCheckBox("Coccinelle");
    QCheckBox* cloporteBox = new QCheckBox("Cloporte");

    QGraphicsProxyWidget* moustiqueProxy = settingsScene->addWidget(moustiqueBox);
    QGraphicsProxyWidget* coccinelleProxy = settingsScene->addWidget(coccinelleBox);
    QGraphicsProxyWidget* cloporteProxy = settingsScene->addWidget(cloporteBox);

    moustiqueProxy->setPos(250, 300);
    coccinelleProxy->setPos(250, 330);
    cloporteProxy->setPos(250, 360);


    // Boîte de sélection pour le nombre de tours annulables (undo)
    QGraphicsTextItem* undoLabel = new QGraphicsTextItem("Nombre de tours annulables :");
    undoLabel->setPos(100, 390);
    settingsScene->addItem(undoLabel);

    QSpinBox* undoSpinBox = new QSpinBox();
    undoSpinBox->setRange(0, 10);  // limite entre 0 et 10 tours
    undoSpinBox->setValue(3);      // valeur par défaut
    QGraphicsProxyWidget* undoProxy = settingsScene->addWidget(undoSpinBox);
    undoProxy->setPos(250, 390);


    // boutons de retour et sauvegarde
    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = settingsScene->addWidget(backButton);
    backButtonProxy->setPos(100, 450);

    QPushButton* saveButton = new QPushButton("Sauvegarder");
    QGraphicsProxyWidget* saveButtonProxy = settingsScene->addWidget(saveButton);
    saveButtonProxy->setPos(250, 450);

    connect(backButton, &QPushButton::clicked, this, &Settings::backToMainMenu);

    connect(saveButton, &QPushButton::clicked, [=]() {
        if (player1Input->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer le nom du Joueur 1.");
            return;
        }
        //collecter les infos des joueurs 
        QString joueur1 = player1Input->text();
        QString joueur2 = vsPlayerButton->isChecked() ? "Joueur 2" : "IA";

        // collecter les extensions sélectionnées
        QSet<QString> extensions;
        if (moustiqueBox->isChecked()) extensions.insert("Moustique");
        if (coccinelleBox->isChecked()) extensions.insert("Coccinelle");
        if (cloporteBox->isChecked()) extensions.insert("Cloporte");

        // récupère le nombre de tours d'annulation
        int nbUndo = undoSpinBox->value();  

        
        emit saveSettings(joueur1, joueur2, vsIAButton->isChecked(),, extensions, nbUndo);
    });
}
