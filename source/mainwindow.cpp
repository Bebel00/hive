#include "../headers/mainwindow.h"
#include "../ui_mainwindow.h"

#include "../headers/graphics/graphicspartie.h"

#include <QGridLayout>
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
}
