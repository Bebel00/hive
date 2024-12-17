#include "fourmi.h"
#include "plateau.h"
#include "usineinsecte.h"

Fourmi::Fourmi(class Joueur* joueur) : Insecte(joueur)
{

}


void Fourmi::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
}


bool Fourmi::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::FOURMI, [](Joueur* joueur) {
    return std::make_unique<Fourmi>(joueur);
});
