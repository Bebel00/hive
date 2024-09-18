#ifndef CASE_H
#define CASE_H

#include "directions.h"
#include "insecte.h"
#include "teams.h"
#include <vector>

class Case
{
public:
    Case();

    /*
     *  Fonction qui sert à vérifier si une case est nulle
     *  On utilise une fonction statique pour l'utiliser même on a une case nullptr
     *  Par exemple pour faire Case::is_empty(case->droite).
     *  Ce qui ne marcherait pas avec case->droite->is_empty().
     */
    static bool is_empty(const class Case* const c)
    {
        // Si la case n'est pas nullptr on regarde si son pion n'est pas nullptr
        if (c)
            // Pas de pion (pion nullptr) <=> case vide
            return c->pion;

        // Si la case est nullptr, on considère que c'est comme si c'était une case vide
        return false;
    }

    /*
     *  Fonction qui crée une  nouvelle case.
     * Elle vérifie que la création de case se passe bien,
     * et qu'il n'y a pas déjà une case à l'endroit souhaité.
     *
     * Renvoie true si tout s'est bien passé.
     */
    bool creer_case(Directions direction);

    // Fonction qui renvoie le pointeur vers la case dans la direction en paramètre
    const Case* case_from_direction(Directions direction) const;

    /*
     * Fonction qui crée les cases alentours à une case
     * Renvoie true si tout s'est bien passé.
     */
    bool creer_alentours();

    inline bool get_team() { if (pion) return pion->team; else return Team::NULL; }

    Case** get_toutes_cases();

private:
    // Fonction qui renvoie un pointeur le pointeur vers la case dans la direction en paramètre
    class Case** case_ptr_from_direction(Directions direction);

    /*
     * Les 6 côtés de l'hexagone
     * La classe est une sorte de liste chaînée
     */
    class Case* haut_droit = nullptr;
    class Case* haut_gauche = nullptr;
    class Case* droite = nullptr;
    class Case* gauche = nullptr;
    class Case* bas_droit = nullptr;
    class Case* bas_gauche = nullptr;

    // Pion qui occupe la case
    Insecte* pion = nullptr;

    // Variable qui sert à voir si une case est visitée ou non
    bool visite = false;

    // Fonction récusrive qui renvoie la liste des cases créées en mémoire
    void get_toutes_cases_recursif(std::vector<Case *> &cases, Case* case_a_visiter);
};

#endif // CASE_H
