#ifndef JOUEUR_H
#define JOUEUR_H

#include "types.h"

#include <string>
#include <unordered_map>

#include <QColor>

class Joueur
{
public:
    Joueur(QColor color, std::string pseudo);

    void utiliser(Type::Type type);
    void remettre(Type::Type type);

    bool peut_utiliser(Type::Type type) const { return (type == Type::Type::NONE) ? false : (jetons.find(type) != jetons.end()) && (jetons.find(type)->second > 0); }
    bool est_abeille_placee() const;

    std::string get_pseudo() const { return pseudo; }
    QColor get_color() const { return color; }

    void afficher_jetons() const;

private:
    QColor color;

    std::unordered_map<Type::Type, unsigned int> jetons;

    bool a_place_abeille = false;

    const std::string pseudo;
};

#endif // JOUEUR_H
