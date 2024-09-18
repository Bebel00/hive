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
    virtual inline Type get_type() = 0;
    virtual inline std::string get_chemin_icone() = 0;

    /*
     * Fonctions qui gèrent les véfifications et possibilités de mouvement
     * Et de placement du pion
     * Le placement est quand on met le pion sur le plateau pour la première fois
     */
    virtual std::vector<Case*> get_moves_possibles(bool start = false) = 0;
    virtual bool verifier_move(Case* const c) const = 0;

    static Case** get_placements_possibles();
    static bool verifier_placement(Case* const c, const Team team);

    bool placer(Case* const c);
    bool bouger(Case* const c);

    // Getter pour la case
    inline Case* getCase() { return position; }

private:
    // BLANC ou NOIR
    Team team;

    Case** get_placements_possibles_recursif(std::vector& );

    Case* position;
};

#endif // INSECTE_H
