#include "fourmi.h"
#include "teams.h"
#include "usineinsecte.h"

Fourmi::Fourmi(Team team) : Insecte(team)
{

}


void Fourmi::get_moves_possibles(std::vector<Case*>& moves_possibles) const{
    if (!move_casse_ruche(get_case()))
    {
        unsigned int size_cases = moves_possibles.size();

        Case* c = nullptr;

        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            c = get_case()->get_case_from_direction(i_direction);
            if (Case::is_empty(c) && est_un_glissement(get_case(), i_direction, get_case()))
            {
                moves_possibles.push_back(c);
            }
        }

        // On cherche dans un premier temps les glissements possibles sur des cases adjacentes à la case actuelle de la fourmie
        while(moves_possibles.size() != size_cases)
        {
            // tant que l'on trouve d'autre case sur lesquelles on peut se déplacer

            size_cases=moves_possibles.size();

            for (unsigned int i{0}; i < size_cases; i++)
            {
                // On va chercher les glissements possibles sur les cases ajouté à la dernière boucle while
                for (auto i_direction : Case::DIRECTIONS_ALL)
                {
                    c=moves_possibles[i]->get_case_from_direction(i_direction);

                    if (c!=nullptr &&Case::is_empty(c)&& est_un_glissement(moves_possibles[i],i_direction,get_case())
                        && std::find(moves_possibles.begin(),moves_possibles.end(),c)==moves_possibles.end())
                    {
                        moves_possibles.push_back(c);
                    }
                }
            }

        }
    }
}

bool Fourmi::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::FOURMI, [](Team team) {
    return std::make_unique<Fourmi>(team);
});
