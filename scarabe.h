#ifndef SCARABE_H
#define SCARABE_H

#include "insecte.h"

class Scarabe : public Insecte
{
public:
    Scarabe(Team team);

    Insecte* get_en_dessous() const { return en_dessous; }

private:
    Insecte* en_dessous = nullptr;
};

#endif // SCARABE_H
