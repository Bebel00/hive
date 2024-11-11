#ifndef COCCINELLE_H
#define COCCINELLE_H

#include "insecte.h"

class Coccinelle : public Insecte
{
public:
    Coccinelle(Team team);


    virtual Type get_type() const override { return Type::COCCINELLE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
};

#endif // COCCINELLE_H
