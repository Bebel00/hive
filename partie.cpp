#include "partie.h"
#include "plateau.h"

#include "insecte.h"
#include "usineinsecte.h"
#include "insecte.h"
#include <stdexcept>

#include <iostream>

Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo, size_t retour)
    : nb_retours_possibles(retour),
    joueur1(Qt::red, joueur1_pseudo),
    joueur2(Qt::yellow, joueur2_pseudo)
{
    plateau = new Plateau(retour, this);

    // setup_test();
}

Partie::~Partie()
{
    delete plateau;
}


std::string Partie::jouer_tour_cli(std::string cmd)
{
    std::string token;

    lire_prochain_token(cmd, token);

    if (token == "undo")
    {
        if (nb_tours < 2)
        {
            return "Vous ne pouvez pas encore annuler d'action.";
        }

        else
            annuler_deplacement();
    }

    if (token == "place")
    {
        lire_prochain_token(cmd, token);

        Type::Type type = Type::str_to_type(token);
        if (type != Type::Type::NONE)
        {
            QPoint p;

            lire_prochain_token(cmd, token);

            try
            {
                p.rx() = std::stoi(token);

                lire_prochain_token(cmd, token);

                try
                {
                    p.ry() = std::stoi(token);


                    Case* c = plateau->get_case(p);
                    if (c)
                    {
                        if (!ajouter_insecte(*tour, c, type))
                        {
                            return "Placement invalide";
                        }

                    }
                    else
                    {
                        return "Case [" + std::to_string(p.x()) + "; " + std::to_string(p.y()) + "] non existante";
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
        QPoint p;

        lire_prochain_token(cmd, token);
        try
        {
            p.rx() = std::stoi(token);

            lire_prochain_token(cmd, token);
            try
            {
                p.ry() = std::stoi(token);


                Case* c = plateau->get_case(p);
                if (c)
                {

                    QPoint p2;

                    lire_prochain_token(cmd, token);
                    try
                    {
                        p2.rx() = std::stoi(token);


                        lire_prochain_token(cmd, token);
                        try
                        {
                            p2.ry() = std::stoi(token);


                            Case* c2 = plateau->get_case(p2);
                            if (c2)
                            {
                                if (c->get_joueur() == tour)
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
                                return "Case [" + std::to_string(p2.x()) + "; " + std::to_string(p2.y()) + "] non existante";
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
                    return "Case [" + std::to_string(p.x()) + "; " + std::to_string(p.y()) + "] non existante";
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

    /*else if (token=="cloporte")
    {
        if(!tour->a_place_cloporte())
        {
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
    }*/

    else{
        return "Commande inconnue";
    }

    jouer_tour();

    return get_display_plateau();
}

bool Partie::ajouter_insecte(Joueur& joueur, Case* c, Type::Type type, bool bypass)
{
    std::unique_ptr<Insecte> insecte = UsineInsecte::get_usine().fabriquer(type, &joueur);

    return (joueur.peut_utiliser(type) && plateau->placer_insecte(c, std::move(insecte), joueur, bypass)) || bypass;
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
    ajouter_insecte(joueur2, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_GAUCHE), Type::Type::SAUTERELLE);
}

void Partie::annuler_deplacement()
{
    if (nb_tours > 1) { nb_tours--; nb_tours--; }
    plateau->annuler_deplacement();
}

std::string Partie::get_display_plateau() const
{
    std::string plateau_str = "";

    int x_max = plateau->get_cases()[0]->get_position().x();
    int x_min = plateau->get_cases()[0]->get_position().x();

    int y_max = plateau->get_cases()[0]->get_position().y();
    int y_min = plateau->get_cases()[0]->get_position().y();
    for (auto i_case : plateau->get_cases())
    {
        if (i_case->get_position().x() > x_max)
            x_max = i_case->get_position().x();

        else if (i_case->get_position().x() < x_min)
            x_min = i_case->get_position().x();

        if (i_case->get_position().y() > y_max)
            y_max = i_case->get_position().y();

        else if (i_case->get_position().y() < y_min)
            y_min = i_case->get_position().y();
    }

    int n_lignes = y_max - y_min + 1;
    int n_colonnes = x_max - x_min + 1;

    std::vector<std::string> plateau_str_vec;
    for (int i{0}; i < n_lignes; i++)
        plateau_str_vec.push_back(std::string(n_colonnes, ' '));

    for (auto i_case : plateau->get_cases())
    {
        if (Case::is_empty(i_case))
            plateau_str_vec[i_case->get_position().y() - y_min][i_case->get_position().x() - x_min]
                = '.';
        else
            plateau_str_vec[i_case->get_position().y() - y_min][i_case->get_position().x() - x_min]
                = Type::type_to_str(i_case->get_pion()->get_type())[0];
    }

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
        if (c->get_pion()->get_type() == Type::Type::ABEILLE && c->get_joueur() == &joueur)
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

void Partie::jouer_tour()
{
    if (tour==&joueur1)
        tour=&joueur2;

    else
    {
        tour=&joueur1;
        nb_tours++;
    }
}


