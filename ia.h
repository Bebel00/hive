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
    inline const int get_poids() const {return poids;}
    inline const int get_type_action() const {return type_action;}
    inline const int get_type_insecte() const {return type_insecte;}
    inline const int get_case_debut() const {return case_debut;}
    inline const int get_case_fin() const {return case_fin;}
    inline std::vector<NoeudIA*> get_liste_fils() {return liste_fils;}
    inline NoeudIA* get_pere() {return pere;}

    inline void ajouter_fils(NoeudIA* fils) {if(fils != nullptr) {liste_fils.push_back(fils);} else {std::cout << "le fils est vide";}}
    inline void set_poids(int n_poids) {poids = n_poids;}
    inline void set_pere(NoeudIA* n_pere) {pere = n_pere;}

    int appliquer_move(Partie* partie);
    int appliquer_move_inverse(Partie* partie);
    ~NoeudIA() {for(NoeudIA* i_noeud : liste_fils){delete *i_noeud;}}
};

class IA : Joueur
{
    Team team;
    int profondeur;
    class NoeudIA* racine_Arbre=nullptr;

public:
    IA(int profondeur, Team team): profondeur(profondeur), team(team){}
    int evaluation_poids(Plateau* plateau);
    NoeudIA* constituer_arbre(Partie* partie,int etage=1, NoeudIA* pere=nullptr, TypeAction type_action=TypeAction::NONE, Type::Type type_insecte = Type::Type::NONE, Case* case_debut = nullptr, Case* case_fin = nullptr);
    NoeudIA* reconstituer_arbre(Partie* partie, TypeAction type_action_precedente = TypeAction::NONE, Type::Type type_insecte_precedent = Type::Type::NONE,
                                Case* case_debut_precedente = nullptr, Case* case_fin_precedente = nullptr);
    void jouer_tour(Partie* partie, TypeAction type_action_precedente = TypeAction::NONE, Type::Type type_insecte_precedent = Type::Type::NONE,
                    Case* case_debut_precedente = nullptr, Case* case_fin_precedente = nullptr);
};


#endif // IA_H
