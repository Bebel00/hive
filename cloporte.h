#ifndef CLOPORTE_H
#define CLOPORTE_H


#include "insecte.h"
#include "types.h"

#include <vector>

class Cloporte : public Insecte
{
public:
    Cloporte(Team team);
    /*
     * Fonctions qui définissent l'identité d'un pion
     */
    virtual Type::Type get_type() const override { return Type::Type::CLOPORTE; }
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;
    void get_pion_deplacer(std::vector<Insecte *> &pions_deplacer); // Méthode permettant de connaître les pions que l'on peut déplacer
    void get_moves_possibles_pions_ennemis(std::vector<Case *> &move_possibles); // Méthode permettant d'obtenir les cases sur lesquels on peut déplacer un pion adjacent

};


#endif // CLOPORTE_H
