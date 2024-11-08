#include "partie.h"
#include "teams.h"
#include "plateau.h"

#include "mainwindow.h"

#include "insecte.h"
#include "usineinsecte.h"

#include <QGraphicsView>
#include <QScrollBar>


Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo)
{
    plateau = new Plateau();

    joueur1 = Joueur(Team::BLANC, joueur1_pseudo);
    joueur2 = Joueur(Team::NOIR, joueur2_pseudo);

    view = new QGraphicsView(plateau->get_scene());
    view->setBackgroundBrush(QBrush(Qt::black));

    view->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    view->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
}

Partie::~Partie()
{
    for (auto& i_insecte : insectes)
        delete i_insecte;

    delete plateau;
}

std::string Partie::jouer_tour_cli(std::string cmd)
{
    std::string token;

    lire_prochain_token(cmd, token);

    if (token == "place")
    {
        lire_prochain_token(cmd, token);

        Type::Type type = Type::str_to_type(token);
        if (type != Type::Type::NONE)
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
                        if (!ajouter_insecte(tour, c, type))
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
                                if (c->get_pion()->get_team() == tour)
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

    else
        return "Commande inconnue";

    if (tour == Team::BLANC)
        tour = Team::NOIR;
    else
        tour = Team::BLANC;

    nb_tours++;

    return get_display_plateau();
}

bool Partie::ajouter_insecte(Team team, Case* c, Type::Type type, bool bypass)
{
    std::unique_ptr<Insecte> insecte = UsineInsecte::get_usine().fabriquer(type, team);
    return plateau->placer_insecte(c, std::move(insecte), team, bypass);
}

void Partie::lire_prochain_token(std::string &cmd, std::string &token)
{
    char delimiter = ' ';

    token = cmd.substr(0, cmd.find(delimiter));
    cmd = cmd.substr(cmd.find(delimiter) + 1);
}

void Partie::setup_test()
{
    ajouter_insecte(Team::NOIR, plateau->get_case_base(), Type::Type::ABEILLE);
    ajouter_insecte(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::BAS_DROIT), Type::Type::ABEILLE);
    ajouter_insecte(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::HAUT_GAUCHE), Type::Type::SAUTERELLE);
    ajouter_insecte(Team::NOIR, plateau->get_case_base()->get_case_from_direction(Case::Direction::DROITE), Type::Type::COCCINELLE);
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
