#include "plateau.h"
#include "case.h"
#include <iostream>
#include <array>    // pour std::array une liste
#include <cstdlib>  // pour abs() la valeur absolue
#include <algorithm> // pour std::find trouver un élément dans une liste

Plateau::Plateau()
{
    case_base = new Case(Position(0, 0));
    liste_cases.push_back(case_base);
    creer_alentours(case_base);
}

Plateau::~Plateau()
{
    // On supprime toutes les cases
    for (auto c : liste_cases)
    {
        delete c;
    }
}



bool Plateau::verifier_suppression_case(Case *c) const
{
    // Si une case possède un pion on ne peut pas la supprimer
    if (c->possede_pion())
        return false;

    // Si toutes les cases adjacentes sont vides (donc soient nullptr soient elles ne contiennent pas d'insecte
    // Alors on peut supprimer la case
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {
        if (!Case::is_empty(c->case_from_direction(i_direction)))
            return false;
    }

    return true;
}

bool Plateau::creer_alentours(Case* c)
{
    std::array<std::array<Case*, 9>, 5> adjacence;

    explorer_adjacence_2(adjacence, c);

    Position increment_position;
    Position increment_position_2;
    Position case_base_pos(4, 2);

    // On boucle sur toutes les directions
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {
        // On regarde si la case peut bel et bien être trouvée
        Case** const i_case = c->case_ptr_from_direction(i_direction);
        if (!i_case)
        {
            std::cout << "Création alentours : impossible de créer une case, problème de direction." << std::endl;
            return false;
        }

        // Ensuite, si la case est vide, on créer une case
        if (!*i_case)
        {
            Case* nouvelle_case = c->creer_case(i_direction);
            // On vérifie bien sûr que la création se passe bien
            if (!nouvelle_case)
            {
                return false;
            }

            // Si la création s'est bien passée on ajoute la case à la liste des cases
            liste_cases.push_back(nouvelle_case);

            increment_position = Case::direction_to_position_increment(i_direction);
            for (auto j_direction : Case::DIRECTIONS_ALL)
            {
                increment_position_2 = Case::direction_to_position_increment(j_direction);
                Position position_finale = case_base_pos + increment_position + increment_position_2;
                (*(nouvelle_case->case_ptr_from_direction(j_direction))) = adjacence[position_finale.y][position_finale.x];
            }
        }
    }
    return true;
}

void Plateau::explorer_adjacence_2(std::array<std::array<Case *, 9>, 5> &adjacence, Case *case_base)
{
    for (int i{0}; i < 5; i++)
        for (int j{0}; j < 9; j++)
            adjacence[i][j] = nullptr;

    for (auto i_case : liste_cases)
    {
        if (abs(i_case->get_position().x - case_base->get_position().x) <= 2)
            if (abs(i_case->get_position().y - case_base->get_position().y) <= 4)
            {
                const int x = i_case->get_position().x - case_base->get_position().x + 4;
                const int y = i_case->get_position().y - case_base->get_position().y + 2;
                adjacence[y][x] = i_case;
            }
    }
}

bool Plateau::tenter_supprimer_case(Case *c)
{
    if (!c)
        return true;

    if (verifier_suppression_case(c))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case** const case_adjacente = c->case_ptr_from_direction(i_direction);

            // Ligne compliquée mais elle fait un truc tout simple
            // Déjà elle s'exécute que s'il y a une case adjacente pour la direction i_direction
            // Et si c'est le cas,
            // Elle remplace le pointeur qui pointe vers la case actuelle par nullptr comme on va la supprimer
            // On utilise la direction opposé pour revenir à la case actuelle du coup

            if (case_adjacente)
                *((*(case_adjacente))->case_ptr_from_direction(Case::DIRECTION_OPPOSE(i_direction))) = nullptr;
        }

        const auto index = std::find(liste_cases.begin(), liste_cases.end(), c);
        if (index != liste_cases.end())
        {
            liste_cases.erase(index);
        }
        else
        {
            std::cout << "Suppression d'une case pas dans la liste de cases, pas normal." << std::endl;
        }

        delete c;
        return true;
    }
    return false;
}
