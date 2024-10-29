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

    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
};

#endif // ABEILLE_H
