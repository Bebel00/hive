#include "scarabe.h"
#include "insecte.h"
#include "case.h"

Scarabe::Scarabe(Team team) : Insecte(team)
{

}
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes

void Scarabe::get_moves_possibles(std::vector<Case *> &move_possibles) const
{
    if (!move_casse_ruche(get_case()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
<<<<<<< Updated upstream
            Case* c = get_case()->case_from_direction(i_direction);
=======
            Case* c = get_case()->get_case_from_direction(i_direction);
>>>>>>> Stashed changes

            if (!Case::is_empty(c))
                move_possibles.push_back(c);

            else
            {
                bool a_insecte_environnant = false;
                for (auto j_direction : Case::DIRECTIONS_ALL)
                {
                    if (i_direction != Case::DIRECTION_OPPOSE(j_direction))
                    {
<<<<<<< Updated upstream
                        if (!Case::is_empty(c->case_from_direction(j_direction)))
=======
                        if (!Case::is_empty(c->get_case_from_direction(j_direction)))
>>>>>>> Stashed changes
                        {
                            a_insecte_environnant = true;
                            break;
                        }
                    }
                }

                if (a_insecte_environnant)
                    move_possibles.push_back(c);
            }
        }
    }
}
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
>>>>>>> Stashed changes
