#ifndef ABEILLE_H
#define ABEILLE_H

#include "insecte.h"

class Abeille : public Insecte
{
public:
    Abeille(Team team);

    virtual std::vector<Case*> get_moves_possibles(bool start = false) override;
    virtual bool verifier_move(const Case* const c, bool start = false) const override;

    virtual std::vector<Case*> get_placements_possibles(bool start = false) override;
    virtual bool verifier_placement(const Plateau* plateau, bool start = false) const override;
};

#endif // ABEILLE_H
