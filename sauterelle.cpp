#include "sauterelle.h"
#include "insecte.h"
#include <vector>

Sauterelle::Sauterelle(Team team) : Insecte(team)
{

}
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes

Case* Sauterelle::get_case_au_bout_direction(Case::Direction direction) const
{
    // Fonction qui permet d'obtenir la dernière case se trouvant sur une ligne droite
    Case* c = get_case();

<<<<<<< Updated upstream
    while (c->case_from_direction(direction) != nullptr)
    {
        c = c->case_from_direction(direction);
=======
    while (c->get_case_from_direction(direction) != nullptr)
    {
        c = c->get_case_from_direction(direction);
>>>>>>> Stashed changes
    }

    return c;
}


void Sauterelle::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
    // Est ce que la pièce est déjà positionné ?
    if (get_case()==nullptr)
    {
        throw "L'Insecte n'est pas encore positionné";
    }

    else if (!move_casse_ruche(get_case()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
<<<<<<< Updated upstream
            if (!Case::is_empty(get_case()->case_from_direction(i_direction)))
=======
            if (!Case::is_empty(get_case()->get_case_from_direction(i_direction)))
>>>>>>> Stashed changes
            {
                moves_possibles.push_back(get_case_au_bout_direction(i_direction));
            }
        }
    }

}


<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
>>>>>>> Stashed changes
