#include "ia.h"

int NoeudIA::appliquer_move(Partie* partie){
    if(type_action == TypeAction::PLACE){
        if (!partie->ajouter_insecte(partie->get_tour(), case_fin, type_insecte))
        {

            std::cout << "Placement invalide";
        }
        else{
            return 0;
        }
    }
    else if(type_action == TypeAction::MOVE){
        if (case_debut!= nullptr && case_debut->get_pion()->get_team() == partie->get_tour())
        {
            std::vector<Case*> move_possibles;
            case_debut->get_pion()->get_moves_possibles(move_possibles);
            if (std::find(move_possibles.begin(), move_possibles.end(), case_fin) != move_possibles.end())
            {
                partie->get_plateau()->deplacer_insecte(case_debut->get_pion()->get_case(), case_fin);
                return 0;
            }
            else
            {
                std::cout << "Movement illegal";
            }
        }
        else
        {
            std::cout << "Ce n'est pas le tour de ce pion";
        }
    }
    else if(type_action == TypeAction::NONE){
        return 0;
    }
    else{
        std::cout << "type d'action inconnue";
    }
    return 1;
}


int NoeudIA::appliquer_move_inverse(Partie* partie){
    if(type_action == TypeAction::PLACE){
        partie->get_plateau()->annuler_placement_insecte(case_fin);
        return 0;
    }
    else if(type_action == TypeAction::MOVE){
        partie->get_plateau()->deplacer_insecte(case_fin->get_pion()->get_case(), case_debut);
        return 0;
    }
    else if(type_action == TypeAction::NONE){
        return 0;
    }
    else {
        std::cout << "type d'action inconnue";
    }
    return 1;
}


//on estime qu'une bonne situation est une situation où on a beaucoup de choix de déplacements et peu d'insectes autour de notre reine
int IA::evaluationPoids(Plateau* plateau){
    int somme_points=0;
    std::vector<Case *> moves_possibles;
    //prise en compte du nombre de choix de déplacements
    for(auto i_case : plateau->get_cases()){
        if (i_case->get_pion()!=nullptr){
            i_case->get_pion()->get_moves_possibles(moves_possibles);
            if(i_case->get_pion()->get_team() == team){
                somme_points += moves_possibles.size();
            }
            else{
                somme_points -= moves_possibles.size();
            }
        }
    }
    //prise en compte du nombre d'insectes autour de notre reine

    for(auto i_abeille : plateau->get_abeilles()){
        int nb_insectes_autour = 0;
        for(auto i_direction : Case::DIRECTIONS_ALL){
            if(i_abeille->get_case()->get_case_from_direction(i_direction)!=nullptr){
                nb_insectes_autour++;
            }
        }
        if(nb_insectes_autour = 6){
            if(i_abeille->get_team() == team){
                somme_points -= 2_000_000;
            }
            else{
                somme_points += 2_000_000;
            }
        }
        else{
            if(i_abeille->get_team() == team){
                somme_points -= (10*nb_insectes_autour+nb_insectes_autour*2);
            }
            else{
                somme_points += 10*nb_insectes_autour+nb_insectes_autour*2;
            }
        }
    }
    return somme_points;
}


void IA::constituerArbre(Partie* partie){
    NoeudIA racine;
    for(int etage = 1; etage<profondeur ;etage++){
        // for(auto ){

        // }
    }
}


void IA::jouerTour(Partie* partie){

}



















