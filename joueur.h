#ifndef JOUEUR_H
#define JOUEUR_H

#include "teams.h"
#include <string>
#include <unordered_map>
#include "types.h"

class Joueur
{
public:
    Joueur(Team team, std::string pseudo);
    Joueur() { }

    std::string pseudo;

    bool a_place_abeille = false;

    // Renvoie -1 s'il n'y a plus d
    int placer(Type::Type type)
    {
        return -1;
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
