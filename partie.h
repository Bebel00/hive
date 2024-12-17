#ifndef PARTIE_H
#define PARTIE_H

#include "mainwindow.h"
#include "types.h"
#include "joueur.h"
#include "insecte.h"

#include <string>

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo,size_t retour=0);
    ~Partie();

    friend class GraphicsPartie;

    class Plateau* get_plateau() const { return plateau; }

    bool verifier_victoire();

    std::string jouer_tour_cli(std::string cmd);

    unsigned int get_nb_tours(){ return nb_tours; }

    void jouer_tour();

    Joueur* get_tour_joueur() const { return tour; }

    unsigned int nb_retours_possibles;


private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Joueur* tour = &joueur2;

    bool ajouter_insecte(Joueur& joueur, class Case* c, Type::Type type, bool bypass = false);

    std::string get_display_plateau() const;

    bool verifier_victoire_joueur(const Joueur& joueur);

    void lire_prochain_token(std::string& cmd, std::string& token);

    void setup_test();

    bool abeille_place(Joueur* joueur);

    void annuler_deplacement();
};

#endif // PARTIE_H
