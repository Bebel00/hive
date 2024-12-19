#include "graphicsplateau.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>

#include "plateau.h"
#include "insecte.h"
#include "joueur.h"
#include "partie.h"
#include <iostream>

#include "graphicscase.h"

#include <string>

GraphicsPlateau::GraphicsPlateau(Plateau* plateau, QObject *parent)
    : QGraphicsScene{parent}, plateau(plateau)
{
    for (auto i_case : plateau->get_cases())
    {
        add_case(i_case);
        if (i_case->possede_pion())
            placer_insecte(i_case->graphics.get(), i_case->get_joueur());
    }
}

void GraphicsPlateau::placer_insecte(GraphicsCase* c, Joueur *joueur)
{
    QBrush brush;
    brush.setColor(Qt::darkCyan);
    brush.setStyle(Qt::SolidPattern);

    c->setBrush(brush);

    // La première lettre du type
    c->textItem->setPlainText(QString(type_to_str(c->case_logique->pion->get_type())[0])+QString(type_to_str(c->case_logique->pion->get_type())[1]));

    c->textItem->setDefaultTextColor(joueur->get_color());
}

void GraphicsPlateau::deplacer_insecte(GraphicsCase* depart, GraphicsCase* arrivee)
{
    if (depart->case_logique->possede_pion())
    {
        depart->textItem->setPlainText(QString(type_to_str(depart->case_logique->pion->get_type())[0])+QString(type_to_str(depart->case_logique->pion->get_type())[1]));

        depart->textItem->setDefaultTextColor(depart->case_logique->get_joueur()->get_color());
    }
    else
    {
        QBrush brush;
        brush.setStyle(Qt::NoBrush);
        depart->setBrush(brush);
        depart->textItem->setPlainText("");
    }

    if (arrivee)
        placer_insecte(arrivee, arrivee->case_logique->get_pion()->get_joueur());
}

void GraphicsPlateau::retirer_insecte(GraphicsCase *c)
{
    deplacer_insecte(c, nullptr);
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
                if (case_selectionnee!=nullptr && std::find(move_possibles.begin(), move_possibles.end(), case_cliquee->case_logique) != move_possibles.end())
                {
                    std::string command = "move " + std::to_string(int(case_selectionnee->case_logique->position.x())) + " "
                                          + std::to_string(int(case_selectionnee->case_logique->position.y())) + " "
                                          + std::to_string(int(case_cliquee->case_logique->position.x())) + " "
                                          + std::to_string(int(case_cliquee->case_logique->position.y()));
                    plateau->partie->jouer_tour_cli(command);

                    // Reset la surbrillance
                    surbriller_cases(plateau->liste_cases, Qt::red, 0);

                    case_selectionnee = nullptr;

                    if(plateau->get_partie()->verifier_victoire()){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Partie Terminée");
                        int gagnant=plateau->get_partie()->get_gagnant();
                        if(gagnant==1){
                            msgBox.setText("Le joueur 1 a gagné!");
                        }else if(gagnant==2){
                            msgBox.setText("Le joueur 2 a gagné!");
                        }
                        msgBox.setIcon(QMessageBox::Information); // Peut être Warning, Critical, etc.
                        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                        int ret = msgBox.exec();

                        // Facultatif : gestion du choix de l'utilisateur
                        if (ret == QMessageBox::Ok) {
                            qDebug("OK clicked");
                        } else if (ret == QMessageBox::Cancel) {
                            qDebug("Cancel clicked");
                        }
                    }


                    return;
                }
                // Reset la surbrillance
                surbriller_cases(plateau->liste_cases, Qt::red, 0);

                case_selectionnee = case_cliquee;
                case_selectionnee->setPen(QPen(Qt::cyan));
                case_selectionnee->setZValue(1);


                if (case_selectionnee->case_logique->possede_pion()
                    && case_selectionnee->case_logique->get_pion()->get_joueur() == plateau->get_partie()->get_tour_joueur())
                {
                    move_possibles.clear();
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
