#ifndef SCARABE_H
#define SCARABE_H

#include "insecte.h"

class Scarabe : public Insecte
{
public:
    Scarabe(Team team);

    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;

    virtual Type get_type() const override { return Type::SCARABE; }
    virtual std::string get_chemin_icone() const override { return ""; }
};

#endif // SCARABE_H
