#ifndef GRAPHICSPLATEAU_H
#define GRAPHICSPLATEAU_H

#include <QGraphicsScene>
#include "menuplacerinsecte.h"
#include "plateau.h"

class GraphicsPlateau : public QGraphicsScene
{
    Q_OBJECT

    friend class MenuPlacerInsecte;

public:
    GraphicsPlateau(Plateau* plateau, QObject *parent = nullptr);

    QGraphicsScene* get_scene() { return this; }

    Plateau* plateau;

    void placer_insecte(GraphicsCase* c, Team team);


    void add_case(Case* c);

    void set_menu_placer_insecte(class MenuPlacerInsecte * menuPI) {menu_placer_insecte = menuPI; }

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    class GraphicsCase* case_selectionnee = nullptr;

    class MenuPlacerInsecte * menu_placer_insecte;

    void surbriller_cases(std::vector<Case*>& cases, QColor color, qreal zvalue);
};

#endif // GRAPHICSPLATEAU_H
