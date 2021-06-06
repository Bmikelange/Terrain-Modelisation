#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "heightmapwidget.h"
#include "terrain.h"
#include "hf.h"
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "colorfield.h"
#include "drawing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//Classe d'affichage, définis les paramètres d'affichage, les boutons et les actions éffectués par ces boutons
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots :
    // lance l'initialisation et l'affichage du mesh de base et génère le heightfield associé
    void execute();
    //Définis les dimensions en x de la grille
    void setX(int x);
    //Définis les dimensions en y de la grille
    void setY(int x);
    //Définis l'intensité de l'affichage pour les streamArea
    void setIntensity(int x);
    //récupère depuis le disque l'image d'ou extraire les valeurs
    void changeImage();
    //affiche le mesh avec une texture de hauteur
    void changeText1();
    //affiche le mesh avec une texture de Normale
    void changeText2();
     //affiche le mesh avec une texture de Blinn
    void changeText3();
    //affiche le mesh avec une texture de pente
    void changeText4();
    //affiche le mesh avec une texture de laplacien
    void changeText5();
    //affiche le mesh avec une texture de pente moyenne
    void changeText6();
    //définis si on fait le rendu des flowarea sur une texture noire ou sur une texture de blinn
    void changeCheck(int i);
    //affiche le mesh avec une texture de flowarea
    void SStreamArea();
    //affiche le mesh avec une texture de flowareaSteepest
    void SStreamArea2();
    //affiche le mesh avec une texture de StreamPower
    void SStreamPower();
    //affiche le mesh avec une texture d'accessibilité
    void SAccess();
    //affiche le mesh avec une texture de Wetness index
    void SWindex();
    //Set la valeur du label  associée au slider X
    void setQLX(int x);
    //Set la valeur du label  associée au slider Y
    void setQLY(int x);
    //Exporte la texture image
    void ExporteTexture();
    //Exporte le mesh au format obj
    void ExporteObj();

    //richdem
    void RFilling();
    void RBreaching();

    //Erosion
    void RStreamPowerE();
    void RhillSlopeE();
    void setK(double i);

    //Road Generation
    void setGrass();
    void setPath();

    //drawing
    void affichageErosion(int i);
    void affichageRoad(int i);
    void affichageDrawing(int i);
    void setCouleur1();
    void setCouleur2();
    void setCouleur3();
    void setCouleur4();
    void setCouleur5();
    void validates();
    void setBrushSize(int i);

    void SetSI(double s);
    void SetEc(double s);
    void SetSmin(double s);
    void SetSmax(double s);
    void SetFI(double s);
    void SetWI(double s);
    void SetPFI(double s);
    void SetPWI(double s);




private:
    // ui principale
    Ui::MainWindow *ui;
    //ensembles des boutons de l'interface
    QPushButton * validate;
    QCheckBox * onBlinn;
    QPushButton * changeMap;
    QPushButton * ExportTexture;
    QPushButton * ExportObj;
    QPushButton * StreamArea;
    QPushButton * StreamArea2;
    QPushButton * StreamPower;
    QPushButton * filling;
    QPushButton * Breaching;
    QPushButton * Windex;
    QPushButton * Blin;
    QPushButton * Height;
    QPushButton * Normal;
    QPushButton * Slope;
    QPushButton * Laplacian;
    QPushButton * ASlope;
    QPushButton * Access;
    QPushButton * StreamPowerEr;
    QPushButton * hillSlopeEr;
    QSpinBox * QSBintensity;
    QDoubleSpinBox * QSK;
    QLabel * QLK;
    QLabel * QLintensity;
    QLabel * QLPrincipal;
    QLabel * QLShading;
    QLabel * QLExport;
    QLabel * QLStream;
    QLabel * QLAccess;
    QLabel * QLRichdem;
    QLabel * QLErode;
    QLabel * QLSliderX;
    QLabel * QLSliderY;
    QSlider * sliderX;
    QSlider * sliderY;
    QLabel * QLRoad;
    QPushButton * LoadGrassTexture;
    QPushButton * BDijkstra;
    QCheckBox * QCBErosion;
    QCheckBox * QCBDrawing;
    QCheckBox * QCBRoad;
    QPushButton * BForest;
    QPushButton * BProfoundForest;
    QPushButton * BWatter;
    QPushButton * BProfoundWatter;
    QPushButton * BErase;
    QPushButton * BValidate;
    QSpinBox * QSPen;
    QLabel * QLPen;

    QDoubleSpinBox * SlopeInfluence;
    QLabel * QLSI;
    QDoubleSpinBox * echelle;
    QLabel * QLECH;
    QDoubleSpinBox * SSeuilMin;
    QLabel * QLSSmin;
    QDoubleSpinBox * SSeuilMax;
    QLabel * QLSSmax;
    QDoubleSpinBox * forestInfluence;
    QLabel * QLFI;
    QDoubleSpinBox * watterInfluence;
    QLabel * QLWI;
    QDoubleSpinBox * profoundForestInfluence;
    QLabel * QLPFI;
    QDoubleSpinBox * profoundWattertInfluence;
    QLabel * QLPWI;
    //affichage principal
    QWidget * Containerfont;
    //Affichage 3D
    HeightMapWidget * map;
    // lecteur pour l'image
    Terrain ter;
    // heightfield sur lequel seront effectués les calculs
    HF heightField;
    //taille de la grille en X
    int GrilleX=128;
    //taille de la grille en Y
    int GrilleY=128;
    // intensité du rendu
    int intensity=1;
    //affichage sur une image de blinn ou non
    int onBlin=0;
    //
    int ControleSteepest=0;
    double K=0.00001;

    ColorField c;
    Drawing * draw;

    double SSlopeInfluence=1;
    double Sechelle=10;
    double SSSeuilMin=0.06,SSSeuilMax=1.2;
    double SforestInfluence=1;
    double SwatterInfluence=1;
    double SprofoundForestInfluence=1;
    double SprofoundWattertInfluence=1;

};
#endif // MAINWINDOW_H
