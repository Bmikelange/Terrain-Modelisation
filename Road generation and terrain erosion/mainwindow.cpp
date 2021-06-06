#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileselector.h"
#include <QDir>
#include "image.h"
#include "export.h"
#include <Utility.h>
#include <dijkstra.h>
#include <QElapsedTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1500, 800);
    Containerfont=new QWidget(this);
    Containerfont->setFixedSize(1100,740);
    Containerfont->move(400,0);
    map=new HeightMapWidget(Containerfont);
    map->setFixedSize(Containerfont->width(),Containerfont->height());
    validate = new QPushButton("Execute",this);
    changeMap = new QPushButton("Change HeightMap",this);
    ExportTexture=new QPushButton("Export Texture",this);
    ExportObj=new QPushButton("Export Obj",this);
    sliderY = new QSlider(Qt::Vertical,this);
    sliderX = new QSlider(Qt::Horizontal,this);
    QLintensity = new QLabel("Intensity :",this);
    QSBintensity = new QSpinBox(this);
    QLPrincipal= new QLabel("Principal",this);
    QLShading = new QLabel("Shading",this);
    QLExport =new QLabel("Export",this);
    QLStream= new QLabel("Stream",this);
    QLRichdem= new QLabel("Richdem",this);
    QLAccess= new QLabel("Accessibility",this);
    QLSliderX= new QLabel(QString::number(GrilleX),this);
    QLSliderY= new QLabel(QString::number(GrilleY),this);
    onBlinn= new QCheckBox("on blinn",this);

    Blin=new QPushButton("Blinn",this);
    Height=new QPushButton("Height",this);
    Normal=new QPushButton("Normal",this);
    Slope=new QPushButton("Slope",this);
    Laplacian=new QPushButton("Lapla",this);
    ASlope=new QPushButton("ASlope",this);
    StreamArea=new QPushButton("Stream Area",this);
    StreamArea2=new QPushButton("Stream Area Steepest",this);
    StreamPower=new QPushButton("Stream Power",this);
    Windex=new QPushButton("Wetness Index",this);
    Access=new QPushButton("Access",this);

    filling=new QPushButton("Filling",this);
    Breaching=new QPushButton("Breaching",this);
    QLErode= new QLabel("Erosion",this);
    StreamPowerEr=new QPushButton("SP Erode",this);
    hillSlopeEr=new QPushButton("HS Erode",this);
    QSK=new QDoubleSpinBox(this);
    QLK=new QLabel("K = ",this);

    QLRoad=new QLabel("Road",this);
    LoadGrassTexture=new QPushButton("Load Grass",this);
    BDijkstra=new QPushButton("Dijkstra",this);

    QCBErosion = new QCheckBox("Erosion",this);
    QCBDrawing = new QCheckBox("Drawing",this);
    QCBRoad = new QCheckBox("Road",this);

    BForest=new QPushButton("Forest",this);
    BProfoundForest=new QPushButton("Profound Forest",this);
    BWatter=new QPushButton("Watter",this);
    BProfoundWatter=new QPushButton("Profound Watter",this);
    BErase=new QPushButton("Erase",this);
    BValidate=new QPushButton("Validate",this);
    draw = new Drawing();
    draw->setParent(Containerfont);
    QSPen=new QSpinBox(this);
    QLPen=new QLabel("Brush size",this);

    SlopeInfluence=new QDoubleSpinBox(this);
    QLSI=new QLabel("Slope I",this);
    echelle=new QDoubleSpinBox(this);
    QLECH=new QLabel("Echelle",this);
    SSeuilMin=new QDoubleSpinBox(this);
    QLSSmin=new QLabel("Slope min",this);
    SSeuilMax=new QDoubleSpinBox(this);
    QLSSmax=new QLabel("Slope max",this);
    forestInfluence=new QDoubleSpinBox(this);
    QLFI=new QLabel("forest I",this);
    watterInfluence=new QDoubleSpinBox(this);
    QLWI=new QLabel("watter I",this);
    profoundForestInfluence=new QDoubleSpinBox(this);
    QLPFI=new QLabel("P forest I",this);
    profoundWattertInfluence=new QDoubleSpinBox(this);
    QLPWI=new QLabel("P watter I",this);

    validate->setFixedSize(150,25);
    changeMap->setFixedSize(150,25);
    sliderY->setFixedSize(25,740);
    sliderX->setFixedSize(740,25);
    Blin->setFixedSize(70,25);
    Height->setFixedSize(70,25);
    Normal->setFixedSize(70,25);
    Slope->setFixedSize(70,25);
    Laplacian->setFixedSize(70,25);
    ASlope->setFixedSize(70,25);
    QLSliderX->setFixedSize(40,25);
    QLSliderY->setFixedSize(40,25);
    //TODO
    StreamArea->setFixedSize(0,0);
    StreamArea2->setFixedSize(0,0);
    StreamPower->setFixedSize(0,0);
    Windex->setFixedSize(0,0);
    QLintensity->setFixedSize(0,0);
    QSBintensity->setFixedSize(0,0);
    QLStream->setFixedSize(0,0);
    QLExport->setFixedSize(150,35);
    QLAccess->setFixedSize(0,0);
    onBlinn->setFixedSize(0,0);
    ExportTexture->setFixedSize(150,25);
    ExportObj->setFixedSize(150,25);
    Access->setFixedSize(0,0);
    filling->setFixedSize(0,0);
    Breaching->setFixedSize(0,0);
    QLRichdem->setFixedSize(0,0);
    QLErode->setFixedSize(0,0);
    StreamPowerEr->setFixedSize(0,0);
    hillSlopeEr->setFixedSize(0,0);
    QSK->setFixedSize(0,0);
    QLK->setFixedSize(0,0);
    QLRoad->setFixedSize(0,0);
    LoadGrassTexture->setFixedSize(0,0);
    BDijkstra->setFixedSize(0,0);
    draw->setFixedSize(0,0);
    //end

    QCBErosion->setFixedSize(150,25);
    QCBDrawing->setFixedSize(150,25);
    QCBRoad->setFixedSize(150,25);

    BForest->setFixedSize(0,0);
    BProfoundForest->setFixedSize(0,0);
    BWatter->setFixedSize(0,0);
    BProfoundWatter->setFixedSize(0,0);
    BErase->setFixedSize(0,0);
    BValidate->setFixedSize(0,0);

    QSPen->setFixedSize(0,0);
    QLPen->setFixedSize(0,0);

    SlopeInfluence->setFixedSize(0,0);
    QLSI->setFixedSize(0,0);
    echelle->setFixedSize(0,0);
    QLECH->setFixedSize(0,0);
    SSeuilMin->setFixedSize(0,0);
    QLSSmin->setFixedSize(0,0);
    SSeuilMax->setFixedSize(0,0);
    QLSSmax->setFixedSize(0,0);
    forestInfluence->setFixedSize(0,0);
    QLFI->setFixedSize(0,0);
    watterInfluence->setFixedSize(0,0);
    QLWI->setFixedSize(0,0);
    profoundForestInfluence->setFixedSize(0,0);
    QLPFI->setFixedSize(0,0);
    profoundWattertInfluence->setFixedSize(0,0);
    QLPWI->setFixedSize(0,0);

    QSK->setRange(0.00001, 0.0001);
    QSK->setSingleStep(0.00001);
    QSK->setDecimals(5);
    SlopeInfluence->setRange(0.1,5.0);
    SlopeInfluence->setSingleStep(0.1);
    SlopeInfluence->setDecimals(1);
    echelle->setRange(10,100.0);
    echelle->setSingleStep(1);
    echelle->setDecimals(0);
    SSeuilMin->setRange(0.01,2.0);
    SSeuilMin->setSingleStep(0.01);
    SSeuilMin->setDecimals(2);
    SSeuilMax->setRange(0.01,2.0);
    SSeuilMax->setSingleStep(0.01);
    SSeuilMax->setDecimals(2);
    forestInfluence->setRange(0.1,5.0);
    forestInfluence->setSingleStep(0.1);
    forestInfluence->setDecimals(1);
    watterInfluence->setRange(0.1,5.0);
    watterInfluence->setSingleStep(0.1);
    watterInfluence->setDecimals(1);
    profoundForestInfluence->setRange(0.1,5.0);
    profoundForestInfluence->setSingleStep(0.1);
    profoundForestInfluence->setDecimals(1);
    profoundWattertInfluence->setRange(0.1,5.0);
    profoundWattertInfluence->setSingleStep(0.1);
    profoundWattertInfluence->setDecimals(1);


    validate->move(180,50);
    changeMap->move(20,50);
    sliderY->move(370,0);
    sliderX->move(400,740);
    Blin->move(30,130);
    Height->move(110,130);
    Normal->move(190,130);
    Slope->move(270,130);
    Laplacian->move(30,160);
    ASlope->move(110,160);
    QCBErosion->setFixedSize(150,25);
    QCBDrawing->setFixedSize(150,25);
    QCBRoad->setFixedSize(150,25);
    //TODO
    StreamArea->move(20,230);
    StreamArea2->move(180,230);
    StreamPower->move(20,290);
    Windex->move(180,290);
    QLintensity->move(20,260);
    QSBintensity->move(90,260);
    QLPrincipal->move(130,10);
    QLShading->move(130,90);
    QLStream->move(130,190);
    QLAccess->move(100,320);
    QLSliderX->move(400,760);
    QLSliderY->move(330,720);
    onBlinn->move(180,260);
    QLExport->move(130,720);
    ExportTexture->move(20,760);
    ExportObj->move(180,760);
    Access->move(20,360);
    filling->move(20,430);
    Breaching->move(180,430);
    QLRichdem->move(130,390);
    QLErode->move(130,460);
    StreamPowerEr->move(20,500);
    hillSlopeEr->move(180,500);
    QLK->move(20,530);
    QSK->move(50,530);
    //TODO
    QLRoad->move(130,250);
    LoadGrassTexture->move(20,290);
    BDijkstra->move(180,290);

    QCBErosion->move(20,200);
    QCBDrawing->move(20,230);
    QCBRoad->move(20,260);

    BForest->move(20,260);
    BProfoundForest->move(20,290);
    BWatter->move(20,320);
    BProfoundWatter->move(20,350);
    BErase->move(20,380);
    BValidate->move(180,410);
    draw->move(332,228);
    QSPen->move(180,260);
    QLPen->move(250,260);

    SlopeInfluence->move(20,320);
    QLSI->move(90,320);
    echelle->move(180,320);
    QLECH->move(250,320);
    SSeuilMin->move(20,350);
    QLSSmin->move(90,350);
    SSeuilMax->move(180,350);
    QLSSmax->move(250,350);
    forestInfluence->move(20,380);
    QLFI->move(90,380);
    watterInfluence->move(180,380);
    QLWI->move(250,380);
    profoundForestInfluence->move(20,410);
    QLPFI->move(90,410);
    profoundWattertInfluence->move(180,410);
    QLPWI->move(250,410);

    BForest->setStyleSheet("background-color: rgb(0,255,0)");
    BProfoundForest->setStyleSheet("background-color: rgb(0,120,0)");
    BWatter->setStyleSheet("background-color: rgb(0,0,255)");
    BProfoundWatter->setStyleSheet("background-color: rgb(0,0,120)");
    QLPrincipal->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLShading->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLStream->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLExport->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLRichdem->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLErode->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLAccess->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLRoad->setStyleSheet("text-decoration: underline;font-size: 25px; color: #191970;");
    QLSliderX->setStyleSheet("border : 1px solid");
    QLSliderY->setStyleSheet("border : 1px solid");

    sliderY->setMaximum(1024);
    sliderY->setMinimum(10);
    sliderX->setMaximum(1024);
    sliderX->setMinimum(10);
    sliderY->setValue(128);
    sliderX->setValue(128);
    QSBintensity->setMaximum(10);
    QSBintensity->setMinimum(1);
    QSBintensity->setValue(1);
    onBlinn->setChecked(false);
    QSPen->setMaximum(1000);
    QSPen->setMinimum(1);
    QSPen->setValue(20);
    SlopeInfluence->setValue(1);
    echelle->setValue(10);
    SSeuilMin->setValue(0.06);
    SSeuilMax->setValue(1.2);
    forestInfluence->setValue(1);
    watterInfluence->setValue(1);
    profoundForestInfluence->setValue(1);
    profoundWattertInfluence->setValue(1);

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(execute()));
    QObject::connect(changeMap, SIGNAL(clicked()), this, SLOT(changeImage()));
    QObject::connect(Height, SIGNAL(clicked()), this, SLOT(changeText1()));
    QObject::connect(Normal, SIGNAL(clicked()), this, SLOT(changeText2()));
    QObject::connect(Blin, SIGNAL(clicked()), this, SLOT(changeText3()));
    QObject::connect(Slope, SIGNAL(clicked()), this, SLOT(changeText4()));
    QObject::connect(Laplacian, SIGNAL(clicked()), this, SLOT(changeText5()));
    QObject::connect(ASlope, SIGNAL(clicked()), this, SLOT(changeText6()));
    QObject::connect(ExportTexture, SIGNAL(clicked()), this, SLOT(ExporteTexture()));
    QObject::connect(ExportObj, SIGNAL(clicked()), this, SLOT(ExporteObj()));
    QObject::connect(StreamArea, SIGNAL(clicked()), this, SLOT(SStreamArea()));
    QObject::connect(StreamArea2, SIGNAL(clicked()), this, SLOT(SStreamArea2()));
    QObject::connect(StreamPower, SIGNAL(clicked()), this, SLOT(SStreamPower()));
    QObject::connect(StreamPowerEr, SIGNAL(clicked()), this, SLOT(RStreamPowerE()));
    QObject::connect(hillSlopeEr, SIGNAL(clicked()), this, SLOT(RhillSlopeE()));
    QObject::connect(filling, SIGNAL(clicked()), this, SLOT(RFilling()));
    QObject::connect(Breaching, SIGNAL(clicked()), this, SLOT(RBreaching()));
    QObject::connect(Access, SIGNAL(clicked()), this, SLOT(SAccess()));
    QObject::connect(Windex, SIGNAL(clicked()), this, SLOT(SWindex()));
    QObject::connect(LoadGrassTexture, SIGNAL(clicked()), this, SLOT(setGrass()));
    QObject::connect(BDijkstra, SIGNAL(clicked()), this, SLOT(setPath()));
    QObject::connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    QObject::connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    QObject::connect(sliderY, SIGNAL(sliderMoved(int)), this, SLOT(setQLY(int)));
    QObject::connect(sliderX, SIGNAL(sliderMoved(int)), this, SLOT(setQLX(int)));
    QObject::connect(QSBintensity, SIGNAL(valueChanged(int)), this, SLOT(setIntensity(int)));
    QObject::connect(QSK, SIGNAL(valueChanged(double)), this, SLOT(setK(double)));
    connect(onBlinn, SIGNAL(stateChanged(int)), this, SLOT(changeCheck(int)));
    connect(QCBErosion, SIGNAL(stateChanged(int)), this, SLOT(affichageErosion(int)));
    connect(QCBRoad, SIGNAL(stateChanged(int)), this, SLOT(affichageRoad(int)));
    connect(QCBDrawing, SIGNAL(stateChanged(int)), this, SLOT(affichageDrawing(int)));
    QObject::connect(BForest, SIGNAL(clicked()), this, SLOT(setCouleur1()));
    QObject::connect(BProfoundForest, SIGNAL(clicked()), this, SLOT(setCouleur2()));
    QObject::connect(BWatter, SIGNAL(clicked()), this, SLOT(setCouleur3()));
    QObject::connect(BProfoundWatter, SIGNAL(clicked()), this, SLOT(setCouleur4()));
    QObject::connect(BErase, SIGNAL(clicked()), this, SLOT(setCouleur5()));
    QObject::connect(BValidate, SIGNAL(clicked()), this, SLOT(validates()));
    QObject::connect(QSPen, SIGNAL(valueChanged(int)), this, SLOT(setBrushSize(int)));

    QObject::connect(SlopeInfluence, SIGNAL(valueChanged(double)), this, SLOT(SetSI(double)));
    QObject::connect(echelle, SIGNAL(valueChanged(double)), this, SLOT(SetEc(double)));
    QObject::connect(SSeuilMin, SIGNAL(valueChanged(double)), this, SLOT(SetSmin(double)));
    QObject::connect(SSeuilMax, SIGNAL(valueChanged(double)), this, SLOT(SetSmax(double)));
    QObject::connect(forestInfluence, SIGNAL(valueChanged(double)), this, SLOT(SetFI(double)));
    QObject::connect(watterInfluence, SIGNAL(valueChanged(double)), this, SLOT(SetWI(double)));
    QObject::connect(profoundForestInfluence, SIGNAL(valueChanged(double)), this, SLOT(SetPFI(double)));
    QObject::connect(profoundWattertInfluence, SIGNAL(valueChanged(double)), this, SLOT(SetPWI(double)));

    execute();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execute()
{
    heightField=HF(SF2(Grid2(Box2(Vec2(0.0,0.0), Vec2(GrilleX,GrilleY)),GrilleX,GrilleY)));
    heightField.setfield(ter.getimg());
    heightField.computeHeightMap();
    heightField.RHeight();
    map->reset();
    map->setImg(heightField.getHeightMap());
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
    c=ColorField(heightField.getnx(),heightField.getny());
}
void MainWindow::setX(int x)
{
    GrilleX=x;
}
void MainWindow::setY(int x)
{
    GrilleY=x;
}

void MainWindow::setK(double i)
{
    K=i;
}

void MainWindow::setQLX(int x)
{
    QLSliderX->setText(QString::number(x));
}
void MainWindow::setQLY(int x)
{
    QLSliderY->setText(QString::number(x));
}

void MainWindow::ExporteTexture()
{
    Export::ExportTexture(map->getTexture());
}
void MainWindow::ExporteObj()
{
    Export::ExportMesh(heightField, map->getPasx(), map->getPasy());
}

void MainWindow::changeImage()
{
    fileselector file;
    std::string filename = file.getFileName();
    ter.setImg(filename);
}

void MainWindow::changeText1()
{
    heightField.RHeight();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::changeCheck(int i)
{
    onBlin=i;
}
void MainWindow::changeText2()
{
    heightField.RNormal();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}
void MainWindow::changeText3()
{
    heightField.RBlin();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}
void MainWindow::changeText4()
{
    heightField.RSlope();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::changeText5()
{
    heightField.RLaplacien();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::changeText6()
{
    heightField.RASlope();
    map->setTexture(heightField.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::SStreamArea()
{
    HF * heightField2=new HF(heightField.StreamArea());
    heightField2->RSArea(intensity);
    if(onBlin==0)
    {
        map->setTexture(heightField2->getTexture());
    }
    else {
        heightField.RBlin();
        map->setTexture(Image::addImage(heightField2->getTexture(),heightField.getTexture()));
    }
    map->initializeGL();
    map->update();
    ControleSteepest=0;
}

void MainWindow::SStreamArea2()
{
    HF * heightField2=new HF(heightField.StreamAreaSteepest());
    heightField2->RSArea(intensity);
    if(onBlin==0)
    {
        map->setTexture(heightField2->getTexture());
    }
    else {
        heightField.RBlin();
        map->setTexture(Image::addImage(heightField2->getTexture(),heightField.getTexture()));
    }
    map->initializeGL();
    map->update();
    ControleSteepest=1;
}

void MainWindow::SStreamPower()
{
    HF heightField2;
    if(ControleSteepest==1)
        heightField2=HF(heightField.StreamPower(heightField.StreamAreaSteepest()));
    else {
        heightField2=HF(heightField.StreamPower(heightField.StreamArea()));
    }
    heightField2.RSArea(intensity);
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::SWindex()
{
    HF heightField2;
    if(ControleSteepest==1)
        heightField2=HF(heightField.WetnessIndex(heightField.StreamAreaSteepest()));
    else {
        heightField2=HF(heightField.WetnessIndex(heightField.StreamArea()));
    }
    heightField2.RSArea(intensity);
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::SAccess()
{
    HF heightField2(heightField.Access());
    heightField2.RSAccess();
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
}

void MainWindow::setIntensity(int x)
{
    intensity=x;
}


void MainWindow::RFilling()
{
    HF heightField2(heightField.SRichdem_depression_filling());
    heightField2.computeHeightMap();
    heightField2.RHeight();
    map->setImg(heightField2.getHeightMap());
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
    heightField=heightField2;
}
void MainWindow::RBreaching()
{
    HF heightField2(heightField.SRichdem_depression_breaching());
    heightField2.computeHeightMap();
    heightField2.RHeight();
    map->setImg(heightField2.getHeightMap());
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
    heightField=heightField2;
}

void MainWindow::RStreamPowerE()
{
    HF heightField2;
    if(ControleSteepest==1)
        heightField2 = HF(heightField.StreamPowerErode(heightField.StreamAreaSteepest(),K));
    else
        heightField2 = HF(heightField.StreamPowerErode(heightField.StreamArea(),K));
    heightField2.computeHeightMap();
    heightField2.RHeight();
    map->setImg(heightField2.getHeightMap());
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
    heightField=heightField2;
}
void MainWindow::RhillSlopeE()
{
    HF heightField2(heightField.Hill_Slope(0.00000056));
    heightField2.computeHeightMap();
    heightField2.RHeight();
    map->setImg(heightField2.getHeightMap());
    map->setTexture(heightField2.getTexture());
    map->initializeGL();
    map->update();
    heightField=heightField2;
}

void MainWindow::setGrass()
{
    heightField.RBlin();
    map->setTexture(Image::addImage(heightField.getTexture(),c.getTexture()));
    map->initializeGL();
    map->update();
}

void MainWindow::setPath()
{
    QElapsedTimer timer;
    timer.start();
    Dijkstra d(heightField);
    d.SetSI(SSlopeInfluence);
    d.SetEc(Sechelle);
    d.SetSmin(SSSeuilMin);
    d.SetSmax(SSSeuilMax);
    d.SetFI(SforestInfluence);
    d.SetWI(SwatterInfluence);
    d.SetPFI(SprofoundForestInfluence);
    d.SetPWI(SprofoundWattertInfluence);
    d.setDijkstra(c);
    ColorField cf=c;
    std::vector<std::pair<int,int>> result = d.draw(cf,d);
    double time1 = ((double)timer.elapsed())/1000;
    qDebug()<< time1;
    map->setRoad(result);
    heightField.RBlin();
    map->setTexture(Image::addImage(heightField.getTexture(),cf.getTexture()));
    map->initializeGL();
    map->update();
}


void MainWindow::affichageErosion(int i)
{
    if(i!=0)
    {
        StreamArea->setFixedSize(150,25);
        StreamArea2->setFixedSize(150,25);
        StreamPower->setFixedSize(150,25);
        Windex->setFixedSize(150,25);
        QLintensity->setFixedSize(80,25);
        QSBintensity->setFixedSize(50,25);
        QLStream->setFixedSize(150,35);
        QLAccess->setFixedSize(150,35);
        onBlinn->setFixedSize(80,25);
        Access->setFixedSize(150,25);
        filling->setFixedSize(150,25);
        Breaching->setFixedSize(150,25);
        QLRichdem->setFixedSize(150,35);
        QLErode->setFixedSize(150,35);
        StreamPowerEr->setFixedSize(150,25);
        hillSlopeEr->setFixedSize(150,25);
        QSK->setFixedSize(120,25);
        QLK->setFixedSize(40,25);
        QCBDrawing->setFixedSize(0,0);
        QCBRoad->setFixedSize(0,0);
    }
    else {
        StreamArea->setFixedSize(0,0);
        StreamArea2->setFixedSize(0,0);
        StreamPower->setFixedSize(0,0);
        Windex->setFixedSize(0,0);
        QLintensity->setFixedSize(0,0);
        QSBintensity->setFixedSize(0,0);
        QLStream->setFixedSize(0,0);
        QLAccess->setFixedSize(0,0);
        onBlinn->setFixedSize(0,0);
        Access->setFixedSize(0,0);
        filling->setFixedSize(0,0);
        Breaching->setFixedSize(0,0);
        QLRichdem->setFixedSize(0,0);
        QLErode->setFixedSize(0,0);
        StreamPowerEr->setFixedSize(0,0);
        hillSlopeEr->setFixedSize(0,0);
        QSK->setFixedSize(0,0);
        QLK->setFixedSize(0,0);
        QCBDrawing->setFixedSize(150,25);
        QCBRoad->setFixedSize(150,25);
    }
}

void MainWindow::affichageRoad(int i)
{
    if(i!=0)
    {
        QLRoad->setFixedSize(150,35);
        LoadGrassTexture->setFixedSize(150,25);
        BDijkstra->setFixedSize(150,25);
        QCBDrawing->setFixedSize(0,0);
        QCBErosion->setFixedSize(0,0);
        SlopeInfluence->setFixedSize(65,25);
        QLSI->setFixedSize(85,25);
        echelle->setFixedSize(65,25);
        QLECH->setFixedSize(85,25);
        SSeuilMin->setFixedSize(65,25);
        QLSSmin->setFixedSize(85,25);
        SSeuilMax->setFixedSize(65,25);
        QLSSmax->setFixedSize(85,25);
        forestInfluence->setFixedSize(65,25);
        QLFI->setFixedSize(85,25);
        watterInfluence->setFixedSize(65,25);
        QLWI->setFixedSize(85,25);
        profoundForestInfluence->setFixedSize(65,25);
        QLPFI->setFixedSize(85,25);
        profoundWattertInfluence->setFixedSize(65,25);
        QLPWI->setFixedSize(85,25);

    }
    else {
        QLRoad->setFixedSize(0,0);
        LoadGrassTexture->setFixedSize(0,0);
        BDijkstra->setFixedSize(0,0);
        QCBDrawing->setFixedSize(150,25);
        QCBErosion->setFixedSize(150,25);
        SlopeInfluence->setFixedSize(0,0);
        QLSI->setFixedSize(0,0);
        echelle->setFixedSize(0,0);
        QLECH->setFixedSize(0,0);
        SSeuilMin->setFixedSize(0,0);
        QLSSmin->setFixedSize(0,0);
        SSeuilMax->setFixedSize(0,0);
        QLSSmax->setFixedSize(0,0);
        forestInfluence->setFixedSize(0,0);
        QLFI->setFixedSize(0,0);
        watterInfluence->setFixedSize(0,0);
        QLWI->setFixedSize(0,0);
        profoundForestInfluence->setFixedSize(0,0);
        QLPFI->setFixedSize(0,0);
        profoundWattertInfluence->setFixedSize(0,0);
        QLPWI->setFixedSize(0,0);

    }
}


void MainWindow::affichageDrawing(int i)
{
    if(i!=0)
    {
        BForest->setFixedSize(150,25);
        BProfoundForest->setFixedSize(150,25);
        BWatter->setFixedSize(150,25);
        BProfoundWatter->setFixedSize(150,25);
        BErase->setFixedSize(150,25);
        BValidate->setFixedSize(150,25);
        QCBRoad->setFixedSize(0,0);
        QCBErosion->setFixedSize(0,0);
        map->setFixedSize(332,228);
        draw->setFixedSize(512,512);
        QSPen->setFixedSize(65,25);
        QLPen->setFixedSize(100,25);
        draw->setColorField(c);
    }
    else {
        BForest->setFixedSize(0,0);
        BProfoundForest->setFixedSize(0,0);
        BWatter->setFixedSize(0,0);
        BProfoundWatter->setFixedSize(0,0);
        BErase->setFixedSize(0,0);
        BValidate->setFixedSize(0,0);
        QCBRoad->setFixedSize(150,25);
        QCBErosion->setFixedSize(150,25);
        draw->setFixedSize(0,0);
        map->setFixedSize(Containerfont->width(),Containerfont->height());
        QSPen->setFixedSize(0,0);
        QLPen->setFixedSize(0,0);
    }
}
void MainWindow::setCouleur1(){
    QColor c1(0,255,0);
    draw->setColor(c1);
}
void MainWindow::setCouleur2(){
    QColor c1(0,120,0);
    draw->setColor(c1);
}
void MainWindow::setCouleur3(){
    QColor c1(0,0,255);
    draw->setColor(c1);
}
void MainWindow::setCouleur4(){
     QColor c1(0,0,120);
     draw->setColor(c1);
}

void MainWindow::setCouleur5(){
     QColor c1(0,0,0);
     draw->setColor(c1);
}

void MainWindow::validates(){
     draw->validate();
     c=draw->getColorField();
}

void  MainWindow::setBrushSize(int i){
    draw->setRadius(i);
}

void MainWindow::SetSI(double s){ SSlopeInfluence=s;}
void MainWindow::SetEc(double s){  Sechelle=s;}
void MainWindow::SetSmin(double s){  SSSeuilMin=s;}
void MainWindow::SetSmax(double s){ SSSeuilMax=s;}
void MainWindow::SetFI(double s){  SforestInfluence=s;}
void MainWindow::SetWI(double s){ SwatterInfluence=s;}
void MainWindow::SetPFI(double s){ SprofoundForestInfluence=s;}
void MainWindow::SetPWI(double s){  SprofoundWattertInfluence=s;}

