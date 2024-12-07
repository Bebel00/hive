#ifndef ARAIGNEE_H
#define ARAIGNEE_H

#include "insecte.h"

class Araignee : public Insecte
{
public:
    Araignee(Team team);
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles)const   override;
};

#endif // ARAIGNEE_H
