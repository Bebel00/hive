#include "fourmi.h"
#include "insecte.h"
#include "teams.h"

Fourmi::Fourmi(Team team) : Insecte(team)
{

}


void Fourmi::get_moves_possibles(std::vector<Case*>& moves_possibles) const{
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases())){
        std::set<Case *> cases; // On utilise un set pour éviter d'avoir des doublons.
        int size_cases=0;
        int i=0;

        Insecte::get_glissements_possibles(*get_case(),cases); // On cherche dans un premier temps les glissements possibles sur des cases adjacentes à la case actuelle de la fourmie
        while(cases.size()!=size_cases){ // tant que l'on trouve d'autre case sur lesquelles on peut se déplacer
            auto it = cases.begin();
            size_cases=cases.size();
            for (i;i<size_cases;i++){ // On va chercher les glissements possibles sur les cases ajouté à la dernière boucle while
                std::advance(it,i);
                get_glissements_possibles(**it,cases,get_case());
            }
        }
        if (cases.size()!=0){
            // On va transverser les données du set dans moves_possibles
            moves_possibles.clear();
            moves_possibles.insert(moves_possibles.end(), cases.begin(), cases.end());
        }
    }

}
