#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"

class Fourmi : public Insecte
{
public:
    Fourmi(Team team);
    virtual int get_jetons_max() const override { return 3; }
};

#endif // FOURMI_H
