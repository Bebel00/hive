#ifndef SAUTERELLE_H
#define SAUTERELLE_H

#include "insecte.h"

class Sauterelle : public Insecte
{
public:
    Sauterelle(Team team);
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles,Plateau* p) const override;

private :
    Case* get_case_au_bout_direction(Case::Direction direction) const;
};

#endif // SAUTERELLE_H
