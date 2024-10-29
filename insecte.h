#ifndef INSECTE_H
#define INSECTE_H

#include <string>
#include <vector>
#include "case.h"
#include "teams.h"
#include "types.h"
#include"plateau.h"

class Insecte
{
public:
    Insecte(Team team);

    /*
     * Fonctions qui définissent l'identité d'un pion
     */
    virtual Type get_type() = 0;
    virtual std::string get_chemin_icone() = 0;

    /*
     * Fonctions qui gèrent les véfifications et possibilités de mouvement
     * Et de placement du pion
     * Le placement est quand on met le pion sur le plateau pour la première fois
     */
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles,Plateau* p) const = 0;
    virtual bool verifier_move(const Case* const c) const = 0;


    // Fonction qui met la liste des placements possibles dans "placements_possibles" (la valeur de retour)
    static void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team);

    static bool verifier_placement(const Case* const c, const Team team);

    bool placer(Case* const c,Plateau* p);
    bool bouger(Case* const c);

    // Getter pour la case
    Case* get_case() const { return position; }

    Team get_team() const { return team; }

    Insecte* get_en_dessous() const { return en_dessous; }

private:
    // BLANC ou NOIR
    Team team;

    Case* position;

    Insecte* en_dessous;

    static bool move_casse_ruche(Case* const case_depart, const std::vector<Case*>& liste_cases);
    static void compter_nb_insecte_connecte(Case* const case_depart, unsigned int& nb_trouve);

    static bool move_trop_serre(Case* depart, Case::Direction d);
};

#endif // INSECTE_H
