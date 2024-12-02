#include "insecte.h"
#include "case.h"
#include <vector>
#include <stdexcept>
#include "plateau.h"

Insecte::Insecte(Team team) : team(team)
{

}

void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team)
{
    for (auto i_case : liste_cases)
        if (Insecte::verifier_placement(i_case, team))
            placements_possibles.push_back(i_case);
}

bool Insecte::verifier_placement(const Case * const c, const Team team)
{
    if (c->get_plateau()->get_cases().size() == 1 && c == c->get_plateau()->get_case_base())
        return true;

    if (c->get_plateau()->get_cases().size() == 7 && c != c->get_plateau()->get_case_base())
        return true;

    // Est-ce qu'il existe un allié adjacent ?
    bool a_allie = false;

    // Pour chaque direction on vérifie le contenu de la case
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {

        // La case pour la direction actuelle
        const Case* c_direction = c->get_case_from_direction(i_direction);

        // Est-ce que la case est vide ?
        bool is_empty = Case::is_empty(c_direction);

        // Si la case n'est pas vide on regarde son contenu
        if (!is_empty)
        {
            if (c_direction->get_team() == team)
                // il y a un allié
                a_allie = true;


            else
                // il y a un ennemi : impossible de placer
                return false;
        }
    }

    // Une fois toutes les directions vérifiées, on regarde si il y a bien un allié adjacent pour placer le pion
    return a_allie;
}

// Méthode récursive permettant d'obtenir le nombre de pions que l'on peut rejoindre à partir de la case de départ
void Insecte::compter_nb_insecte_connecte(Case * const case_depart, unsigned int& nb_trouve)
{
    case_depart->visite = true;
    nb_trouve += 1;

    // Pour chaque direction on vérifie si la case n'est pas vide,
    // et si la case n'est pas déjà visitée

    for (auto i_direction : Case::DIRECTIONS_ALL)
    {
        auto i_case = case_depart->get_case_from_direction(i_direction);
        if (!Case::is_empty(i_case) && !i_case->visite)
            compter_nb_insecte_connecte(i_case, nb_trouve);
    }
}

/*
 * Fonction qui vérifie si le fait de bouger un pion ne casse pas la ruche.
 * Pour ça on vérifie qu'en enlevant le pion de la case passée en paramètre,
 * on peut toujours atteindre tous les pions de la ruche.
 */
bool Insecte::move_casse_ruche(Case * const case_depart)
{
    const std::vector<Case*>& liste_cases = case_depart->get_plateau()->get_cases();

    if (Case::is_empty(case_depart))
        throw std::invalid_argument("Move casse ruche : impossible de bouger une case vide.");

    if (case_depart->get_pion()->get_en_dessous())
        return false;

    // On enlève le pion pour voir ce qu'il se passe
    std::unique_ptr<Insecte> insecte = std::move(case_depart->pion);
    case_depart->pion = nullptr;

    unsigned int nb_trouve = 0;
    unsigned int nb_pions = 0;

    // On part d'un pion voisin au hasard, le premier trouvé,
    // pour tenter d'atteindre tous les pions.
    for (auto i_direction : Case::DIRECTIONS_ALL)
        if (!Case::is_empty(case_depart->get_case_from_direction(i_direction)))
        {
            compter_nb_insecte_connecte(case_depart->get_case_from_direction(i_direction), nb_trouve);
            break;
        }

    // On remet pour toutes les cases l'attribut visite à false
    for (auto i_case : liste_cases)
    {
        if (i_case->possede_pion())
            nb_pions++;

        i_case->visite = false;
    }

    // On remet le pion à sa place
    case_depart->pion = std::move(insecte);

    // Si on a trouvé tous les autres pions sur le plateau alors la ruche n'est pas cassé.
    if (nb_trouve == nb_pions)
    {
        return false;
    }

    return true;
}

bool Insecte::move_trop_serre(Case* depart, Case::Direction d)
{
    switch (d)
    {
    case(Case::Direction::HAUT_DROIT):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE))
                && !Case::is_empty(depart->get_case_from_direction(Case::Direction::DROITE));
    case(Case::Direction::DROITE):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::HAUT_DROIT))
               && !Case::is_empty(depart->get_case_from_direction(Case::Direction::BAS_DROIT));
    case(Case::Direction::BAS_DROIT):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::DROITE))
               && !Case::is_empty(depart->get_case_from_direction(Case::Direction::BAS_GAUCHE));
    case(Case::Direction::BAS_GAUCHE):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::BAS_DROIT))
               && !Case::is_empty(depart->get_case_from_direction(Case::Direction::GAUCHE));
    case(Case::Direction::GAUCHE):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::HAUT_GAUCHE))
               && !Case::is_empty(depart->get_case_from_direction(Case::Direction::BAS_GAUCHE));
    case(Case::Direction::HAUT_GAUCHE):
        return !Case::is_empty(depart->get_case_from_direction(Case::Direction::HAUT_DROIT))
               && !Case::is_empty(depart->get_case_from_direction(Case::Direction::GAUCHE));
    default:
        return false;
    }
}

void Insecte::placer(Case * const c)
{
    // La vérification du placement se fera au niveau du plateau
    position = c;
}

void Insecte::bouger(Case* const c)
{
    position->pion = std::move(en_dessous);

    position = c;
    if (c->possede_pion())
        en_dessous = std::move(c->pion);
}

bool Insecte::est_cerne() const
{
    for (auto i_direction : Case::DIRECTIONS_ALL)
        if (Case::is_empty(get_case()->get_case_from_direction(i_direction)))
            return false;
    return true;
}
