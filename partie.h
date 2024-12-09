#ifndef PARTIE_H
#define PARTIE_H

#include "mainwindow.h"
#include "types.h"
#include "joueur.h"
#include "insecte.h"

#include <vector>
#include <string>

class Partie
{
public:
    Partie(std::string joueur1_pseudo, std::string joueur2_pseudo,size_t retour=0);
    ~Partie();

    class Plateau* get_plateau() const { return plateau; }
    class QGraphicsView* get_view() const { return view; }
    bool verifier_victoire();

    std::string jouer_tour_cli(std::string cmd);
    size_t get_nb_retour_possible() const {return nb_retour_possible;}
    void set_nb_retour_possible(size_t nb)  {nb_retour_possible=nb;}
    const unsigned int get_nb_tours(){return nb_tours;}
    void annuler_tour(){if(nb_tours>0) nb_tours--;}

private:
    class Plateau* plateau;

    Joueur joueur1;
    Joueur joueur2;

    unsigned int nb_tours = 0;
    Joueur* tour = &joueur1;

    std::vector<class Insecte*> insectes;

    bool ajouter_insecte(Joueur& joueur, class Case* c, Type::Type type, bool bypass = false);

    std::string get_display_plateau() const;

    bool verifier_victoire_joueur(const Joueur& joueur);

    void lire_prochain_token(std::string& cmd, std::string& token);

    void setup_test();

    bool abeille_place(Joueur* joueur);

    size_t nb_retour_possible;


    class QGraphicsView* view;

};

#endif // PARTIE_H
