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
    partie->set_tour_suivant();
    return 1;
}


int NoeudIA::appliquer_move_inverse(Partie* partie){
    if(type_action == TypeAction::PLACE){
        partie->get_plateau()->annuler_placement_insecte(case_fin,partie);
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
    partie->set_tour_suivant();
    return 1;
}


//on estime qu'une bonne situation est une situation où on a beaucoup de choix de déplacements et peu d'insectes autour de notre reine
int IA::evaluation_poids(Plateau* plateau){
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
                somme_points -= 1_000_000;
            }
            else{
                somme_points += 1_000_000;
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


NoeudIA* IA::constituer_arbre(Partie* partie,int etage=0, NoeudIA* pere=nullptr, TypeAction type_action=TypeAction::NONE, Type::Type type_insecte = Type::Type::NONE, Case* case_debut = nullptr, Case* case_fin = nullptr){
    NoeudIA* racine = &NoeudIA(pere, type_action, type_insecte, case_debut, case_fin);
    racine->appliquer_move(partie);
    if (etage==profondeur){
        racine->set_poids(evaluationPoids(partie->get_plateau()));
    }
    else {
        Joueur * joueur;
        if(partie->get_tour()==partie->get_joueur1()->get_team()){
            joueur = partie->get_joueur1();
        }
        else{
            joueur = partie->get_joueur2();
        }
        for(auto i_case : partie->get_plateau()->get_cases()){
            if(i_case->get_pion()==nullptr){
                if(Insecte::verifier_placement(i_case,partie->get_tour())){
                    for(auto i_type: joueur->get_jetons()){
                        if(joueur->get_jetons()[i_type]>0){
                            racine->ajouter_fils(constituer_arbre(partie,etage+1, racine, TypeAction::PLACE, i_type,nullptr,i_case));
                        }
                    }
                }
            }
            else if(i_case->get_pion()->get_team() == joueur->get_team()){
                std::vector<Case*> move_possibles;
                i_case->get_pion()->get_moves_possibles(move_possibles);
                for(Case * i_case_move : move_possibles){
                    racine->ajouter_fils(constituer_arbre(partie,etage+1, racine, TypeAction::MOVE, Type::Type::NONE,i_case,i_case_move));
                }
            }
        }
        if(team != partie->get_tour()){ //dans le cas ou c'est à l'IA de choisir, on prend le meilleur coup
            int max = -2_000_000;
            for(NoeudIA* i_noeud: racine->get_liste_fils()){
                if(i_noeud->get_poids()>max){
                    max=i_noeud->get_poids();
                }
            }
            racine->set_poids(max);
        }
        else{ //dans le cas ou c'est au joeur de choisir, on estime qu'il va choisir le meilleur coup pour lui et donc le pire pour nous
            int min = 2_000_000;
            for(NoeudIA* i_noeud: racine->get_liste_fils()){
                if(i_noeud->get_poids()<min){
                    min=i_noeud->get_poids();
                }
            }
            racine->set_poids(min);
        }
    }
    racine->appliquer_move_inverse(partie);
    return racine;
}


void IA::jouer_tour(Partie* partie, TypeAction type_action_precedente = TypeAction::NONE, Type::Type type_insecte_precedent = Type::Type::NONE,
                    Case* case_debut_precedente = nullptr, Case* case_fin_precedente = nullptr){
    if(racine_Arbre==nullptr){
        racine_Arbre = constituer_arbre(partie);
    }
    else{
        racine_Arbre = reconstituer_arbre(partie, type_action_precedente, type_insecte_precedent, case_debut_precedente, case_fin_precedente);
    }
    for(NoeudIA* i_noeud: racine_Arbre->get_liste_fils()){
        if(i_noeud->get_poids()== racine_Arbre->get_poids()){
            i_noeud->appliquer_move(partie);
            break;
        }
    }
}



















