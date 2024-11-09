#include "coccinelle.h"
#include "insecte.h"
#include "teams.h"

Coccinelle::Coccinelle(Team team) : Insecte(team)
{

Type Coccinelle::get_type() const {
    return Type::COCCINELLE;
}

void Coccinelle::get_moves_possibles(std::vector<Case*> &move_possibles) const
{
    for (auto dir1 : Case::DIRECTIONS_ALL) {
        Case* case1 = get_case()->get_case_from_direction(dir1);

        if (case1 && case1->est_occupee()) {
            for (auto dir2 : Case::DIRECTIONS_ALL) {
                if (dir1 == dir2) continue;

                Case* case2 = case1->get_case_from_direction(dir2);

                if (case2 && case2->est_occupee()) {
                    for (auto dir3 : Case::DIRECTIONS_ALL) {
                        if (dir2 == dir3) continue;

                        Case* case_finale = case2->get_case_from_direction(dir3);

                        if (case_finale && !case_finale->est_occupee() && case_finale != get_case()) {
                            move_possibles.push_back(case_finale);
                        }
                    }
                }
            }
        }
    }
}

}
