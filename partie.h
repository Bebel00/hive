#ifndef PARTIE_H
#define PARTIE_H

#include "joueur.h"

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo);
    ~Partie();

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;
};

#endif // PARTIE_H
