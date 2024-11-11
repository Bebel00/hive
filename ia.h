#ifndef IA_H
#define IA_H

#include "case.h"
#include "teams.h"
#include "partie.h"
#include "plateau.h"
#include "Joueur.h"
#include "types.h"
#include "insecte.h"
#include <vector>
#include <array>
#include <iostream>


enum class TypeAction
{
    PLACE,
    MOVE,
    NONE
};

class NoeudIA
{
    int poids=NULL;
    NoeudIA* pere = nullptr;
    std::vector<NoeudIA*> liste_fils;
    TypeAction type_action = TypeAction::NONE;
    Type::Type type_insecte = Type::Type::NONE;
    Case* case_debut = nullptr;
    Case* case_fin = nullptr;

public:
    NoeudIA(NoeudIA* pere, TypeAction type_action, Type::Type type_insecte, Case* case_fin) : pere(pere), type_action(type_action),
        type_insecte(type_insecte), case_fin(case_fin) {}
    NoeudIA(NoeudIA* pere, TypeAction type_action,  Case* case_debut, Case* case_fin) : pere(pere), type_action(type_action),
        case_debut(case_debut), case_fin(case_fin) {}
    inline const int get_poids() const {return poids;}
    inline const NoeudIA* get_pere() {return pere;}
    inline void ajouter_fils(NoeudIA* fils) {if(fils != nullptr) {liste_fils.push_back(fils);} else {std::cout << "le fils est vide";}}
    inline void set_poids(int n_poids) {poids = n_poids;}
    inline void set_pere(NoeudIA* n_pere) {pere = n_pere;}
    int appliquer_move(Partie* partie);
    int appliquer_move_inverse(Partie* partie);
};

class IA : Joueur
{
    int profondeur;
    class NoeudIA* racine_Arbre;

public:
    IA(int profondeur): profondeur(profondeur){}
    int evaluationPoids(Plateau* plateau);
    void constituerArbre(Partie* partie);
    void jouerTour(Partie* partie);
};


#endif // IA_H
