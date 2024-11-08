#include "sauterelle.h"
#include "insecte.h"
#include <vector>
#include <stdexcept>

Sauterelle::Sauterelle(Team team) : Insecte(team)
{

}

Case* Sauterelle::get_case_au_bout_direction(Case::Direction direction) const
{
    // Fonction qui permet d'obtenir la dernière case se trouvant sur une ligne droite
    Case* c = get_case();


    while (c->get_case_from_direction(direction) != nullptr)
    {
        c = c->get_case_from_direction(direction);
    }

    return c;
}


void Sauterelle::get_moves_possibles(std::vector<Case*>& moves_possibles) const
{
    // Est ce que la pièce est déjà positionné ?
    if (get_case()==nullptr)
    {
        throw std::logic_error("L'Insecte n'est pas encore positionné");
    }

    else if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            if (!Case::is_empty(get_case()->get_case_from_direction(i_direction)))
            {
                moves_possibles.push_back(get_case_au_bout_direction(i_direction));
            }
        }
    }
}

bool Sauterelle::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::SAUTERELLE, [](Team team) {
    return std::make_unique<Sauterelle>(team);
});
