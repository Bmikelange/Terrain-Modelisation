#include <string>
using namespace std;

#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QObject>
#include <QWidget>


// contient les fonctions nécessaires à l'ouverture des fichiers
class fileselector : public QWidget
{
public:
    // Ouvre une fenêtre permettant d'aller chercher l'image à ouvrir
    fileselector();
    //renvoie le chemin d'accès au fichier;
    string getFileName();
private:
    //le chemin d'accès au fichier;
    string filename;
};

#endif // FILESELECTOR_H
