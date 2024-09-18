#ifndef PARTIE_H
#define PARTIE_H

#include "joueur.h"

class Partie
{
public:
    Partie(std::string joueur1, std::string joueur2);
    ~Partie();

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;
};

#endif // PARTIE_H
