#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partie.h"
#include "QGridLayout"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout(centralWidget());
    centralWidget()->setLayout(layout);

    QPushButton* boutonMenu = new QPushButton("Afficher Menu", this);
    layout->addWidget(boutonMenu, 0, 0, Qt::AlignTop);

    QPushButton* boutonFermerMenu = new QPushButton("Fermer Menu", this);
    layout->addWidget(boutonFermerMenu, 0, 1, Qt::AlignTop);

    // connecte des boutons à leurs slots respectifs
    connect(boutonMenu, &QPushButton::clicked, this, &MainWindow::afficherMenu);
    connect(boutonFermerMenu, &QPushButton::clicked, this, &MainWindow::fermerMenu);

    // désactive  bouton "Fermer Menu" au début
    boutonFermerMenu->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete layout;
    delete ui;
}

void MainWindow::setPartie(Partie* const partie)
{
    this->partie = partie;
    layout->addWidget(partie->get_view(), 1, 1, Qt::AlignCenter);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),0,0);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),2,2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 16);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(1, 9);
}
void MainWindow::afficherMenu()
{
    // active le menu via la partie
    if (partie != nullptr) {
        partie->afficher_menu();

        // désactive des éléments du jeu et affichage du bouton de fermeture du menu
        QMessageBox::information(this, "Menu", "Le menu est maintenant affiché. Vous devez le fermer pour continuer à jouer.");
    }

    // mise à jour des boutons
    QPushButton* boutonFermerMenu = layout->itemAtPosition(0, 1)->widget()->findChild<QPushButton*>();
    boutonFermerMenu->setEnabled(true);
    QPushButton* boutonMenu = layout->itemAtPosition(0, 0)->widget()->findChild<QPushButton*>();
    boutonMenu->setEnabled(false);
}

void MainWindow::fermerMenu()
{
    // ferme le menu via la partie
    if (partie != nullptr) {
        partie->fermer_menu();

        // réactive bouton bouton pour afficher le menu
        QPushButton* boutonMenu = layout->itemAtPosition(0, 0)->widget()->findChild<QPushButton*>();
        boutonMenu->setEnabled(true);
    }

    // mise à jour des boutons
    QPushButton* boutonFermerMenu = layout->itemAtPosition(0, 1)->widget()->findChild<QPushButton*>();
    boutonFermerMenu->setEnabled(false);
}
