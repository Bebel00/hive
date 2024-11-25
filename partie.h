#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include "mainwindow.h"
#include "types.h"
#include "joueur.h"

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo);
    ~Partie();

    class Plateau* get_plateau() const { return plateau; }
    class QGraphicsView* get_view() const { return view; }
    inline Team get_tour() const {return tour;}
    inline void set_tour_suivant() {if(tour == Team::BLANC){tour=Team::NOIR;} else if(tour == Team::NOIR){tour = Team::BLANC;} else {tour = Team::NONE;}}

    std::string jouer_tour_cli(std::string cmd);
    bool ajouter_insecte(Team team, class Case* c, Type::Type type, bool bypass = false);

    Joueur* get_joueur1() {return &joueur1;}
    Joueur* get_joueur2() {return &joueur2;}

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Team tour = Team::BLANC;

    std::string get_display_plateau() const;

    class QGraphicsView* view;

    void lire_prochain_token(std::string& cmd, std::string& token);

    void setup_test();
};

#endif // PARTIE_H
