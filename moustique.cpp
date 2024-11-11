#include "moustique.h"
#include "abeille.h"
#include "insecte.h"

Moustique::Moustique(Team team) : Insecte(team)
{

}

void Moustique::get_moves_possibles(std::vector<Case *> &move_possibles) const
{
    // for (auto i_direction : Case::DIRECTIONS_ALL)
    // {
    //     auto* get_move = get_case()->get_case_from_direction()->get_pion()->get_moves_possibles;
    // }
    return;
}
