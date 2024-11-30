#include "fourmi.h"
#include "teams.h"
#include "plateau.h"

Fourmi::Fourmi(Team team) : Insecte(team)
{

}


void Fourmi::get_moves_possibles(std::vector<Case*>& moves_possibles) const{
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases())){
        int size_cases=moves_possibles.size();
        int i=0;
        Case* c=nullptr;
        for (auto i_direction : Case::DIRECTIONS_ALL){
            c=get_case()->get_case_from_direction(i_direction);
            if (Case::is_empty(c)&& est_un_glissement(get_case(),i_direction)){
                moves_possibles.push_back(c);
            }
        }
            // On cherche dans un premier temps les glissements possibles sur des cases adjacentes à la case actuelle de la fourmie
        while(moves_possibles.size()!=size_cases){ // tant que l'on trouve d'autre case sur lesquelles on peut se déplacer
            size_cases=moves_possibles.size();
            for (i;i<size_cases;i++){ // On va chercher les glissements possibles sur les cases ajouté à la dernière boucle while
                for (auto i_direction : Case::DIRECTIONS_ALL){
                    c=moves_possibles[i]->get_case_from_direction(i_direction);
                    if (Case::is_empty(c)&& est_un_glissement(moves_possibles[i],i_direction) &&std::find(moves_possibles.begin(),moves_possibles.end(),c)!=moves_possibles.end()){
                        moves_possibles.push_back(c);
                    }
                }
            }
        }
    }

}
