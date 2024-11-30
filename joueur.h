#ifndef JOUEUR_H
#define JOUEUR_H

#include "teams.h"
#include "types.h"

#include <string>
#include <unordered_map>
#include <iostream>

class Joueur
{
public:
    Joueur(Team team, std::string pseudo);

    void utiliser(Type::Type type);
    void remettre(Type::Type type);

    bool peut_utiliser(Type::Type type) const;
    const std::string& getPseudo() const;
    bool estAbeillePlacee() const;
    Team getTeam() const;
    void afficherJetons() const;

private:
    Team team;

    std::unordered_map<Type::Type, unsigned int> jetons;

    bool a_place_abeille = false;

    const std::string pseudo;

    int getJetonsMax(Type::Type type) const;
};

#endif // JOUEUR_H
