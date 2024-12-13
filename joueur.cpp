#include "joueur.h"
#include "teams.h"
#include <string>
#include <stdexcept>
#include <iostream>

Joueur::Joueur(Team team, std::string pseudo) : team(team), pseudo(std::move(pseudo)) {
    // Initialisation des jetons
    jetons[Type::Type::ABEILLE] = 1;
    jetons[Type::Type::ARAIGNEE] = 2;
    jetons[Type::Type::COCCINELLE] = 1;
    jetons[Type::Type::FOURMI] = 3;
    jetons[Type::Type::SCARABE] = 2;
    jetons[Type::Type::SAUTERELLE] = 2;
}

void Joueur::utiliser(Type::Type type) {
    if (type == Type::Type::NONE) {
        throw std::invalid_argument("Type d'insecte invalide.");
    }

    if (jetons[type] <= 0) {
        throw std::out_of_range("Aucun jeton disponible pour ce type.");
    }

    if (type == Type::Type::ABEILLE && a_place_abeille) {
        throw std::logic_error("La reine a déjà été placée.");
    }

    if (type == Type::Type::ABEILLE) {
        a_place_abeille = true;
    }

    jetons[type]--;
    std::cout << "Jeton de type " << toString(type) << " utilisé. Restants : " << jetons[type] << std::endl;
}

void Joueur::remettre(Type::Type type) {
    if (type == Type::Type::NONE) {
        throw std::invalid_argument("Type d'insecte invalide.");
    }

    int maxJetons = getJetonsMax(type);
    if (jetons[type] >= maxJetons) {
        throw std::out_of_range("Nombre maximum de jetons atteint pour ce type.");
    }

    if (type == Type::Type::ABEILLE) {
        a_place_abeille = false;
    }

    jetons[type]++;
    std::cout << "Jeton de type " << toString(type) << " remis. Disponibles : " << jetons[type] << std::endl;
}

int Joueur::getJetonsMax(Type::Type type) const {
    switch (type) {
    case Type::Type::ABEILLE:
        return 1;
    case Type::Type::ARAIGNEE:
        return 2;
    case Type::Type::COCCINELLE:
        return 1;
    case Type::Type::FOURMI:
        return 3;
    case Type::Type::SCARABE:
        return 2;
    case Type::Type::SAUTERELLE:
        return 2;
    default:
        throw std::invalid_argument("Type d'insecte invalide.");
    }
}

bool Joueur::peutUtiliser(Type::Type type) const {
    return jetons.count(type) > 0 && jetons.at(type) > 0;
}

void Joueur::afficherJetons() const {
    std::cout << "Jetons disponibles pour " << pseudo << " :\n";
    for (const auto& [type, count] : jetons) {
        std::cout << "- " << toString(type) << " : " << count << "\n";
    }
}

bool Joueur::estAbeillePlacee() const {
    return a_place_abeille;
}

std::string Joueur::getPseudo() const {
    return pseudo;
}

Team Joueur::getTeam() const {
    return team;
}
