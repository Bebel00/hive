#include "moustique.h"
#include "usineinsecte.h"
#include "insecte.h"

Moustique::Moustique(Joueur* joueur) : Insecte(joueur)
{

}

void Moustique::get_moves_possibles(std::vector<Case *> &move_possibles) const
{
    if (!move_casse_ruche(get_case()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case* c = get_case()->get_case_from_direction(i_direction);

            if (!Case::is_empty(c))
            {
                std::unique_ptr<Insecte> i = UsineInsecte::get_usine().fabriquer(c->get_pion()->get_type(), get_joueur());
                i->placer(get_case());
                i->get_moves_possibles(move_possibles);
            }
        }

        std::sort(move_possibles.begin(), move_possibles.end());
        move_possibles.erase(std::unique(move_possibles.begin(), move_possibles.end()), move_possibles.end());
    }
    return;
}
