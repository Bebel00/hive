
#include "case.h"
#include "insecte.h"
#include "graphicscase.h"

#include <iostream>

Case::Direction Case::DIRECTION_OPPOSE(Direction direction)
{
    switch(direction)
    {
    case Direction::HAUT_DROIT:
        return Direction::BAS_GAUCHE;
        break;
    case Direction::DROITE:
        return Direction::GAUCHE;
        break;
    case Direction::BAS_DROIT:
        return Direction::HAUT_GAUCHE;
        break;
    case Direction::HAUT_GAUCHE:
        return Direction::BAS_DROIT;
        break;
    case Direction::GAUCHE:
        return Direction::DROITE;
        break;
    case Direction::BAS_GAUCHE:
        return Direction::HAUT_DROIT;
        break;
    default:
        return Direction::NONE;
    }
}

QPoint Case::direction_to_position_increment(Direction direction)
{
    switch(direction)
    {
    case Direction::HAUT_DROIT:
        return QPoint(1, 1);
        break;
    case Direction::DROITE:
        return QPoint(2, 0);
        break;
    case Direction::BAS_DROIT:
        return QPoint(1, -1);
        break;
    case Direction::HAUT_GAUCHE:
        return QPoint(-1, 1);
        break;
    case Direction::GAUCHE:
        return QPoint(-2, 0);
        break;
    case Direction::BAS_GAUCHE:
        return QPoint(-1, -1);
        break;
    default:
        return QPoint(0, 0);
    }
}

Case::Case(QPoint position, Plateau *plateau) : position(position), plateau(plateau)
{
    pion = nullptr;
}

Case* Case::creer_case(Direction direction, Plateau* const plateau)
{
    Case** case_a_creer = case_ptr_from_direction(direction);

    if (!case_a_creer)
    {
        std::cout << "Erreur dans la direction de la case à créer" << std::endl;
        return nullptr;
    }
    if (*case_a_creer)
    {
        std::cout << "La case à créer existe déjà" << std::endl;
        return nullptr;
    }
    *case_a_creer = new Case(position + direction_to_position_increment(direction), plateau);

    if (!*case_a_creer)
    {
        std::cout << "Impossible de créer une nouvelle case." << std::endl;
        return nullptr;
    }
    return *case_a_creer;
}

Case* Case::get_case_from_direction(Direction direction) const
{
    Case* case_cherchee = nullptr;

    switch (direction)
    {
    case Direction::HAUT_DROIT:
        case_cherchee = haut_droit;
        break;
    case Direction::DROITE:
        case_cherchee = droite;
        break;
    case Direction::BAS_DROIT:
        case_cherchee = bas_droit;
        break;
    case Direction::HAUT_GAUCHE:
        case_cherchee = haut_gauche;
        break;
    case Direction::GAUCHE:
        case_cherchee = gauche;
        break;
    case Direction::BAS_GAUCHE:
        case_cherchee = bas_gauche;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

Case** Case::case_ptr_from_direction(Direction direction)
{
    Case** case_cherchee = nullptr;

    switch (direction)
    {
    case Direction::HAUT_DROIT:
        case_cherchee = &haut_droit;
        break;
    case Direction::DROITE:
        case_cherchee = &droite;
        break;
    case Direction::BAS_DROIT:
        case_cherchee = &bas_droit;
        break;
    case Direction::HAUT_GAUCHE:
        case_cherchee = &haut_gauche;
        break;
    case Direction::GAUCHE:
        case_cherchee = &gauche;
        break;
    case Direction::BAS_GAUCHE:
        case_cherchee = &bas_gauche;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

Team Case::get_team() const
{
    if (pion) return pion->get_team(); else return Team::NONE;
}

Case::~Case() = default;
