#ifndef JOUEUR_H
#define JOUEUR_H

#include "teams.h"
#include <string>

class Joueur
{
public:
    Joueur(Team team, std::string pseudo);

    std::string pseudo;

    template<typename T>
    void utiliser()
    {
        switch (typeid(T))
        {

        }
    }

private:
    Team team;

    unsigned char n_abeilles = 1;
    unsigned char n_araignees = 2;
    unsigned char n_coccinelles = 1;
    unsigned char n_fourmis = 3;
    unsigned char n_moustique = 1;
    unsigned char n_sauterelle = 2;
    unsigned char n_scarabe = 2;
};

#endif // JOUEUR_H
