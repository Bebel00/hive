
#ifndef ARAIGNEE_H
#define ARAIGNEE_H

#include "insecte.h"
#include <vector>

class Araignee : public Insecte {
public:
    Araignee(Team team);
    virtual Type get_type() const override { return Type::ARAIGNEE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const override;
};

#endif // ARAIGNEE_H
