#ifndef SCARABE_H
#define SCARABE_H

#include "insecte.h"

class Scarabe : public Insecte
{
public:
    Scarabe(class Joueur* joueur);

    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;

    virtual Type::Type get_type() const override { return Type::Type::SCARABE; }
    virtual std::string get_chemin_icone() const override { return ""; }

    static bool enregistre;
};

#endif // SCARABE_H
