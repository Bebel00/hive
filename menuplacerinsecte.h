#ifndef MENUPLACERINSECTE_H
#define MENUPLACERINSECTE_H

#include <QGraphicsView>
#include <QObject>
#include <graphicspartie.h>
#include <partie.h>
#include <QGridLayout>

class MenuPlacerInsecte : public QGraphicsView
{
    Q_OBJECT

    friend class GraphicsPartie;

public:
    MenuPlacerInsecte(class GraphicsPartie* const graphicpartie, QWidget *parent = nullptr);
    ~MenuPlacerInsecte();

private:
    class Partie* partie;
    QGraphicsScene* menuPIScene=nullptr;
};


#endif // MENUPLACERINSECTE_H
