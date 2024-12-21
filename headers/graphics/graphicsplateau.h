#ifndef GRAPHICSPLATEAU_H
#define GRAPHICSPLATEAU_H

#include <QGraphicsScene>
#include "../teams.h"

class GraphicsPlateau : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsPlateau(class Plateau* plateau, QObject *parent = nullptr);

    QGraphicsScene* get_scene() { return this; }

    class Plateau* plateau;

    void placer_insecte(class GraphicsCase* c, Team team);

    void add_case(class Case* c);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    class GraphicsCase* case_selectionnee = nullptr;

    void surbriller_cases(std::vector<Case*>& cases, QColor color, qreal zvalue);
};

#endif // GRAPHICSPLATEAU_H
