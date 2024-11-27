#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partie.h"
#include <QPushButton>
#include <QMessageBox>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , partie(nullptr)
{
    ui->setupUi(this);
    layout = new QGridLayout(centralWidget());
    centralWidget()->setLayout(layout);


    QPushButton* boutonMenu = new QPushButton("Afficher Menu", this);
    layout->addWidget(boutonMenu, 0, 0, Qt::AlignTop);


    QPushButton* boutonFermerMenu = new QPushButton("Fermer Menu", this);
    layout->addWidget(boutonFermerMenu, 0, 1, Qt::AlignTop);


    connect(boutonMenu, &QPushButton::clicked, this, &MainWindow::afficherMenu);
    connect(boutonFermerMenu, &QPushButton::clicked, this, &MainWindow::fermerMenu);

    
    boutonFermerMenu->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete layout;
    delete ui;
}

void MainWindow::setPartie(Partie* const nouvellePartie)
{
    // Supprime l'ancienne partie si elle existe
    if (partie) {
        layout->removeWidget(partie->get_view());
        delete partie;
        partie = nullptr;
    }

    // Associe la nouvelle partie
    partie = nouvellePartie;
    layout->addWidget(partie->get_view(), 1, 1, Qt::AlignCenter);

    // Ajoute des marges autour du plateau
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 16);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(1, 9);
}

void MainWindow::afficherMenu()
{
    if (partie != nullptr) {
        partie->afficher_menu(); 

        QMessageBox::information(this, "Menu", 
            "Le menu est maintenant affiché. Vous devez le fermer pour continuer à jouer.");
    }

    
    auto boutonFermerMenu = qobject_cast<QPushButton*>(layout->itemAtPosition(0, 1)->widget());
    if (boutonFermerMenu) boutonFermerMenu->setEnabled(true);

    auto boutonMenu = qobject_cast<QPushButton*>(layout->itemAtPosition(0, 0)->widget());
    if (boutonMenu) boutonMenu->setEnabled(false);
}

void MainWindow::fermerMenu()
{
    if (partie != nullptr) {
        partie->fermer_menu(); // Ferme le menu via l'objet Partie

        // Émet le signal pour retourner au menu principal si nécessaire
        emit menuFerme();
    }

    // Mise à jour des boutons
    auto boutonFermerMenu = qobject_cast<QPushButton*>(layout->itemAtPosition(0, 1)->widget());
    if (boutonFermerMenu) boutonFermerMenu->setEnabled(false);

    auto boutonMenu = qobject_cast<QPushButton*>(layout->itemAtPosition(0, 0)->widget());
    if (boutonMenu) boutonMenu->setEnabled(true);
}

void MainWindow::recommencerPartie()
{
    
    emit nouvellePartieDemandee();
}
