#ifndef SAUTERELLE_H
#define SAUTERELLE_H

#include "insecte.h"

class Sauterelle : public Insecte
{
    public:
        Sauterelle(Team team);
        std::vector<const Case*> get_moves_possibles();
    private :
        const Case* get_moves_possibles_direction(Case::Direction direction);
};

#endif // SAUTERELLE_H
