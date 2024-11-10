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
    inline const Team get_tour() {return tour;}

    std::string jouer_tour_cli(std::string cmd);

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Team tour = Team::BLANC;

    std::vector<class Insecte*> insectes;

    bool ajouter_insecte(Team team, class Case* c, Type::Type type, bool bypass = false);

    std::string get_display_plateau() const;

    class QGraphicsView* view;

    void lire_prochain_token(std::string& cmd, std::string& token);

    void setup_test();
};

#endif // PARTIE_H
