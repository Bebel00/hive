#ifndef GRAPHICSPLATEAU_H
#define GRAPHICSPLATEAU_H

#include <QGraphicsScene>

#include "plateau.h"

class GraphicsPlateau : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsPlateau(Plateau* plateau, QObject *parent = nullptr);

    QGraphicsScene* get_scene() { return this; }

    Plateau* plateau;

    void placer_insecte(GraphicsCase* c, Joueur* joueur);
    void deplacer_insecte(GraphicsCase* depart, GraphicsCase* arrivee);
    void retirer_insecte(GraphicsCase* c);
    void add_case(Case* c);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    class GraphicsCase* case_selectionnee = nullptr;

    void surbriller_cases(std::vector<Case*>& cases, QColor color, qreal zvalue);

    std::vector<Case*> move_possibles;

};

#endif // GRAPHICSPLATEAU_H
