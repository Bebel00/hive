#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"
#include "../types.h"

class Fourmi : public Insecte
{
public:
    Fourmi(Team team);
    virtual Type::Type get_type() const override { return Type::Type::FOURMI; }
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;
    virtual std::string get_chemin_icone() const override { return ""; }
private:
    static bool enregistre;
};

#endif // FOURMI_H
