#include "settings.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSpinBox>

Settings::Settings(QWidget* parent) : QGraphicsView(parent), settingsScene(new QGraphicsScene(this))
{
    // configuration initiale
    setupSettingsScene();
    //associe la scène
    setScene(settingsScene);
}

void Settings::setupSettingsScene() 
{
    /// Titre principal
    QGraphicsTextItem* title = new QGraphicsTextItem("Paramètres");
    title->setFont(QFont("Arial", 24));
    title->setPos(100, 50);
    settingsScene->addItem(title);

    // Configuration des sections
    setupPlayerInputs();
    setupExtensionOptions();
    setupUndoOption();
    setupButtons();
    }

   void Settings::setupPlayerInputs() 
{
    // label et champ pour le nom du joueur 1
    QGraphicsTextItem* player1Label = new QGraphicsTextItem("Nom du Joueur 1 :");
    player1Label->setPos(100, 120);
    settingsScene->addItem(player1Label);

    player1Input = new QLineEdit();
    QGraphicsProxyWidget* player1InputProxy = settingsScene->addWidget(player1Input);
    player1InputProxy->setPos(250, 120);

    // sélection de l'adversaire (IA ou joueur)
    QGraphicsTextItem* opponentLabel = new QGraphicsTextItem("Adversaire :");
    opponentLabel->setPos(100, 180);
    settingsScene->addItem(opponentLabel);

    vsPlayerButton = new QRadioButton("Contre un autre joueur");
    vsIAButton = new QRadioButton("Contre l'IA");

    QGraphicsProxyWidget* vsPlayerProxy = settingsScene->addWidget(vsPlayerButton);
    QGraphicsProxyWidget* vsIAProxy = settingsScene->addWidget(vsIAButton);

    vsPlayerProxy->setPos(250, 200);
    vsIAProxy->setPos(250, 230);

    
    opponentGroup = new QButtonGroup(this);
    opponentGroup->addButton(vsPlayerButton);
    opponentGroup->addButton(vsIAButton);
}

    void Settings::setupExtensionOptions() 
{
    // Label pour les extensions
    QGraphicsTextItem* extensionsLabel = new QGraphicsTextItem("Extensions disponibles :");
    extensionsLabel->setPos(100, 260);
    settingsScene->addItem(extensionsLabel);

    // Cases à cocher pour chaque extension
    moustiqueBox = new QCheckBox("Moustique");
    coccinelleBox = new QCheckBox("Coccinelle");
    cloporteBox = new QCheckBox("Cloporte");

    settingsScene->addWidget(moustiqueBox)->setPos(250, 300);
    settingsScene->addWidget(coccinelleBox)->setPos(250, 330);
    settingsScene->addWidget(cloporteBox)->setPos(250, 360);
}
    
void Settings::setupUndoOption()
{
    // label et champ pour le nombre de tours annulables
    QGraphicsTextItem* undoLabel = new QGraphicsTextItem("Nombre de tours annulables :");
    undoLabel->setPos(100, 390);
    settingsScene->addItem(undoLabel);

    undoSpinBox = new QSpinBox();
    undoSpinBox->setRange(0, 10); // De 0 à 10 tours
    undoSpinBox->setValue(3);     // Valeur par défaut : 3
    QGraphicsProxyWidget* undoProxy = settingsScene->addWidget(undoSpinBox);
    undoProxy->setPos(250, 390);
}




void Settings::setupButtons() {
    // Bouton Retour
    QPushButton* backButton = new QPushButton("Retour");
    QGraphicsProxyWidget* backButtonProxy = settingsScene->addWidget(backButton);
    backButtonProxy->setPos(100, 450);

    // Bouton Sauvegarder
    QPushButton* saveButton = new QPushButton("Sauvegarder");
    QGraphicsProxyWidget* saveButtonProxy = settingsScene->addWidget(saveButton);
    saveButtonProxy->setPos(250, 450);

    // Connexion des boutons
    connect(backButton, &QPushButton::clicked, this, &Settings::backToMainMenu);

    connect(saveButton, &QPushButton::clicked, [=]() 
    {
        if (player1Input->text().isEmpty()) 
        {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer le nom du Joueur 1.");
            return;
        }

        // Récupération des paramètres
        QString joueur1 = player1Input->text();
        QString joueur2 = vsPlayerButton->isChecked() ? "Joueur 2" : "IA";

        QSet<QString> extensions;
        if (moustiqueBox->isChecked()) extensions.insert("Moustique");
        if (coccinelleBox->isChecked()) extensions.insert("Coccinelle");
        if (cloporteBox->isChecked()) extensions.insert("Cloporte");

        int nbUndo = undoSpinBox->value();

        // signal avec les paramètres
        
        emit saveSettings(joueur1, joueur2, vsIAButton->isChecked(), extensions, nbUndo);

    }

        void Settings::backToMainMenu() 
{
    emit backToMainMenu();  // signal pour revenir au menu principal
}
    });
}
