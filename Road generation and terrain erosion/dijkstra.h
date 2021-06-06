#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits>

#include <set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <QPoint>

#include<colorfield.h>
#include<hf.h>


typedef int vertex_t;
typedef double weight_t;

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;


class Dijkstra : public HF
{
protected :
    const weight_t max_weight = std::numeric_limits<double>::infinity();
    adjacency_list_t list;
    double SlopeInfluence=1;
    double echelle=10;
    double SSeuilMin=0.06,SSeuilMax=1.2;
    double forestInfluence=1;
    double watterInfluence=1;
    double profoundForestInfluence=1;
    double profoundWattertInfluence=1;
public:
    Dijkstra();
    Dijkstra(HF h) : HF(h){}

    void setDijkstra(const ColorField & c);
    double heights(QPoint a, QPoint b,const ColorField & c);
    double Slope(Vec2 pa, Vec2 pb,double l);
    void DijkstraComputePaths(vertex_t source,
                              const adjacency_list_t &adjacency_list,
                              std::vector<weight_t> &min_distance,
                              std::vector<vertex_t> &previous);
    std::list<vertex_t> DijkstraGetShortestPathTo(
        vertex_t vertex, const std::vector<vertex_t> &previous);
    std::vector<std::pair<int,int>> draw(ColorField & c, Dijkstra d);

    void SetSI(double s){ SlopeInfluence=s;}
    void SetEc(double s){  echelle=s;}
    void SetSmin(double s){  SSeuilMin=s;}
    void SetSmax(double s){ SSeuilMax=s;}
    void SetFI(double s){  forestInfluence=s;}
    void SetWI(double s){ watterInfluence=s;}
    void SetPFI(double s){ profoundForestInfluence=s;}
    void SetPWI(double s){  profoundWattertInfluence=s;}

};

#endif // DIJKSTRA_H
