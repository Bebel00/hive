#include "graphicspartie.h"

#include "partie.h"
#include "plateau.h"
#include "graphicsplateau.h"

#include <iostream>
#include <QScrollBar>
#include <QGraphicsView>

#include <memory>

GraphicsPartie::GraphicsPartie(Partie* partie, QWidget* parent) : QGraphicsView(parent), partie(partie)
{
    partie->plateau->graphics = std::make_unique<GraphicsPlateau>(partie->plateau);

    setScene(partie->plateau->graphics.get());

    setBackgroundBrush(QBrush(Qt::black));

    horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    std::cout<< partie->plateau->graphics.get()->height();
}
