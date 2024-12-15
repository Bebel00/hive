#include "fourmi.h"
#include "teams.h"
#include "plateau.h"
#include "usineinsecte.h"

Fourmi::Fourmi(Team team) : Insecte(team)
{

}


void Fourmi::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
}


bool Fourmi::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::FOURMI, [](Team team) {
    return std::make_unique<Fourmi>(team);
});
