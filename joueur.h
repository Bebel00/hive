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

    bool peut_utiliser(Type::Type type) const;
    const std::string& get_pseudo() const { return pseudo; }
    const bool& get_a_place_abeille() const { return a_place_abeille; }
    const Team& get_team() const { return team; }

private:
    Team team;

    std::unordered_map<Type::Type, unsigned int> jetons;

    bool a_place_abeille = false;

    const std::string pseudo;

    int getJetonsMax(Type::Type type) const;
};

#endif // JOUEUR_H
