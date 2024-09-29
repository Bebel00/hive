#include "partie.h"

#include "teams.h"
#include "plateau.h"

Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo)
{
    plateau = new Plateau();

    joueur1 = Joueur(Team::BLANC, joueur1_pseudo);
    joueur2 = Joueur(Team::NOIR, joueur2_pseudo);
}

Partie::~Partie()
{
    delete plateau;
}
