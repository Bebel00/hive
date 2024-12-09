#include "mainwindow.h"
#include "plateau.h"
#include "ui_mainwindow.h"
#include "partie.h"
#include "QGridLayout"
#include <QGraphicsView>
#include <QPushButton>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

void MainWindow::setPartie(Partie* const p)
{
    layout->addWidget(p->get_view(), 1, 1, Qt::AlignCenter);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),0,0);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),2,2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 16);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(1, 9);
    partie=p;
    if (partie->get_nb_retour_possible()>0){
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
    if (partie->get_nb_tours()==0){
        annuler->setText("Vous ne pouvez pas annuler tant que les 2 joueurs n'ont pas encore jouer");
    }else if(partie->get_nb_tours()==1){
        annuler->setText("Vous ne pouvez pas annuler le premier tour");
    }else{
        partie->get_plateau()->annuler_deplacement(2);
        partie->annuler_tour();
    }
    annuler->setText("Annuler");



}
