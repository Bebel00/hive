#ifndef PLATEAU_H
#define PLATEAU_H

#include "case.h"
#include "teams.h"
#include <vector>
#include <array>

class Plateau
{
public:
    Plateau();
    ~Plateau();

    void deplacer_insecte(class Case* case_depart, class Case* case_fin);

    bool placer_insecte(class Case* c, class Insecte* insecte, Team team, bool bypass_check = false);

    /*
     * Fonction qui potentiellement supprime une case si elle n'a plus aucun voisin avec un insecte.
     */
    bool verifier_suppression_case(class Case* c) const;

    /*
     * Fonction qui crée les cases alentours à une case
     * Renvoie true si tout s'est bien passé.
     */
    bool creer_alentours(class Case* c);

    /*
     * Fonction dont la valeur de retour est mise dans adjacence.
     *
     * Adjacence est une matrice (9 x 5)
     * L'élément central est la case en paramètre (case_base) dont on cherche les cases adjacentes
     * Et l'élément 2 cases au dessus est la case qui serait au dessus dans le jeu par exemple.
     */
    void explorer_adjacence_2(std::array<std::array<Case*, 9>, 5>& adjacence, Case* case_base);

    Case* get_case_base() const { return case_base; }

private:
    Case* case_base;
    std::vector<Case*> liste_cases;

    bool tenter_supprimer_case(Case* c);

    constexpr static float echelle_plateau = 10.0;

protected:
    void paintEvent(class QPaintEvent *event);
};

#endif // PLATEAU_H
