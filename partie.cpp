#include "partie.h"
#include "abeille.h"
#include "teams.h"
#include "plateau.h"
#include "insecte.h"


Partie::Partie(std::string joueur1_pseudo, std::string joueur2_pseudo)
{
    plateau = new Plateau();

    joueur1 = Joueur(Team::BLANC, joueur1_pseudo);
    joueur2 = Joueur(Team::NOIR, joueur2_pseudo);

    ajouter_insecte<Abeille>(Team::NOIR, plateau->get_case_base());
    ajouter_insecte<Abeille>(Team::BLANC, plateau->get_case_base()->get_case_from_direction(Case::Direction::DROITE));
}

Partie::~Partie()
{
    for (auto& i_insecte : insectes)
        delete i_insecte;

    delete plateau;
}

template<typename T_Insecte>
void Partie::ajouter_insecte(Team team, Case* c)
{
    // La fonction ne marche que pour des sous-types d'insecte
    static_assert(std::is_base_of<Insecte, T_Insecte>::value);

    T_Insecte* insecte = new T_Insecte(team);
    plateau->placer_insecte(c, insecte, team);
}
