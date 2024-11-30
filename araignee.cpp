#include "araignee.h"
#include "insecte.h"
#include "teams.h"
#include "plateau.h"

Araignee::Araignee(Team team) : Insecte(team)
{

}




void Araignee::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases())){
        for (auto i_direction : Case::DIRECTIONS_ALL){
            Case* c1 = get_case()->get_case_from_direction(i_direction);
            if (Case::is_empty(c1)&& est_un_glissement(get_case(),i_direction)){
                for (auto j_direction : Case::DIRECTIONS_ALL){
                    Case* c2 = c1->get_case_from_direction(i_direction);
                    if (Case::is_empty(c2)&& j_direction!=Case::DIRECTION_OPPOSE(i_direction) && est_un_glissement(c1,j_direction)){
                        for(auto k_direction : Case::DIRECTIONS_ALL){
                            Case* c3 = get_case()->get_case_from_direction(i_direction);
                            if (Case::is_empty(c3)&& k_direction!=Case::DIRECTION_OPPOSE(j_direction) && est_un_glissement(c2,k_direction)&& c3!=get_case()){
                                moves_possibles.push_back(c3);
                            }
                        }
                    }
                }
            }
        }

    }

}
