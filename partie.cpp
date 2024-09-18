#include "partie.h"

#include "team.h"
#include "plateau.h"

Partie::Partie(std::string joueur1, std::string joueur2)
{
    plateau = new Plateau;

    this->joueur1.pseudo = joueur1;
    this->joueur2.pseudo = joueur2;
}

Partie::~Partie()
{
    delete Plateau;
}
