#ifndef MOUSTIQUE_H
#define MOUSTIQUE_H

#include "insecte.h"

class Moustique : public Insecte
{
public:
    Moustique(Team team);

    Insecte* get_en_dessous() const { return en_dessous; }

private:
    Insecte* en_dessous = nullptr;
};

#endif // MOUSTIQUE_H
