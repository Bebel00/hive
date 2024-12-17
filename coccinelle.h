#ifndef COCCINELLE_H
#define COCCINELLE_H

#include "insecte.h"
#include "types.h"

class Coccinelle : public Insecte
{
public:
    Coccinelle(Team team);


    virtual Type::Type get_type() const override { return Type::Type::COCCINELLE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
    virtual int get_jetons_max() const override { return 1; }
};

#endif // COCCINELLE_H
