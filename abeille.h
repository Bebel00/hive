#ifndef ABEILLE_H
#define ABEILLE_H

#include "insecte.h"
#include <vector>

class Abeille : public Insecte
{
public:
    Abeille(Team team);

    /*
     * Fonctions qui définissent l'identité d'un pion
     */
    virtual Type get_type() const override { return Type::ABEILLE; }

    virtual std::string get_chemin_icone() const override { return ""; }

    /*
     * Fonctions qui gèrent les véfifications et possibilités de mouvement
     * Et de placement du pion
     * Le placement est quand on met le pion sur le plateau pour la première fois
     */
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
    virtual bool verifier_move(const Case* const c) const override { return true; }
};

#endif // ABEILLE_H
