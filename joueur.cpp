#include "joueur.h"
#include "teams.h"
#include <string>

Joueur::Joueur(Team team, std::string pseudo) : team(team), pseudo(pseudo)
{
    jetons[Type::Type::ABEILLE] = 1;
    jetons[Type::Type::ARAIGNEE] = 2;
    jetons[Type::Type::COCCINELLE] = 1;
    jetons[Type::Type::FOURMI] = 3;
    jetons[Type::Type::SCARABE] = 1;
    jetons[Type::Type::SAUTERELLE] = 2;
    jetons[Type::Type::SCARABE] = 2;
}

void Joueur::utiliser(Type::Type type)
{
    if (type != Type::Type::NONE && jetons[type] > 0)
    {
        if (type == Type::Type::ABEILLE)
            a_place_abeille = true;

        jetons[type]--;
    }
}
