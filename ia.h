#ifndef IA_H
#define IA_H

#include "case.h"
#include "teams.h"
#include "partie.h"
#include "plateau.h"
#include "joueur.h"
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

    NoeudIA* pere = nullptr;

    TypeAction type_action = TypeAction::NONE;
    Type::Type type_insecte = Type::Type::NONE;
    Case* case_debut = nullptr;
    Case* case_fin = nullptr;
    bool enfants_testes = true;
    int poids = 0;
    std::vector<NoeudIA*> liste_fils;

public:
    NoeudIA(NoeudIA* pere, TypeAction type_action, Type::Type type_insecte, Case* case_debut, Case* case_fin) : pere(pere), type_action(type_action),
        type_insecte(type_insecte), case_debut(case_debut), case_fin(case_fin){}

    NoeudIA()= default;

    int get_poids() const {return poids;}
    TypeAction get_type_action() const {return type_action;}
    Type::Type get_type_insecte() const {return type_insecte;}
    Case* get_case_debut() const {return case_debut;}
    Case* get_case_fin() const {return case_fin;}
    bool get_enfants_testes() const {return enfants_testes;}
    std::vector<NoeudIA*> get_liste_fils() {return liste_fils;}
    NoeudIA* get_pere() {return pere;}

    void ajouter_fils(NoeudIA* fils) {if(fils != nullptr) {liste_fils.push_back(fils);} else {std::cout << "le fils est vide";}}
    void set_poids(int n_poids) {poids = n_poids;}
    void set_pere(NoeudIA* n_pere) {pere = n_pere;}
    void set_enfants_testes(bool b) {enfants_testes = b;}

    int appliquer_move(Partie* partie);
    int appliquer_move_inverse(Partie* partie);
    ~NoeudIA() {for(NoeudIA* i_noeud : liste_fils){delete i_noeud;}}
};

class IA
{
    Team team;
    int profondeur=4;
    class NoeudIA* racine_Arbre=nullptr;

public:
    IA( Team team, int profondeur): team(team), profondeur(profondeur){}
    int evaluation_poids(Plateau* plateau);
    NoeudIA* constituer_arbre(Partie* partie, NoeudIA* racine,int etage=1);
    NoeudIA* redevelopper_arbre(Partie* partie, NoeudIA* racine,int etage=1);
    NoeudIA* reconstituer_arbre(Partie* partie, TypeAction type_action_humain = TypeAction::NONE, Type::Type type_insecte_humain = Type::Type::NONE,
                                Case* case_debut_humain = nullptr, Case* case_fin_humain = nullptr);
    void jouer_tour(Partie* partie, TypeAction type_action_humain = TypeAction::NONE, Type::Type type_insecte_humain = Type::Type::NONE,
                    Case* case_debut_humain = nullptr, Case* case_fin_humain = nullptr);
};


#endif // IA_H
