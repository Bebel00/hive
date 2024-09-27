#include "sauterelle.h"
#include "insecte.h"
#include <vector>

Sauterelle::Sauterelle(Team team) : Insecte(team)
{

}

const Case* Sauterelle::get_moves_possibles_direction(Case::Direction direction){ // Fonction qui permet d'obtenir la dernière case se trouvant sur une ligne droite
    const Case*  c =this->get_case() ;
    c=c->case_from_direction(Case::Direction::HAUT_DROIT);
    while (c->case_from_direction(Case::Direction::HAUT_DROIT)!=nullptr){
        c=c->case_from_direction(Case::Direction::HAUT_DROIT);
    }
    return c;
}


std::vector<const Case*> Sauterelle::get_moves_possibles(){
    if(this->get_case()==nullptr){ // Est ce que la pièce est déjà positionné ?
        throw "L'Insecte n'est pas encore positionné";
    }
    else{
        std::vector<const Case* > d_possibles;
        if (this->get_case()->case_from_direction(Case::Direction::HAUT_DROIT)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        if (this->get_case()->case_from_direction(Case::Direction::HAUT_GAUCHE)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        if (this->get_case()->case_from_direction(Case::Direction::DROITE)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        if (this->get_case()->case_from_direction(Case::Direction::GAUCHE)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        if (this->get_case()->case_from_direction(Case::Direction::BAS_DROIT)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        if (this->get_case()->case_from_direction(Case::Direction::BAS_GAUCHE)!=nullptr){
            d_possibles.push_back(this->get_moves_possibles_direction(Case::Direction::HAUT_DROIT));
        }
        return d_possibles;
    }

}


