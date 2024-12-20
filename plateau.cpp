#include "plateau.h"
#include "case.h"
#include "insecte.h"
#include "joueur.h"

#include <iostream>
#include <array>    // pour std::array une liste
#include <cstdlib>  // pour abs() la valeur absolue
#include <algorithm> // pour std::find trouver un élément dans une liste
#include <stdexcept>

#include "graphicsplateau.h"

Plateau::Plateau()
{
    case_base = new Case(QPoint(0, 0), this);

    add_case(case_base);

    creer_alentours(case_base);
}

Plateau::~Plateau()
{
    // On supprime toutes les cases
    for (auto c : liste_cases)
    {
        delete c;
    }

}

void Plateau::deplacer_insecte(Case *case_depart, Case *case_fin)
{
    if (case_fin)
    {
        std::unique_ptr<Insecte> pion = std::move(case_depart->pion);

        pion->bouger(case_fin);
        case_fin->pion = std::move(pion);
        creer_alentours(case_fin);

        if (case_depart->pion == nullptr)
        {
            for (auto i_direction : Case::DIRECTIONS_ALL)
            {
                tenter_supprimer_case(*(case_depart->case_ptr_from_direction(i_direction)));
            }
        }
    }
}

bool Plateau::placer_insecte(Case *c, std::unique_ptr<Insecte> insecte, Joueur& joueur, bool bypass_check)
{
    if (Insecte::verifier_placement(c, joueur.get_team()) || bypass_check)
    {
        c->pion = std::move(insecte);
        creer_alentours(c);
        c->pion->placer(c);

        joueur.utiliser(c->pion->get_type());

        if (graphics && c->graphics)
            graphics->placer_insecte(c->graphics.get(), joueur.get_team());

        return true;
    }
    return false;
}


bool Plateau::verifier_suppression_case(Case *c) const
{
    // Si une case possède un pion on ne peut pas la supprimer
    if (c->possede_pion())
        return false;

    // Si toutes les cases adjacentes sont vides (donc soient nullptr soient elles ne contiennent pas d'insecte
    // Alors on peut supprimer la case
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {
        if (!Case::is_empty(c->get_case_from_direction(i_direction)))
            return false;
    }

    return true;
}

/*
 * Fonction qui crée les cases autour d'une autre case.
 *
 * Il faut bien comprendre que dans le jeu on crée toujours une nouvelle case DEPUIS une autre case.
 * En fait le jeu doit fonctionner par création petit à petit de cases alentours.
 *
 * C'est-à-dire que quand on crée une nouvelle case, elle est par défaut vide.
 * Puis quand un insecte arrive dessus, il faut créer les cases alentours,
 * pour les rendre sélectionnables quand on veut bouger un insecte sur ces emplacements.
 *
 * Tout le jeu fonctionne comme ça : au fur et à mesure qu'on place des insectes sur le plateau,
 * le nombre de cases que l'on peut sélectionner augmente, et ces cases sont créées par cette fonction creer_alentours().
 *
 * Comme le jeu fonctionne par une liste chaînée avec 6 maillons par case,
 * Il faut faire attention à ce que quand on crée une case au dessus d'une autre par exemple,
 * Il n'y en ait pas déjà une qui existe. Pour ça, on vérifie simplement si c->haut_droit ou c->haut_gauche est défini ou non.
 *
 * Mais pour que ça fonctionne il faut que les pointeurs soient bien définis. Sauf que y a des cas compliqués :
 * Si je crée une case à droite, et qu'il y a une case à droite de la nouvelle case que je viens de créer,
 * comment je lie le pointeur nouvelle_case->droite à cette case anciennement présente ?
 *
 * Pour ça il faut chercher s'il y a une case à droite de la nouvelle case.
 * Du coup le système de Position (avec x, y) a été implémenté pour rechercher une case selon sa position.
 *
 * Et on utilise la fonction adjacence() pour obtenir la liste des cases dans un rayon de 2 pour que ce soit plus simple.
 * La fonction est vraiment très simple : elle parcourt la liste des cases (stockée dans liste_cases),
 * Et si d'après sa Position elle est dans un rayon de 2 on la met dans la valeur de retour,
 * qui est une matrice 9x5 représentant une carte des alentours d'une case.
 *
 * Pourquoi 9x5 ? Parce qu'aller à droite fait bouger de 2 vers la droite en x (et gauche -2 en x)
 * Et on peut pas aller en haut directement, donc on peut pas bouger de 2 vers le haut directement
 * on est obligé d'aller en haut à droite puis en haut à gauche pour aller vers le haut.
 * Donc un "rayon de 2" en fait c'est 9 cases possibles (en comptant le centre) en x,
 * et 5 cases possibles (en comptant le centre) en y.
 *
 * Grâce à cette carte on peut tout simplement bien lier toutes les cases entre elles,
 * et bel et bien crée les alentours d'une case pour qu'elle soit prête à être sélectionnée.
 */
bool Plateau::creer_alentours(Case* c)
{
    // On crée la carte des cases sur un rayon de 2
    std::array<std::array<Case*, 9>, 5> adjacence;

    explorer_adjacence_2(adjacence, c);

    // Les incréments de position vont permettre de travailler sur des cases dont on calculera la position
    // En ajoutant un incrément de position qui est équivalent à bouger dans une direction
    QPoint increment_position;
    QPoint increment_position_2;

    // La position de la case depuis laquelle on crée les alentours est au centre de la matrice adjacence, donc (4, 2)
    QPoint case_base_pos(4, 2);

    // On boucle sur toutes les directions pour créer une nouvelle case dans chaque direction
    for (auto i_direction : Case::DIRECTIONS_ALL)
    {
        increment_position = Case::direction_to_position_increment(i_direction);

        *(c->case_ptr_from_direction(i_direction)) =
            adjacence[case_base_pos.y() + increment_position.y()][case_base_pos.x() + increment_position.x()];

        // On récupère le pointeur vers le pointeur vers la case dans la direction actuelle
        // Double pointeur pour pouvoir changer la valeur du pointeur case_droite par exemple,
        // Sans double pointeur ça ferait juste une copie du pointeur et on travaillerait sur la copie
        Case** const i_case = c->case_ptr_from_direction(i_direction);

        // Juste au cas où
        if (!i_case)
        {
            std::cout << "Création alentours : impossible de créer une case, problème de direction." << std::endl;
            return false;
        }

        // Ensuite, si la case est vide, on créer une case
        if (!*i_case)
        {
            Case* nouvelle_case = c->creer_case(i_direction, this);

            // On vérifie bien sûr que la création se passe bien
            if (!nouvelle_case)
            {
                return false;
            }

            // Si la création s'est bien passée on ajoute la case à la liste des cases
            add_case(nouvelle_case);
            adjacence[case_base_pos.y() + increment_position.y()][case_base_pos.x() + increment_position.x()] = nouvelle_case;

            // Et là c'est de la magie noire

            // Maintenant qu'on a créé une nouvelle case dans une des directions
            // On va regarder depuis cette nouvelle case toutes les cases qui sont autour
            // Grâce à la matrice adjacence

            // Et on s'occupe de bien mettre les pointeurs pour lier les cases entre elles.

            // L'incrément de position pour aller à la nouvelle case depuis la case de base
            increment_position = Case::direction_to_position_increment(i_direction);

            for (auto j_direction : Case::DIRECTIONS_ALL)
            {
                // L'incrément de position pour aller à la case observée depuis la nouvelle case
                increment_position_2 = Case::direction_to_position_increment(j_direction);

                // La position finale de la case observée
                QPoint position_finale = case_base_pos + increment_position + increment_position_2;

                // Son pointeur
                Case* const case_finale = adjacence[position_finale.y()][position_finale.x()];

                // On initialise le pointeur dans la direction donnée et on le fait pointer vers la case finale observée
                (*(nouvelle_case->case_ptr_from_direction(j_direction))) = case_finale;

                if (case_finale)
                    (*(case_finale->case_ptr_from_direction(Case::DIRECTION_OPPOSE(j_direction)))) = nouvelle_case;
            }
        }
    }
    return true;
}

/*
 * Parcourt la liste des cases et renvoie une matrice correspondant à une carte
 * Des cases dans un rayon de 2 d'une case (case_base) passée en paramètre
 *
 * adjacence est sa valeur de retour
 */
void Plateau::explorer_adjacence_2(std::array<std::array<Case *, 9>, 5> &adjacence, Case *case_base)
{
    for (int i{0}; i < 5; i++)
        for (int j{0}; j < 9; j++)
            adjacence[i][j] = nullptr;

    for (auto i_case : liste_cases)
    {
        if (abs(i_case->get_position().x() - case_base->get_position().x()) <= 4)
            if (abs(i_case->get_position().y() - case_base->get_position().y()) <= 2)
            {
                const int x = i_case->get_position().x() - case_base->get_position().x() + 4;
                const int y = i_case->get_position().y() - case_base->get_position().y() + 2;
                adjacence[y][x] = i_case;
            }
    }
}

bool Plateau::tenter_supprimer_case(Case *c)
{
    if (!c)
        return true;

    if (verifier_suppression_case(c))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case** const case_adjacente = c->case_ptr_from_direction(i_direction);

            // Ligne compliquée mais elle fait un truc tout simple
            // Déjà elle s'exécute que s'il y a une case adjacente pour la direction i_direction
            // Et si c'est le cas,
            // Elle remplace le pointeur qui pointe vers la case actuelle par nullptr comme on va la supprimer
            // On utilise la direction opposé pour revenir à la case actuelle du coup

            if (case_adjacente)
                *((*(case_adjacente))->case_ptr_from_direction(Case::DIRECTION_OPPOSE(i_direction))) = nullptr;
        }

        const auto index = std::find(liste_cases.begin(), liste_cases.end(), c);
        if (index != liste_cases.end())
        {
            liste_cases.erase(index);
        }
        else
        {
            throw std::logic_error("Suppression d'une case pas dans la liste de cases, pas normal.");
        }

        delete c;
        return true;
    }
    return false;
}

void Plateau::add_case(Case *c)
{
    liste_cases.push_back(c);

    if (graphics)
        graphics->add_case(c);
}
