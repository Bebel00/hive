#include "araignee.h"
#include "insecte.h"
#include "teams.h"
#include "case.h"
#include "plateau.h"
#include "usineinsecte.h"

#include <set>

void Araignee::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
    // Est ce que la pièce est déjà positionné ?
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases()))
    {
        std::vector<Case*> case1;
        std::vector<int> case1_r;
        std::set<Case*> case2;
        int size_case2=0;
        std::set<Case*> case3;
        int i=0;

        get_glissements_possibles(*get_case(),case1);
        for(int j=0;j<case1.size();j++){
            get_glissements_possibles(*case1[j],case2,get_case());
            for(int k=0; k<case2.size()-size_case2;k++){
                case1_r.push_back(i);
            }
            size_case2=case2.size();
            i++;
        }
        i=0;
        for (const auto& case_j: case2){
            get_glissements_possibles(*case_j,case3,case1[case1_r[i]]);
            i++;
        }
        case3.erase(get_case());
        moves_possibles.clear();
        moves_possibles.insert(moves_possibles.end(), case3.begin(), case3.end());
    }

}
