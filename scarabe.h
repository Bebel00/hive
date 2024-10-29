#ifndef SCARABE_H
#define SCARABE_H

#include "insecte.h"

class Scarabe : public Insecte
{
public:
    Scarabe(Team team);

    virtual void get_moves_possibles(std::vector<Case*>& move_possibles,Plateau* p) const override;
};

#endif // SCARABE_H
