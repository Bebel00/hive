#include "abeille.h"
#include "insecte.h"
#include "teams.h"
#include "usineinsecte.h"

Abeille::Abeille(Team team) : Insecte(team)
{

}

void Abeille::get_moves_possibles(std::vector<Case *> &move_possibles) const
{
    if (!move_casse_ruche(get_case(), get_case()->get_plateau()->get_cases()))
    {
        for (auto i_direction : Case::DIRECTIONS_ALL)
        {
            Case* c = get_case()->get_case_from_direction(i_direction);
            if (Case::is_empty(c))
            {
                bool a_insecte_environnant = false;
                for (auto j_direction : Case::DIRECTIONS_ALL)
                {
                    if (i_direction != Case::DIRECTION_OPPOSE(j_direction))
                    {
                        if (!Case::is_empty(c->get_case_from_direction(j_direction)))
                        {
                            a_insecte_environnant = true;
                            break;
                        }
                    }
                }
                if (a_insecte_environnant)
                    move_possibles.push_back(c);
            }
        }
    }
}

bool Abeille::enregistre = UsineInsecte::get_usine().enregistrer_type(Type::Type::ABEILLE, [](Team team) {
    return std::make_unique<Abeille>(team);
});
