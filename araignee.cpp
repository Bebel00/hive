#include "araignee.h"
#include "insecte.h"
#include "teams.h"
#include "plateau.h"
#include "usineinsecte.h"
#include <iostream>

Araignee::Araignee(Team team) : Insecte(team)
{

}




void Araignee::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
    int i=0;
    int j=0;
    int k=0;
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases())){
        for (auto i_direction : Case::DIRECTIONS_ALL){
            Case* c1 = get_case()->get_case_from_direction(i_direction);
            i++;
            if (c1!=nullptr && Case::is_empty(c1)&& est_un_glissement(get_case(),i_direction,get_case())){
                for (auto j_direction : Case::DIRECTIONS_ALL){
                    j++;
                    Case* c2 = c1->get_case_from_direction(j_direction);

                    if (c2!=nullptr &&Case::is_empty(c2)&& j_direction!=Case::DIRECTION_OPPOSE(i_direction) && est_un_glissement(c1,j_direction,get_case())){
                        for(auto k_direction : Case::DIRECTIONS_ALL){
                            k++;
                            Case* c3 = c2->get_case_from_direction(k_direction);

                            if (c3!=nullptr && Case::is_empty(c3)&& k_direction!=Case::DIRECTION_OPPOSE(j_direction) && est_un_glissement(c2,k_direction,get_case())&& c3!=get_case()){
                                moves_possibles.push_back(c3);
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout<<"1 :"<<i<<"\n";
    std::cout<<"2 :"<<j<<"\n";
    std::cout<<"3 :"<<k<<"\n";

}
bool Araignee::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::ARAIGNEE, [](Team team) {
    return std::make_unique<Araignee>(team);
});
