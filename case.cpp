
#include "case.h"
#include "insecte.h"
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

Position Case::direction_to_position_increment(Direction direction)
{
    switch(direction)
    {
    case Direction::HAUT_DROIT:
        return Position(1, 1);
        break;
    case Direction::DROITE:
        return Position(2, 0);
        break;
    case Direction::BAS_DROIT:
        return Position(1, -1);
        break;
    case Direction::HAUT_GAUCHE:
        return Position(-1, 1);
        break;
    case Direction::GAUCHE:
        return Position(-2, 0);
        break;
    case Direction::BAS_GAUCHE:
        return Position(-1, -1);
        break;
    default:
        return Position(0, 0);
    }
}

Case::Case(Position position) : position(position)
{

}

Case* Case::creer_case(Direction direction)
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
    *case_a_creer = new Case(position + direction_to_position_increment(direction));
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
        case_cherchee = bas_droit;
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
        case_cherchee = &bas_droit;
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

void Case::set_visite(bool v){
    if (v){
        visite=true;
    } else{
        visite=false;
    }
}

/*Case **Case::get_toutes_cases()
{
    std::vector<Case*> cases;



    // On remet le flag de visite à 0
    for (auto& i_case : cases)
        cases->visite = false;

    return cases.data();
}

void Case::get_toutes_cases_recursif(std::vector<Case *> &cases, Case* case_a_visiter)
{
    if (case_a_visiter)
    {
        case_a_visiter->visite = true;
        cases.push_back(case_a_visiter);
    }
    else
    {
        std::cout << "Une case nullptr a été visitée. (Ca ne devrait pas arriver)" << std::endl;
    }
    if (!Case::is_empty(case_a_visiter))
    {
        for (auto i_direction : DIRECTIONS_ALL)
        {
            Case* i_case = case_a_visiter->case_from_direction(i_direction);
            if (i_case != nullptr)
            {
                if (i_case->visite == false)
                    get_toutes_cases_recursif(cases, i_case);
            }
        }
    }
}*/

// Pour l'instant on aura sûrement pas besoin de ça en fait
