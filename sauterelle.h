#ifndef SAUTERELLE_H
#define SAUTERELLE_H

#include "insecte.h"

class Sauterelle : public Insecte
{
public:
    Sauterelle(Team team);
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;

    virtual Type get_type() const override { return Type::SAUTERELLE; }
    virtual std::string get_chemin_icone() const override { return ""; }

private:
    Case* get_case_au_bout_direction(Case::Direction direction) const;
};

#endif // SAUTERELLE_H
