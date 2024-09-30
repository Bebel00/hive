#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plateau.h"
#include "QGridLayout"

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

void MainWindow::setPlateau(Plateau* const plateau)
{
    plateau->setParent(this);
    layout->addWidget(plateau, 1, 1, Qt::AlignCenter);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),0,0);
    layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),2,2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(1, 1);
    plateau->update();
    plateau->show();
}

