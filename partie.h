#ifndef PARTIE_H
#define PARTIE_H

#include "joueur.h"
#include "plateau.h"
#include "insecte.h"
#include <vector>
#include <string>
#include "mainwindow.h"

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo);
    ~Partie();

    class Plateau* get_plateau() const { return plateau; }
    class QGraphicsView* get_view() const { return view; }
    bool verifier_victoire();

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Team tour;

    std::vector<class Insecte*> insectes;

    template<typename T_Insecte>
    void ajouter_insecte(Team team, class Case* c);

    bool verifier_victoire_joueur(const Joueur& joueur);

    class QGraphicsView* view;
};

#endif // PARTIE_H
