#include "insecte.h"
#include "case.h"
#include <vector>

Insecte::Insecte(Team team) : team(team)
{

}

void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team)
{
    for (auto i_case : liste_cases)
        if (Insecte::verifier_placement(i_case, team))
            placements_possibles.push_back(i_case);
}

bool Insecte::verifier_placement(Case * const c, const Team team)
{
    // Est-ce qu'il existe un allié adjacent ?
    bool a_allie = false;

    // Pour chaque direction on vérifie le contenu de la case
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {

        // La case pour la direction actuelle
        const Case* c_direction = c->case_from_direction(i_direction);

        // Est-ce que la case est vide ?
        bool is_empty = Case::is_empty(c_direction);

        // Si la case n'est pas vide on regarde son contenu
        if (!is_empty)
        {
            if (c_direction->get_team() == team)
                // il y a un allié
                a_allie = true;


            else
                // il y a un ennemi : impossible de placer
                return false;
        }
    }

    // Une fois toutes les directions vérifiées, on regarde si il y a bien un allié adjacent pour placer le pion
    return a_allie;
}


bool Insecte::placer(Case * const c)
{
    // On vérifie le placement, s'il est bon, on place le pion
    if (verifier_placement(c, team))
    {
        position = c;
        return true;
    }
    else
    {
        return false;
    }
}

bool Insecte::bouger(Case* const c)
{
    if (verifier_move(c))
    {
        position = c;
        return true;
    }
    return false;
}
