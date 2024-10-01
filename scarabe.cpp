#include "scarabe.h"
#include "insecte.h"
#include "case.h"

Scarabe::Scarabe(Team team) : Insecte(team)
{

}

void Scarabe::get_moves_possibles(std::vector<Case *> &move_possibles,Plateau* p) const
{
    if (!move_casse_ruche(p->get_case_base(),get_case(),p))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case* c = get_case()->get_case_from_direction(i_direction);

            if (!Case::is_empty(c))
                move_possibles.push_back(c);

            else
            {
                bool a_insecte_environnant = false;
                for (auto j_direction : Case::DIRECTIONS_ALL)
                {
                    if (i_direction != Case::DIRECTION_OPPOSE(j_direction))
                    {
                        if (!Case::is_empty(c->get_case_from_direction(j_direction)))
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
