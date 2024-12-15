#ifndef GRAPHICSPARTIE_H
#define GRAPHICSPARTIE_H

#include <QGraphicsView>

class GraphicsPartie : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsPartie(class Partie* partie, QWidget *parent = nullptr);

    Partie* partie;
};

#endif // GRAPHICSPARTIE_H
