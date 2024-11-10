#ifndef IA_H
#define IA_H

#include "case.h"
#include "teams.h"
#include <vector>
#include <array>

class NoeudIA
{
    int poids;
    NoeudIA* pere;
    std::vector<NoeudIA*> liste_fils;
    TypeAction type_action;
    Insecte* insecte_concerne;
    Case* case_concernee;

public:
    inline const int get_poids() const {return poids;}
    inline const NoeudIA* get_pere() {return pere;}
    inline void ajouter_fils(Noeud* fils) {if(fils != nullptr) {liste_fils.push_back(fils);} else {cout << "le fils est vide";}}
    inline void set_poids(int n_poids) {poids = n_poids;}
    inline void set_pere(NoeudIA* n_pere) {pere = n_pere;}
    void appliquer_move(Team tour);
    void appliquer_move_inverse();
};

class IA
{
    int profondeur;
    class NoeudIA* racine_Arbre;

public:
    IA(int profondeur): profondeur(profondeur){}
    int evaluationPoids();
    void jouerTour(Team tour);
    void constituerArbre(Team tour);
};

enum class TypeAction
{
    PLACE,
    MOVE
};

#endif // IA_H
