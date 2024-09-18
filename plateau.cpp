#include "plateau.h"

Plateau::Plateau()
{
    case_base = new Case;
    case_base->creer_alentours();
}

Plateau::~Plateau()
{
    delete case_base;
}
