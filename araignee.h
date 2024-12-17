
#ifndef ARAIGNEE_H
#define ARAIGNEE_H

#include "insecte.h"
#include <vector>

class Araignee : public Insecte {
public:
    Araignee(Team team);
    virtual Type::Type get_type() const override { return Type::Type::ARAIGNEE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;
    virtual int get_jetons_max() const override { return 2; }
};

#endif // ARAIGNEE_H
