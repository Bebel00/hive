#include "joueur.h"
#include "teams.h"
#include <string>

Joueur::Joueur(Team team, std::string pseudo) : pseudo(pseudo), team(team) { }
