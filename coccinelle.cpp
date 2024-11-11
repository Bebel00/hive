#include "coccinelle.h"
#include "insecte.h"
#include "teams.h"

Coccinelle::Coccinelle(Team team) : Insecte(team)
{
}

void Coccinelle::get_moves_possibles(std::vector<Case*> &move_possibles) const
{
    if (!move_casse_ruche(get_case()))
        for (auto dir1 : Case::DIRECTIONS_ALL) {
            Case* case1 = get_case()->get_case_from_direction(dir1);

            if (!Case::is_empty(case1)) {
                for (auto dir2 : Case::DIRECTIONS_ALL) {

                    Case* case2 = case1->get_case_from_direction(dir2);

                    if (!Case::is_empty(case2)) {
                        for (auto dir3 : Case::DIRECTIONS_ALL) {

                            Case* case_finale = case2->get_case_from_direction(dir3);

                            if (case_finale && Case::is_empty(case_finale) && case_finale != get_case())
                            {
                                if (std::find(move_possibles.begin(), move_possibles.end(), case_finale) == move_possibles.end())
                                    move_possibles.push_back(case_finale);
                            }
                        }
                    }
                }
            }
        }
}
