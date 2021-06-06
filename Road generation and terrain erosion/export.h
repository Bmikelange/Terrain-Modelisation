#ifndef EXPORT_H
#define EXPORT_H

#include <image.h>
#include <hf.h>


class Export
{
public:
    // Constructeur par défaut
    Export();
    //Exporte la texture associée au mesh
    static void ExportTexture(Image img);
    //Exporte le mesh au format obj
    static void ExportMesh(HF heightfield, int Xpas, int Ypas);
};

#endif // EXPORT_H
