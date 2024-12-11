#include "partie.h"
#include "teams.h"
#include "plateau.h"
#include "mainwindow.h"

#include "insecte.h"
#include "usineinsecte.h"
#include "cloporte.h"
#include "insecte.h"
#include <stdexcept>

#include <QGraphicsView>
#include <QScrollBar>
#include <iostream>




Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo,size_t retour)
    : joueur1(Team::BLANC, joueur1_pseudo), joueur2(Team::NOIR, joueur2_pseudo),nb_retour_possible(retour)
{
    plateau = new Plateau(retour);


    setup_test();

    view = new QGraphicsView(plateau->get_scene());
    view->setBackgroundBrush(QBrush(Qt::black));

    view->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    view->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

}




Partie::~Partie()
{
    delete plateau;
}


std::string Partie::jouer_tour_cli(std::string cmd)
{
    std::string token;

    lire_prochain_token(cmd, token);


    if (token == "undo"){

        lire_prochain_token(cmd, token);
        try{
            int nb_undo=stoi(token); // Le nombre de tour que l'utilisateur veut supprimer
            if(nb_undo>nb_retour_possible){
                return " Les paramètres de la partie permettent de supprimer au maximum " + std::to_string(nb_retour_possible) + " annulations";
            }else{
                if (nb_tours<nb_undo ){
                    return "Vous avez jouer moins de tours que " + std::to_string(nb_undo);
                }else{
                    plateau->annuler_deplacement(nb_undo*2);
                    nb_tours=nb_tours-nb_undo;
                }

            }
        }catch(const std::invalid_argument& e){
            return "Nombre d'annulation invalide";
        }

    if(nb_tours==3 && token!="place" && !tour->get_a_place_abeille()){
        return " L'abeille doit être placé";
    }

    if (token == "place")
    {
        lire_prochain_token(cmd, token);

        Type::Type type = Type::str_to_type(token);
        if (type != Type::Type::NONE)
        {
            //On vérifier que l'abeille de chaque joueur est placé avant leu 5 ème tour
            if ((nb_tours==3)&& !tour->get_a_place_abeille() && type!=Type::Type::ABEILLE){
                return " L'abeille doit être placé";
            }
            Position p;

            lire_prochain_token(cmd, token);

            try
            {
                p.x = std::stoi(token);

                lire_prochain_token(cmd, token);

                try
                {
                    p.y = std::stoi(token);


                    Case* c = plateau->get_case(p);
                    if (c)
                    {
                        if (type==Type::Type::ABEILLE){
                            tour->placer_abeille();
                        }

                        if (!ajouter_insecte(*tour, c, type))
                        {
                            return "Placement invalide";
                        }

                    }
                    else
                    {
                        return "Case [" + std::to_string(p.x) + "; " + std::to_string(p.y) + "] non existante";
                    }
                }
                catch (const std::invalid_argument& e)
                {
                    return "Coordonees invalides";
                }
            }
            catch (const std::invalid_argument& e)
            {
                return "Coordonees invalides";
            }
        }
    }
    else if (token == "move")
    {
        Position p;

        lire_prochain_token(cmd, token);
        try
        {
            p.x = std::stoi(token);

            lire_prochain_token(cmd, token);
            try
            {
                p.y = std::stoi(token);


                Case* c = plateau->get_case(p);
                if (c)
                {

                    Position p2;

                    lire_prochain_token(cmd, token);
                    try
                    {
                        p2.x = std::stoi(token);


                        lire_prochain_token(cmd, token);
                        try
                        {
                            p2.y = std::stoi(token);


                            Case* c2 = plateau->get_case(p2);
                            if (c2)
                            {
                                if (c->get_pion()->get_team() == tour->get_team())
                                {
                                    std::vector<Case*> move_possibles;
                                    c->get_pion()->get_moves_possibles(move_possibles);
                                    if (std::find(move_possibles.begin(), move_possibles.end(), c2) != move_possibles.end())
                                    {
                                        plateau->deplacer_insecte(c, c2);
                                    }
                                    else
                                    {
                                        return "Movement illegal";
                                    }
                                }
                                else
                                {
                                    return "Ce n'est pas le tour de ce pion";
                                }
                            }
                            else
                            {
                                return "Case [" + std::to_string(p2.x) + "; " + std::to_string(p2.y) + "] non existante";
                            }
                        }
                        catch (const std::invalid_argument& e)
                        {
                            return "Coordonees invalides";
                        }
                    }
                    catch (const std::invalid_argument& e)
                    {
                        return "Coordonees invlalides";
                    }
                }
                else
                {
                    return "Case [" + std::to_string(p.x) + "; " + std::to_string(p.y) + "] non existante";
                }
            }
            catch (const std::invalid_argument& e)
            {
                return "Coordonees invalides";
            }
        }
        catch (const std::invalid_argument& e)
        {
            return "Coordonees invlalides";
        }
    }

    }else if (token=="cloporte"){
        if(!tour->a_place_cloporte()){
            return "Vous n'avez pas encore placer votre cloporte.";
        }
        Position p;
        lire_prochain_token(cmd,token);
        try
        {
            p.x = std::stoi(token);

            lire_prochain_token(cmd, token);
            try
            {
                p.y = std::stoi(token);


                Case* c = plateau->get_case(p);
                if (c)
                {
                    if (!c->possede_pion()){
                        Position p2;

                        lire_prochain_token(cmd, token);
                        try{
                            Position p2;

                            lire_prochain_token(cmd, token);
                            try
                            {
                                p2.x = std::stoi(token);


                                lire_prochain_token(cmd, token);
                                try
                                {
                                    p2.y = std::stoi(token);


                                    Case* c2 = plateau->get_case(p2);
                                    if (c2)
                                    {
                                        if (tour->get_cloporte()->get_team() == tour->get_team())
                                        {
                                            std::vector<Insecte*> pions_deplacer;
                                            tour->get_cloporte()->get_pion_deplacer(pions_deplacer);
                                            if (std::find(pions_deplacer.begin(),pions_deplacer.end(),c->get_pion())!=pions_deplacer.end()){
                                                std::vector<Case*> deplacements_possibles;
                                                tour->get_cloporte()->get_deplacements_possibles(deplacements_possibles);
                                                if (std::find(deplacements_possibles.begin(), deplacements_possibles.end(), c2) != deplacements_possibles.end())
                                                {
                                                    plateau->deplacer_insecte(c, c2);
                                                }
                                                else
                                                {
                                                    return "Movement illegal";
                                                }
                                            }else{
                                                return "Le Cloporte ne peut pas déplacer le pion sélectionné";
                                            }

                                        }else{
                                            return "Ce n'est pas le tour de ce pion";
                                        }
                                    }else
                                    {
                                        return "Case [" + std::to_string(p2.x) + "; " + std::to_string(p2.y) + "] non existante";
                                    }
                                }catch(const std::invalid_argument& e){
                                    return "Coordonees invalides";
                                }

                            }catch(const std::invalid_argument& e){
                                return "Coordonees invalides";
                            }

                        }catch(const std::invalid_argument& e){
                    return "Coordonees invalides";
                        }
                    }else{
                        return " Il n'y a pas de pion sur la case sélectionné";
                    }

                }else{
                    return "Case [" + std::to_string(p.x) + "; " + std::to_string(p.y) + "] non existante";
                }
            }catch(const std::invalid_argument& e){
                return "Coordonees invalides";
            }
        }catch(const std::invalid_argument& e){
                return "Coordonees invalides";
        }
    }else{
        return "Commande inconnue";
    }

    if (tour == &joueur1){
        tour = &joueur2;
    }else{
        tour = &joueur1;
        nb_tours++;
    }



    return get_display_plateau();
}

bool Partie::ajouter_insecte(Joueur& joueur, Case* c, Type::Type type, bool bypass)
{
    std::unique_ptr<Insecte> insecte=UsineInsecte::get_usine().fabriquer(type, joueur.get_team());
    return bypass ||(joueur.peut_utiliser(type) && plateau->placer_insecte(c, std::move(insecte), joueur, bypass));
}

void Partie::lire_prochain_token(std::string &cmd, std::string &token)
{
    char delimiter = ' ';

    token = cmd.substr(0, cmd.find(delimiter));
    cmd = cmd.substr(cmd.find(delimiter) + 1);
}

void Partie::setup_test()
{
    ajouter_insecte(joueur1, plateau->get_case_base(), Type::Type::ABEILLE);
    ajouter_insecte(joueur2, plateau->get_case_base()->get_case_from_direction(Case::Direction::BAS_DROIT), Type::Type::ABEILLE);
    ajouter_insecte(joueur1, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_DROIT), Type::Type::SAUTERELLE);
    ajouter_insecte(joueur2, plateau->get_case_base()->get_case_from_direction(Case::Direction::BAS_DROIT)->get_case_from_direction(Case::Direction::BAS_DROIT), Type::Type::FOURMI);
    Position p;
    p.x=1;
    p.y=1;
    plateau->deplacer_insecte(plateau->get_case(p),plateau->get_case(p)->get_case_from_direction(Case::Direction::BAS_GAUCHE)->get_case_from_direction(Case::Direction::BAS_GAUCHE));
    nb_tours=3;
}

std::string Partie::get_display_plateau() const
{
    std::string plateau_str = "";

    int x_max = plateau->get_cases()[0]->get_position().x;
    int x_min = plateau->get_cases()[0]->get_position().x;

    int y_max = plateau->get_cases()[0]->get_position().y;
    int y_min = plateau->get_cases()[0]->get_position().y;
    for (auto i_case : plateau->get_cases())
    {
        if (i_case->get_position().x > x_max)
            x_max = i_case->get_position().x;

        else if (i_case->get_position().x < x_min)
            x_min = i_case->get_position().x;

        if (i_case->get_position().y > y_max)
            y_max = i_case->get_position().y;

        else if (i_case->get_position().y < y_min)
            y_min = i_case->get_position().y;
    }

    int n_lignes = y_max - y_min + 1;
    int n_colonnes = x_max - x_min + 1;

    std::vector<std::string> plateau_str_vec;
    for (int i{0}; i < n_lignes; i++)
        plateau_str_vec.push_back(std::string(n_colonnes, ' '));

    for (auto i_case : plateau->get_cases())
        if (Case::is_empty(i_case))
            plateau_str_vec[i_case->get_position().y - y_min][i_case->get_position().x - x_min] = '.';
        else
            plateau_str_vec[i_case->get_position().y - y_min][i_case->get_position().x - x_min] = Type::type_to_str(i_case->get_pion()->get_type())[0];

    for (auto ligne : plateau_str_vec)
        plateau_str += ligne + "\n";

    return plateau_str;
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
    Case* abeille_joueur = nullptr;
    for (auto c : plateau->get_cases())
    {
        if (c->get_pion()->get_type() == Type::Type::ABEILLE && c->get_pion()->get_team() == joueur.get_team())
        {
            abeille_joueur = c;
            break;
        }
    }

    if (abeille_joueur == nullptr)
    {
        return false;
    }

    for (auto direction : Case::DIRECTIONS_ALL)
    {
        Case* case_voisine = abeille_joueur->get_case_from_direction(direction);
        if (Case::is_empty(case_voisine))
        {
            return false;
        }
    }

    return true;
}


