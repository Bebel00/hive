#include "joueur.h"
#include <string>
#include <stdexcept>
#include <iostream>

Joueur::Joueur(QColor color, std::string pseudo) : color(color), pseudo(std::move(pseudo))
{
    // Initialisation des jetons
    jetons[Type::Type::ABEILLE] = 1;
    jetons[Type::Type::ARAIGNEE] = 2;
    jetons[Type::Type::COCCINELLE] = 1;
    jetons[Type::Type::FOURMI] = 3;
    jetons[Type::Type::SCARABE] = 2;
    jetons[Type::Type::SAUTERELLE] = 2;
}

void Joueur::utiliser(Type::Type type)
{
    if (type == Type::Type::NONE || jetons[type] <= 0)
        return;

    if (type == Type::Type::ABEILLE)
        a_place_abeille = true;

    jetons[type]--;
    std::cout << "Jeton de type " << Type::type_to_str(type) << " utilisé. Restants : " << jetons[type] << std::endl;
}

void Joueur::remettre(Type::Type type)
{
    if (type == Type::Type::ABEILLE)
        a_place_abeille = false;

    jetons[type]++;
    std::cout << "Jeton de type " << Type::type_to_str(type) << " remis. Disponibles : " << jetons[type] << std::endl;
}

void Joueur::afficher_jetons() const
{
    std::cout << "Jetons disponibles pour " << pseudo << " :\n";

    for (const auto& [type, count] : jetons)
        std::cout << "- " << Type::type_to_str(type) << " : " << count << "\n";
}
