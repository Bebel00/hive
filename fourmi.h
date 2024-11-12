#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"

class Fourmi : public Insecte
{
public:
    Fourmi(Team team);
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;
};

#endif // FOURMI_H
