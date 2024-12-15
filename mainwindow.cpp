#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicspartie.h"
#include "partie.h"
#include "plateau.h"

#include <QGridLayout>
#include <QGraphicsView>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , partie(nullptr)
{
    ui->setupUi(this);
    layout = new QGridLayout(centralWidget());
    centralWidget()->setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete layout;
    delete ui;
}

void MainWindow::setPartie(GraphicsPartie* const partie)
{
    layout->addWidget(partie, 1, 1, Qt::AlignCenter);

    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),0,0);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),2,2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 16);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(1, 9);

    if (partie->partie->nb_retours_possibles > 0)
    {
        button = new QPushButton("<-", this);
        button->setFixedSize(50, 30); // Taille fixe pour le bouton

        annuler = new QLabel("Annuler ", this);
        annuler->setAlignment(Qt::AlignCenter); // Centrer le texte du label

        // Ajouter le bouton et le label au layout
        layout->addWidget(button, 1, 0, Qt::AlignLeft | Qt::AlignBottom); // Ligne 1, Colonne 0
        layout->addWidget(annuler, 2, 0, Qt::AlignLeft | Qt::AlignTop);     // Ligne 2, Colonne 0

        // Connecter le clic du bouton à une méthode
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonAnnulerClicked);
    }
}

void MainWindow::onButtonAnnulerClicked()
{
    if (partie->partie->get_nb_tours() == 0)
        annuler->setText("Vous ne pouvez pas annuler tant que les 2 joueurs n'ont pas encore jouer");

    else if(partie->partie->get_nb_tours() == 1)
        annuler->setText("Vous ne pouvez pas annuler le premier tour");

    else
        partie->partie->get_plateau()->annuler_deplacement();

    annuler->setText("Annuler");
}
