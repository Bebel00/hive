#ifndef ABEILLE_H
#define ABEILLE_H

#include "insecte.h"
#include "types.h"

#include <vector>

class Abeille : public Insecte
{
public:
    Abeille(class Joueur* joueur);
    /*
     * Fonctions qui définissent l'identité d'un pion
     */
    virtual Type::Type get_type() const override { return Type::Type::ABEILLE; }
    virtual std::string get_chemin_icone() const override { return ""; }
    virtual void get_moves_possibles(std::vector<Case *> &move_possibles) const override;

    static bool enregistre;
};


#endif // ABEILLE_H
