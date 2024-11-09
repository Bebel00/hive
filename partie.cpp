#include "partie.h"
#include "abeille.h"
#include "teams.h"
#include "plateau.h"
#include "insecte.h"
#include "araignee.h"
#include "mainwindow.h"
#include "scarabe.h"
#include <QGraphicsView>
#include <QScrollBar>


Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo)
{
    plateau = new Plateau();

    joueur1 = Joueur(Team::BLANC, joueur1_pseudo);
    joueur2 = Joueur(Team::NOIR, joueur2_pseudo);

    ajouter_insecte<Abeille>(Team::NOIR, plateau->get_case_base());
    ajouter_insecte<Abeille>(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::BAS_DROIT));

    view = new QGraphicsView(plateau->get_scene());
    view->setBackgroundBrush(QBrush(Qt::black));

    view->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    view->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    ajouter_insecte<Scarabe>(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_GAUCHE));

     ajouter_insecte<Araignee>(Team::NOIR, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_DROIT));
    ajouter_insecte<Araignee>(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_GAUCHE)); 

}

Partie::~Partie()
{
    for (auto& i_insecte : insectes)
        delete i_insecte;

    delete plateau;
}

template<typename T_Insecte>
void Partie::ajouter_insecte(Team team, Case* c)
{
    // La fonction ne marche que pour des sous-types d'insecte
    static_assert(std::is_base_of<Insecte, T_Insecte>::value);

    T_Insecte* insecte = new T_Insecte(team);
    plateau->placer_insecte(c, insecte, team, true);
}
bool Partie::verifier_victoire()
{
    bool victoire_joueur1 = verifier_victoire_joueur(joueur1);
    bool victoire_joueur2 = verifier_victoire_joueur(joueur2);

    if (victoire_joueur1)
    {
        return true;
    }
    else if (victoire_joueur2)
    {
        return true;
    }

    return false;
}

bool Partie::verifier_victoire_joueur(const Joueur& joueur)
{
    Abeille* abeille_joueur = nullptr;
    for (auto insecte : plateau->get_insectes())
    {
        if (insecte->get_type() == Insecte::Type::ABEILLE && insecte->get_team() == joueur.get_team())
        {
            abeille_joueur = dynamic_cast<Abeille*>(insecte);
            break;
        }
    }

    if (abeille_joueur == nullptr)
    {
        return false;
    }

    for (auto direction : Case::DIRECTIONS_ALL)
    {
        Case* case_voisine = abeille_joueur->get_case()->get_case_from_direction(direction);
        if (case_voisine != nullptr && Case::is_empty(case_voisine))
        {
            return false;
        }
    }

    return true;
}
