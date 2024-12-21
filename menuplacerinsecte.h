#ifndef MENUPLACERINSECTE_H
#define MENUPLACERINSECTE_H

#include <QPushButton>
#include <QGraphicsView>
#include <QObject>
#include <graphicspartie.h>
#include "graphicsplateau.h"
#include <partie.h>
#include <QGridLayout>
#include <vector>
#include <memory>
#include "insecte.h"

class MenuPlacerInsecte : public QGraphicsView
{
    Q_OBJECT

    friend class GraphicsPartie;
    friend class GraphicsPlateau;

public:
    MenuPlacerInsecte(class GraphicsPartie* graphicpartie, QWidget *parent = nullptr);
    ~MenuPlacerInsecte();

private:
    std::vector<QPushButton *> boutons;
    class GraphicsPartie* graphicpartie;
    QGraphicsScene* menuPIScene=nullptr;

private slots:
    void selectionner_insecte();

};



class BoutonPlacementInsecte : public QPushButton
{
    Q_OBJECT

public:
    BoutonPlacementInsecte(Team team,Type::Type type, unsigned int nb_restant): QPushButton(), team(team), type(type), nb_restant(nb_restant) {}
    Team get_team() {return team;}
    Type::Type get_type(){return type;}
    unsigned int get_nb_restant(){return nb_restant;}

private:
    Team team;
    Type::Type type;
    unsigned int nb_restant;
};


#endif // MENUPLACERINSECTE_H
