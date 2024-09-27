#ifndef INSECTE_H
#define INSECTE_H

#include <string>
#include <vector>
#include "case.h"
#include "teams.h"
#include "types.h"

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
    virtual std::vector<const Case*> get_moves_possibles() = 0;
    virtual bool verifier_move(Case* const c) const = 0;

    // Fonction qui met la liste des placements possibles dans "placements_possibles" (la valeur de retour)
    void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team) const;

    static bool verifier_placement(Case* const c, const Team team);

    bool placer(Case* const c);
    bool bouger(Case* const c);

    // Getter pour la case
    const Case* get_case() { return position; }

    Team get_team() { return team; }

private:
    // BLANC ou NOIR
    Team team;

    Case* position;
};

#endif // INSECTE_H
