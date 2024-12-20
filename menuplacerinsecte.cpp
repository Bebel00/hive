#include "menuplacerinsecte.h"
#include <QPushButton>
#include <QScrollBar>
#include <QGridLayout>
#include <QString>

MenuPlacerInsecte::MenuPlacerInsecte(class GraphicsPartie* const graphicpartie, QWidget *parent): QGraphicsView(parent), partie(graphicpartie->partie) {

    setBackgroundBrush(QBrush(Qt::black));
    menuPIScene = new QGraphicsScene(this);
    setScene(menuPIScene);
    //ajout des Insectes blancs
    size_t pos_x = 0 ;
    size_t pos_y = 0 ;

    for(auto i_umap: partie->get_joueur1().get_jetons()){
        if(i_umap.second > 0){ //
            QPushButton * bouton = new QPushButton();
            bouton->setText(Type::type_to_str(i_umap.first));
            bouton->setGeometry(pos_x, pos_y, bouton->width(),bouton->height());
            menuPIScene->addWidget(bouton);
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

    for(auto i_umap: partie->get_joueur2().get_jetons()){
        if(i_umap.second > 0){ //
            QPushButton * bouton = new QPushButton();
            bouton->setText(Type::type_to_str(i_umap.first));
            bouton->setGeometry(pos_x, pos_y, bouton->width(),bouton->height());
            menuPIScene->addWidget(bouton);
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
    delete menuPIScene;
}
