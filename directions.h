#ifndef DIRECTIONS_H
#define DIRECTIONS_H

enum class Directions
{
    HAUT_DROIT,
    DROITE,
    BAS_DROIT,
    HAUT_GAUCHE,
    GAUCHE,
    BAS_GAUCHE
};

constexpr Directions DIRECTIONS_ALL[] =
{ Directions::HAUT_DROIT, Directions::DROITE, Directions::BAS_DROIT, Directions::HAUT_GAUCHE, Directions::GAUCHE, Directions::BAS_GAUCHE };

#endif // DIRECTIONS_H
