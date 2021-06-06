#include "dijkstra.h"
#include "array2.h"

Dijkstra::Dijkstra()
{

}

void Dijkstra::DijkstraComputePaths(vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
        if (distance_through_u < min_distance[v]) {
            vertex_queue.erase(std::make_pair(min_distance[v], v));

            min_distance[v] = distance_through_u;
            previous[v] = u;
            vertex_queue.insert(std::make_pair(min_distance[v], v));

        }

        }
    }
}

std::list<vertex_t> Dijkstra::DijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t> &previous)
{
    std::list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}


void Dijkstra::setDijkstra(const ColorField & c)
{

    list=adjacency_list_t(nx*ny);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
        {
            QPoint p(i,j);
            for(int k=0;k<8;k++)
            {
                QPoint b = p + Array2::next[k];
                if (!InsideVertexIndex(b.x(), b.y())) {
                    continue; }
                double h=heights(p,b,c);
                list[index(i,j)].push_back(neighbor(index(b.x(), b.y()),h));
            }
            for(int k=0;k<8;k++)
            {
                QPoint b = p + Array2::next2[k];
                if (!InsideVertexIndex(b.x(), b.y())) {
                    continue; }
                double h=heights(p,b,c);
                list[index(i,j)].push_back(neighbor(index(b.x(), b.y()),h));
            }
            for(int k=0;k<16;k++)
            {
                QPoint b = p + Array2::next3[k];
                if (!InsideVertexIndex(b.x(), b.y())) {
                    continue; }
                double h=heights(p,b,c);
                list[index(i,j)].push_back(neighbor(index(b.x(), b.y()),h));
            }
        }

}

double Dijkstra::Slope(Vec2 a, Vec2 b,double l)
{
    return (fabs(height(a.getx(),a.gety())-height(b.getx(),b.gety()))*(echelle/10))/l;
}

double Dijkstra::heights(QPoint a, QPoint b,const ColorField & c)
{
    int x=a.x();
    int y=a.y();
    double p=0;
    Vec2 pa(x,y);
    Vec2 pb(b.x(),b.y());
    Vec2 le=pa-pb;
    double l=le.norm()*echelle;
    double s=Slope(pa,pb,l);
    if(c.at(x,y)==1)
        p=forestInfluence*150;
    else if(c.at(x,y)==2)
        p=profoundForestInfluence*500;
    else if(c.at(x,y)==3)
        p=watterInfluence*200;
    else if(c.at(x,y)==4)
        p=profoundWattertInfluence*1000;
    if(s<SSeuilMin)
        return l+p;
    else if(s<SSeuilMax)
        return l+SlopeInfluence*s*100*(echelle/10)+p;
    else
        return max_weight;
}

std::vector<std::pair<int,int>> Dijkstra::draw(ColorField & c, Dijkstra d)
{
    std::vector<weight_t> min;
    std::vector<vertex_t> prev;
    d.DijkstraComputePaths(1,list,min,prev);
    std::list<vertex_t> t = d.DijkstraGetShortestPathTo(12000,prev);
    std::vector<std::pair<int,int>> p;
    for(int x : t)
    {
        c.getSet(x)=5;
        p.push_back(transform(x));
    }
    return p;
}
