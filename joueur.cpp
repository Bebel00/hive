#include "joueur.h"
#include "teams.h"
#include <string>
#include <stdexcept>
#include <iostream>

Joueur::Joueur(Team team, std::string pseudo) : team(team), pseudo(std::move(pseudo)) {
    // récupère le type de l'insecte et le nombre de jetons max associé 
    
    jetons[Type::Type::ABEILLE] = UsineInsecte::get_usine().get_jetons_max(Type::Type::ABEILLE);
    jetons[Type::Type::ARAIGNEE] = UsineInsecte::get_usine().get_jetons_max(Type::Type::ARAIGNEE);
    jetons[Type::Type::COCCINELLE] = UsineInsecte::get_usine().get_jetons_max(Type::Type::COCCINELLE);
    jetons[Type::Type::FOURMI] = UsineInsecte::get_usine().get_jetons_max(Type::Type::FOURMI);
    jetons[Type::Type::SCARABE] = UsineInsecte::get_usine().get_jetons_max(Type::Type::SCARABE);
    jetons[Type::Type::SAUTERELLE] = UsineInsecte::get_usine().get_jetons_max(Type::Type::SAUTERELLE);
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
    return UsineInsecte::get_usine().get_jetons_max(type);
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
