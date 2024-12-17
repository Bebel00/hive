#ifndef SCARABE_H
#define SCARABE_H

#include "insecte.h"

class Scarabe : public Insecte
{
public:
    Scarabe(Team team);

    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;

    virtual Type::Type get_type() const override { return Type::Type::SCARABE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual int get_jetons_max() const override { return 2; }

    static bool enregistre;
};

#endif // SCARABE_H
