
#include "insecte.h"
#include "case.h"
#include <vector>
#include "plateau.h"

Insecte::Insecte(Team team) : team(team)
{

}

void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team)
{
    for (auto i_case : liste_cases)
        if (Insecte::verifier_placement(i_case, team))
            placements_possibles.push_back(i_case);
}

bool Insecte::verifier_placement(const Case * const c, const Team team)
{
    // Est-ce qu'il existe un allié adjacent ?
    bool a_allie = false;

    // Pour chaque direction on vérifie le contenu de la case
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {

        // La case pour la direction actuelle
        const Case* c_direction = c->get_case_from_direction(i_direction);

        // Est-ce que la case est vide ?
        bool is_empty = Case::is_empty(c_direction);

        // Si la case n'est pas vide on regarde son contenu
        if (!is_empty)
        {
            if (c_direction->get_team() == team)
                // il y a un allié
                a_allie = true;


            else
                // il y a un ennemi : impossible de placer
                return false;
        }
    }

    // Une fois toutes les directions vérifiées, on regarde si il y a bien un allié adjacent pour placer le pion
    return a_allie;
}

// Méthode récursive permettant d'obtenir le nombre de pions que l'on peut rejoindre à partir de la case de départ
void Insecte::compter_nb_insecte_connecte( Case * const case_depart, const Case* supprime, unsigned int* nb_trouve ){
    case_depart->set_visite(true);
    if (case_depart->possede_pion()){
        *nb_trouve+=1;
    }
    // Pour chaque direction on vérifie si la case n'st pas null, si la case n'est pas déjà visité et si la case n'est pas celle que l'on souhaite supprimé
    if (case_depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE)->get_visite() && case_depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE), supprime, nb_trouve);
    }
    if (case_depart->get_case_from_direction(Case::Direction::HAUT_DROIT)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::HAUT_DROIT)->get_visite() && case_depart->get_case_from_direction(Case::Direction::HAUT_DROIT)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::HAUT_DROIT), supprime, nb_trouve);
    }
    if (case_depart->get_case_from_direction(Case::Direction::GAUCHE)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::GAUCHE)->get_visite() && case_depart->get_case_from_direction(Case::Direction::GAUCHE)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::GAUCHE), supprime, nb_trouve);
    }
    if (case_depart->get_case_from_direction(Case::Direction::DROITE)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::DROITE)->get_visite() && case_depart->get_case_from_direction(Case::Direction::DROITE)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::DROITE), supprime, nb_trouve);
    }
    if (case_depart->get_case_from_direction(Case::Direction::BAS_GAUCHE)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::BAS_GAUCHE)->get_visite() && case_depart->get_case_from_direction(Case::Direction::BAS_GAUCHE)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::BAS_GAUCHE), supprime, nb_trouve);
    }
    if (case_depart->get_case_from_direction(Case::Direction::BAS_DROIT)!=nullptr && !case_depart->get_case_from_direction(Case::Direction::BAS_DROIT)->get_visite() && case_depart->get_case_from_direction(Case::Direction::BAS_DROIT)!=supprime ){
        compter_nb_insecte_connecte(case_depart->get_case_from_direction(Case::Direction::BAS_DROIT), supprime, nb_trouve);
    }

}



// To do
bool Insecte::move_casse_ruche( Case * const case_depart, const Case* supprime,  Plateau * p )
{
    unsigned int nb_trouve=0;
    unsigned int* pt_nb_trouve=&nb_trouve;
    compter_nb_insecte_connecte(case_depart, supprime, pt_nb_trouve);
    p->remettre_visite_faux(); // On remet pour toutes les cases l'attribut visite à false
    if (nb_trouve==p->get_nb_pions() -1){ // Si on a trouvé tous les autres pions sur le plateau alors la ruche n'est pas cassé.
        return true;
    }

    return false;
}


bool Insecte::placer(Case * const c, Plateau* p)
{
    // On vérifie le placement, s'il est bon, on place le pion
    if (verifier_placement(c, team))
    {
        position = c;
        p->ajouter_pion();
        return true;
    }
    else
    {
        return false;
    }
}

bool Insecte::bouger(Case* const c)
{
    if (verifier_move(c))
    {
        position = c;
        return true;
    }
    return false;
}
