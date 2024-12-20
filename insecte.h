#ifndef INSECTE_H
#define INSECTE_H

#include <string>
#include <vector>
#include "case.h"
#include "teams.h"
#include "types.h"

class Insecte
{
public:
    Insecte(Team team);
    virtual ~Insecte() {}

    /*
     * Fonctions qui définissent l'identité d'un pion
     */
    virtual Type::Type get_type() const = 0;
    virtual std::string get_chemin_icone() const = 0;

    /*
     * Fonctions qui gèrent les véfifications et possibilités de mouvement
     * Et de placement du pion
     * Le placement est quand on met le pion sur le plateau pour la première fois
     */
    virtual void get_moves_possibles(std::vector<Case*>& move_possibles) const = 0;

    // Fonction qui met la liste des placements possibles dans "placements_possibles" (la valeur de retour)
    static void get_placements_possibles(std::vector<Case*>& liste_cases, std::vector<Case*>& placements_possibles, const Team team);

    static bool verifier_placement(const Case* const c, const Team team);

    void placer(Case* const c);
    void bouger(Case* const c);

    // Getter pour la case
    Case* get_case() const { return position; }

    Team get_team() const { return team; }

    const std::unique_ptr<Insecte>& get_en_dessous() const { return en_dessous; }

    bool est_cerne() const;

private:
    // BLANC ou NOIR
    Team team;

    Case* position;

    std::unique_ptr<Insecte> en_dessous;

protected:
    static bool move_casse_ruche(Case* const case_depart);
    static void compter_nb_insecte_connecte(Case* const case_depart, unsigned int& nb_trouve);

    static bool move_trop_serre(const Case* const depart, Case::Direction d);
    static bool est_un_glissement(const Case* const depart, Case::Direction d, const Case* const case_interdite);
};

#endif // INSECTE_H
