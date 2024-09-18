#ifndef PLATEAU_H
#define PLATEAU_H

#include "case.h"
#include "joueur.h"
#include <vector>

class Plateau
{
public:
    Plateau();
    ~Plateau();

private:
    Case* case_base;
};

#endif // PLATEAU_H
