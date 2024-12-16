#include "../../headers/plateau.h"
#include "../../headers/insecte.h"
#include "../../headers/joueur.h"

#include "../../headers/graphics/graphicsplateau.h"
#include "../../headers/graphics/graphicscase.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

GraphicsPlateau::GraphicsPlateau(Plateau* plateau, QObject *parent)
    : QGraphicsScene{parent}, plateau(plateau)
{
    for (auto i_case : plateau->get_cases())
    {
        add_case(i_case);
        if (i_case->possede_pion())
            placer_insecte(i_case->graphics.get(), i_case->get_team());
    }
}

void GraphicsPlateau::placer_insecte(GraphicsCase* c, Team team)
{
    QBrush brush;
    brush.setColor(Qt::darkCyan);
    brush.setStyle(Qt::SolidPattern);

    c->setBrush(brush);

    // La première lettre du type
    c->textItem->setPlainText(QString(type_to_str(c->case_logique->pion->get_type())[0]));

    if (team == Team::BLANC)
        c->textItem->setDefaultTextColor(Qt::white);

    else
        c->textItem->setDefaultTextColor(Qt::black);
}

void GraphicsPlateau::add_case(Case *c)
{
    c->graphics = std::make_unique<GraphicsCase>(c);

    QBrush brush;

    brush.setStyle(Qt::NoBrush);
    c->graphics->setBrush(brush);
    c->graphics->setPen(QPen(Qt::red));
    addItem(c->graphics.get());
}

void GraphicsPlateau::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
        GraphicsCase* case_cliquee = qgraphicsitem_cast<GraphicsCase*>(item);


        if (case_cliquee)
        {
            if (case_cliquee != case_selectionnee)
            {

                // Reset la surbrillance
                surbriller_cases(plateau->liste_cases, Qt::red, 0);

                case_selectionnee = case_cliquee;
                case_selectionnee->setPen(QPen(Qt::cyan));
                case_selectionnee->setZValue(1);

                if (case_selectionnee->case_logique->possede_pion())
                {
                    std::vector<Case*> move_possibles;
                    case_selectionnee->case_logique->get_pion()->get_moves_possibles(move_possibles);
                    surbriller_cases(move_possibles, Qt::yellow, 0.5);
                }
            }
        }
    }
}

void GraphicsPlateau::surbriller_cases(std::vector<Case*>& cases, QColor color, qreal zvalue)
{
    for (auto i_case : cases)
    {
        i_case->graphics->setPen(QPen(color));
        i_case->graphics->setZValue(zvalue);
    }
}
