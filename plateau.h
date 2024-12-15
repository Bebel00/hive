#ifndef PLATEAU_H
#define PLATEAU_H

#include "case.h"
#include <vector>
#include <array>
#include "types.h"

class Plateau
{
public:
    Plateau(size_t nb_retour_possible=0);
    ~Plateau();

    friend class GraphicsPlateau;

    void deplacer_insecte(class Case* case_depart, class Case* case_fin, bool undo = 0);

    bool placer_insecte(class Case* c, std::unique_ptr<Insecte> insecte, class Joueur& joueur, bool bypass_check = false);

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

    Case* get_case_base() const  { return case_base; }
    Case* get_case(QPoint p) const { for (auto c : liste_cases) if (p == c->get_position()) return c; return nullptr; }

    const std::vector<Case*>& get_cases() const { return liste_cases; }
    Insecte* get_dernier_deplacement_pion() const;

    void annuler_deplacement();
    void retirer_piece_sur_case(Case* c);

private:
    Case* case_base;
    std::vector<Case*> liste_cases;

    bool tenter_supprimer_case(Case* c);

    void add_case(Case* c);

    //On stocke le dernier déplacement afin de pouvoir retourner en arrière
    std::vector<Insecte *> dernier_deplacement_pion;
    std::vector<Case*> dernier_deplacement_debut;
    std::vector<Case*> dernier_deplacement_fin;
    size_t nb_retour_possible;

    void retirer_insecte(Case* c);

public:
    std::unique_ptr<class GraphicsPlateau> graphics;
};

#endif // PLATEAU_H
