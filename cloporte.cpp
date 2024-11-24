#include "cloporte.h"
#include "insecte.h"
#include "teams.h"

Cloporte::Cloporte(Team team) : Insecte(team)
{

}


void Cloporte::get_moves_possibles(std::vector<Case*>& moves_possibles) const{
    // Est ce que la pièce est déjà positionné ?
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case* c = get_case()->get_case_from_direction(i_direction);
            if (Case::is_empty(c))
            {
                // Nous devons vérifier que chaque déplacement possible est un glissement et non pas un saut.
                bool a_insecte_environnant = false;
                for (auto j_direction : Case::DIRECTIONS_ALL)
                {
                    if (i_direction != Case::DIRECTION_OPPOSE(j_direction)) // Nous vérifions que nous ne faisons pas de demi tour.
                    {
                        if (!Case::is_empty(c->get_case_from_direction(j_direction)))
                        {
                            a_insecte_environnant = true;
                            break;
                        }
                    }
                }
                if (a_insecte_environnant)
                    moves_possibles.push_back(c);
            }
        }
    }

}

void Cloporte::get_pion_deplacer(std::vector<Insecte *> &pions_deplacer){
    for (auto i_direction: Case::DIRECTIONS_ALL){
        /* Nous devons vérifier que
         * La case dans la direction i possède un pion
         * Qu'il n'y a pas de pion en dessous de celui-ci
         * Et que le déplacement de ce pion ne détruit pas la ruche
         * Et qu'enfin ce pion ne soit pas le dernier à avoir été déplacer
         */
        Case* c = get_case()->get_case_from_direction(i_direction);
        if((c->possede_pion()) && (c->get_pion()->get_en_dessous()==nullptr) && (!move_casse_ruche(c,c->get_plateau()->get_cases())) &&(c->get_pion()!=c->get_plateau()->get_dernier_deplacement()))
            pions_deplacer.push_back(c->get_pion());
    }
}

void Cloporte::get_moves_possibles_pions_ennemis(std::vector<Case *> &move_possibles){
    for (auto i_direction: Case::DIRECTIONS_ALL){
        Case* c = get_case()->get_case_from_direction(i_direction);
        if(!c->possede_pion()){
            move_possibles.push_back(c);
        }
    }
}


