#ifndef MOUSTIQUE_H
#define MOUSTIQUE_H

#include "insecte.h"

class Moustique : public Insecte
{
public:
    Moustique(Team team);

    virtual Type::Type get_type() const override { return Type::Type::ABEILLE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
};

#endif // MOUSTIQUE_H
