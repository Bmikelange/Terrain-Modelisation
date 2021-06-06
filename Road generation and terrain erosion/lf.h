#ifndef LF_H
#define LF_H

#include "sf2.h"

class LF : public Grid2
{
protected :
    // terrain de base
    SF2 bedrock;
    // Ajout déposés (sable, déchets végéteaux)
    SF2 sediment;
public:
    //Initialise un landscapeField à partir d'un terrain
    LF(const SF2& bd) :Grid2(bedrock), bedrock(bd){}
    //Initialise un landscapeField à partir de deux terrains
    LF(const SF2& bd, const SF2& s) :Grid2(bedrock), bedrock(bd), sediment(s){}
};

#endif // LF_H
