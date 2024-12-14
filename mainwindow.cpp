#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partie.h"

#include <QPushButton>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGraphicsView>

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

void MainWindow::setPartie(Partie* const nouvellePartie)
{
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
