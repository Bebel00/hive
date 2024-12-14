#ifndef JOUEUR_H
#define JOUEUR_H

#include "teams.h"
#include "types.h"

#include <string>
#include <unordered_map>

class Joueur
{
public:
    Joueur(Team team, std::string pseudo);

    void utiliser(Type::Type type);
    void remettre(Type::Type type);

    bool peut_utiliser(Type::Type type) const { return (type == Type::Type::NONE) ? false : (jetons.find(type) != jetons.end()) && (jetons.find(type)->second > 0); }
    bool est_abeille_placee() const;

    std::string get_pseudo() const { return pseudo; }
    Team get_team() const { return team; }

    void afficher_jetons() const;

private:
    Team team;

    std::unordered_map<Type::Type, unsigned int> jetons;

    bool a_place_abeille = false;

    const std::string pseudo;
};

#endif // JOUEUR_H
