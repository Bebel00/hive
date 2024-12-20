#ifndef GRAPHICSPARTIE_H
#define GRAPHICSPARTIE_H

#include <QGraphicsView>
#include <partie.h>
#include "menuplacerinsecte.h"

class GraphicsPartie : public QGraphicsView
{
    Q_OBJECT

    friend class MenuPlacerInsecte;

public:
    GraphicsPartie(class Partie* partie, QWidget *parent = nullptr);

private:
    Partie* partie;
};

#endif // GRAPHICSPARTIE_H
