#ifndef PARTIE_H
#define PARTIE_H

#include "joueur.h"
#include "partie.h"
#include <vector>

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo);
    ~Partie();

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Team tour;

    std::vector<class Insecte*> insectes;

    template<typename T_Insecte>
    void ajouter_insecte(Team team, class Case* c);
};

#endif // PARTIE_H
