#include "case.h"
#include "directions.h"
#include <iostream>
#include <vector>

Case::Case()
{

}

bool Case::creer_case(Directions direction)
{
    Case** case_a_creer = case_ptr_from_direction(direction);
    if (!case_a_creer)
    {
        std::cout << "La case à créer n'existe pas." << std::endl;
        return false;
    }
    if (*case_a_creer)
    {
        std::cout << "La case à créer existe déjà" << std::endl;
    }
    *case_a_creer = new Case;
    if (!*case_a_creer)
    {
        std::cout << "Impossible de créer une nouvelle case." << std::endl;
        return false;
    }
    return true;
}

const Case* Case::case_from_direction(Directions direction) const
{
    Case* case_cherchee = nullptr;

    switch (direction)
    {
    case Directions::HAUT_DROIT:
        case_cherchee = haut_droit;
        break;
    case Directions::DROITE:
        case_cherchee = droite;
        break;
    case Directions::BAS_DROIT:
        case_cherchee = bas_droit;
        break;
    case Directions::HAUT_GAUCHE:
        case_cherchee = haut_gauche;
        break;
    case Directions::GAUCHE:
        case_cherchee = gauche;
        break;
    case Directions::BAS_GAUCHE:
        case_cherchee = bas_droit;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

Case** Case::case_ptr_from_direction(Directions direction)
{
    Case** case_cherchee = nullptr;

    switch (direction)
    {
    case Directions::HAUT_DROIT:
        case_cherchee = &haut_droit;
        break;
    case Directions::DROITE:
        case_cherchee = &droite;
        break;
    case Directions::BAS_DROIT:
        case_cherchee = &bas_droit;
        break;
    case Directions::HAUT_GAUCHE:
        case_cherchee = &haut_gauche;
        break;
    case Directions::GAUCHE:
        case_cherchee = &gauche;
        break;
    case Directions::BAS_GAUCHE:
        case_cherchee = &bas_droit;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

bool Case::creer_alentours()
{
    // On boucle sur toutes les directions
    for (auto i_direction : DIRECTIONS_ALL)
    {
        // On regarde si la case peut bel et bien être trouvée
        Case** const i_case = case_ptr_from_direction(i_direction);
        if (!i_case)
        {
            std::cout << "Création alentours : impossible de créer une case." << std::endl;
            return false;
        }

        // Ensuite, si la case est vide, on créer une case
        if (!*i_case)
        {
            // On vérifie bien sûr que la création se passe bien
            if (!creer_case(i_direction))
                return false;
        }
    }
    return true;
}

Case **Case::get_toutes_cases()
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
}
