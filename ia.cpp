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


//on estime qu'une bonne situation est une situation où on a beaucoup de choix de déplacements et peu d'insectes autour de notre reine. Le but de l'IA est de maximiser le poids
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

    for(auto i_abeille : plateau->get_abeilles())
    {
        int nb_insectes_autour = 0;
        for(auto i_direction : Case::DIRECTIONS_ALL)
        {
            if(i_abeille->get_case()->get_case_from_direction(i_direction)!=nullptr)
            {
                nb_insectes_autour++;
            }
        }
        if(nb_insectes_autour == 6)
        {
            if(i_abeille->get_team() == team)
            {
                somme_points -= 1000000;
            }
            else
            {
                somme_points += 1000000;
            }
        }
        else
        {
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


NoeudIA* IA::constituer_arbre(Partie* partie, NoeudIA* racine,int etage /*=1*/){
    racine->appliquer_move(partie);
    if (etage>=profondeur){
        racine->set_poids(evaluation_poids(partie->get_plateau()));
        racine->set_enfants_testes(false);
    }
    else {
        Joueur * joueur;
        if(partie->get_tour()==partie->get_joueur1()->get_team()){
            joueur = partie->get_joueur1();
        }
        else{
            joueur = partie->get_joueur2();
        }
        for(Case* i_case : partie->get_plateau()->get_cases()){
            if(i_case->get_pion()==nullptr){
                if(Insecte::verifier_placement(i_case,partie->get_tour())){
                    for(auto i_umap: joueur->get_jetons()){
                        if(i_umap.second > 0){ //
                            NoeudIA* fils = new NoeudIA(racine, TypeAction::PLACE, i_umap.first,nullptr,i_case);
                            racine->ajouter_fils(constituer_arbre(partie,fils,etage+1));
                        }
                    }
                }
            }
            else if(i_case->get_pion()->get_team() == joueur->get_team()){
                std::vector<Case*> move_possibles;
                i_case->get_pion()->get_moves_possibles(move_possibles);
                for(Case * i_case_move : move_possibles){
                    NoeudIA* fils = new NoeudIA(racine, TypeAction::MOVE, Type::Type::NONE,i_case,i_case_move);
                    racine->ajouter_fils(constituer_arbre(partie,fils,etage+1));
                }
            }
        }
        if(team != partie->get_tour()){ //dans le cas ou c'est à l'IA de choisir, on prend le meilleur coup
            int max = -2000000;
            for(NoeudIA* i_noeud: racine->get_liste_fils()){
                if(i_noeud->get_poids()>max){
                    max=i_noeud->get_poids();
                }
            }
            racine->set_poids(max);
        }
        else{ //dans le cas ou c'est au joeur de choisir, on estime qu'il va choisir le meilleur coup pour lui et donc le pire pour nous
            int min = 2000000;
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


NoeudIA* IA::reconstituer_arbre(Partie* partie, TypeAction type_action_humain /*= TypeAction::NONE*/, Type::Type type_insecte_humain /*= Type::Type::NONE*/,
                    Case* case_debut_humain /*= nullptr*/, Case* case_fin_humain /*= nullptr*/){

    NoeudIA* choixIAPrecedent;
    NoeudIA* choixHumainPrecedent;
    for(NoeudIA * i_noeud : racine_Arbre->get_liste_fils()){
        if(i_noeud->get_poids()==racine_Arbre->get_poids()){
            choixIAPrecedent = i_noeud;
        }
    }
    for(NoeudIA * i_noeud : choixIAPrecedent->get_liste_fils()){
        if(i_noeud->get_type_action()==type_action_humain &&  i_noeud->get_type_insecte()==type_insecte_humain && i_noeud->get_case_debut()==case_debut_humain && i_noeud->get_case_fin()==case_fin_humain){
            choixHumainPrecedent = i_noeud;
        }
    }
    int max = -2000000;
    NoeudIA* nouvelleRacine=nullptr;
    auto it_max = choixHumainPrecedent->get_liste_fils().begin();
    auto it = choixHumainPrecedent->get_liste_fils().begin();
    for(size_t i=0; i<choixHumainPrecedent->get_liste_fils().size(); ++i){
        ++it;
        if(choixHumainPrecedent->get_liste_fils()[i]->get_poids()>max){
            max = choixHumainPrecedent->get_liste_fils()[i]->get_poids();
            nouvelleRacine = choixHumainPrecedent->get_liste_fils()[i];
            it_max=it;
        }
    }

    choixHumainPrecedent->get_liste_fils().erase(it_max);
    nouvelleRacine->set_pere(nullptr);
    delete racine_Arbre;
    return redevelopper_arbre(partie, nouvelleRacine);
}

NoeudIA* IA::redevelopper_arbre(Partie* partie, NoeudIA* racine, int etage /*=1*/){
    if(racine->get_enfants_testes()){
        racine->appliquer_move(partie);
        for(NoeudIA* i_fils : racine->get_liste_fils()){
            redevelopper_arbre(partie, i_fils, etage+1);
        }
        if(team != partie->get_tour()){ //dans le cas ou c'est à l'IA de choisir, on prend le meilleur coup
            int max = -2000000;
            for(NoeudIA* i_noeud: racine->get_liste_fils()){
                if(i_noeud->get_poids()>max){
                    max=i_noeud->get_poids();
                }
            }
            racine->set_poids(max);
        }
        else{ //dans le cas ou c'est au joeur de choisir, on estime qu'il va choisir le meilleur coup pour lui et donc le pire pour nous
            int min = 2000000;
            for(NoeudIA* i_noeud: racine->get_liste_fils()){
                if(i_noeud->get_poids()<min){
                    min=i_noeud->get_poids();
                }
            }
            racine->set_poids(min);
        }
        racine->appliquer_move_inverse(partie);
    }
    else{
        constituer_arbre(partie,racine,etage);
    }
    return racine;
}

void IA::jouer_tour(Partie* partie, TypeAction type_action_humain /*= TypeAction::NONE*/, Type::Type type_insecte_humain /*= Type::Type::NONE*/,
                    Case* case_debut_humain /*= nullptr*/, Case* case_fin_humain /*= nullptr*/){
    if(racine_Arbre==nullptr){
        NoeudIA* racine = new NoeudIA();
        racine_Arbre = constituer_arbre(partie,racine);
    }
    else{
        racine_Arbre = reconstituer_arbre(partie, type_action_humain, type_insecte_humain, case_debut_humain, case_fin_humain);
    }
    for(NoeudIA* i_noeud: racine_Arbre->get_liste_fils()){
        if(i_noeud->get_poids() == racine_Arbre->get_poids()){
            i_noeud->appliquer_move(partie);
            break;
        }
    }
}



















