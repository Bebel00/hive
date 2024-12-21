#include "menuplacerinsecte.h"

#include <QScrollBar>
#include <QGridLayout>
#include <QString>
#include <QPalette>
#include <string>
#include "plateau.h"
#include "partie.h"
#include "usineinsecte.h"

MenuPlacerInsecte::MenuPlacerInsecte(class GraphicsPartie* const graphicpartie, QWidget *parent): QGraphicsView(parent), graphicpartie(graphicpartie) {
    horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    setBackgroundBrush(QBrush(Qt::black));
    menuPIScene = new QGraphicsScene(this);
    setScene(menuPIScene);
    menuPIScene->setSceneRect(0,0,465,640);
    graphicpartie->partie->get_plateau()->graphics->set_menu_placer_insecte(this);

    //ajout des Insectes blancs
    size_t pos_x = 0 ;
    size_t pos_y = 0 ;
    for(auto i_umap: graphicpartie->partie->get_joueur1().get_jetons()){
        if(i_umap.second > 0){ //
            BoutonPlacementInsecte * bouton = new BoutonPlacementInsecte(Team::BLANC,i_umap.first, i_umap.second);
            bouton->setText(QString::fromStdString(Type::type_to_str(i_umap.first) + " " + std::to_string(i_umap.second)));
            bouton->setGeometry(pos_x, pos_y, 150,75);
            bouton->setStyleSheet("QPushButton {background-color: #ffffff; color: black;}");
            menuPIScene->addWidget(bouton);
            boutons.push_back(bouton);
            connect(bouton, &QPushButton::clicked, this, &MenuPlacerInsecte::selectionner_insecte);
            if(pos_x + bouton->width() + 5 < menuPIScene->width()){
               pos_x = pos_x + bouton->width() + 5;
            }
            else{
                pos_x = 0;
                pos_y = pos_y + 5 + bouton->height();
            }
        }
    }

    //ajout des Insectes noirs

    pos_x = 0 ;
    pos_y = menuPIScene->height()/2 ;
    for(auto i_umap: graphicpartie->partie->get_joueur2().get_jetons()){
        if(i_umap.second > 0){ //
            BoutonPlacementInsecte * bouton = new BoutonPlacementInsecte(Team::NOIR,i_umap.first, i_umap.second);
            bouton->setText(QString::fromStdString(Type::type_to_str(i_umap.first) + " " + std::to_string(i_umap.second)));
            bouton->setGeometry(pos_x, pos_y, 150,75);

            bouton->setStyleSheet("QPushButton {background-color: #000000; color: white;border-color: rgb(255, 255, 255); border-width : 1.2px; border-style:inset;}");

            menuPIScene->addWidget(bouton);
            boutons.push_back(bouton);
            connect(bouton, &QPushButton::clicked, this, &MenuPlacerInsecte::selectionner_insecte);
            if(pos_x + bouton->width() + 5 < menuPIScene->width()){
                pos_x = pos_x + bouton->width() + 5;
            }
            else{
                pos_x = 0;
                pos_y = pos_y + 5 + bouton->height();
            }
        }
    }
}

MenuPlacerInsecte::~MenuPlacerInsecte()
{
    for(auto i_bouton : boutons){
        delete i_bouton;
    }
    delete menuPIScene;
}

void MenuPlacerInsecte::selectionner_insecte(){
    BoutonPlacementInsecte* btn = qobject_cast<BoutonPlacementInsecte*>(sender());
    if(graphicpartie->partie->get_tour()->get_team()== btn->get_team()){
        std::vector<Case*> placements_possibles;
        insecteAPlacer = std::move(UsineInsecte::get_usine().fabriquer(btn->get_type(), btn->get_team()));
        insecteAPlacer->get_placements_possibles(graphicpartie->partie->get_plateau()->get_cases(),placements_possibles,btn->get_team());
        graphicpartie->partie->get_plateau()->graphics->surbriller_cases(graphicpartie->partie->get_plateau()->get_cases(), Qt::red, 0);
        graphicpartie->partie->get_plateau()->graphics->surbriller_cases(placements_possibles, Qt::yellow, 0.5 );
    }
}



