#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;


template<typename TV, typename TE>
class Graph{
private:
    int number_vertexes = 0,cur_vertex = 0;
    vector<TV> data; // data[i] = data del i-esimo vertice
    vector<TE> weight; // weight[i] = peso de la i-esima arista 
//    unordered_map< pair<int,int> , int> num_edges; // dado un par de vertices devuelve el numero de la arista
    unordered_map< string,int>  vertexes; // dado el id devuelve el numero del vertice
    vector< vector< pair<int,int> > > adj; // lista de adjacencia (numero vecino, id de la arista)
    bool is_directed = false;

public:
    Graph(bool directed = false){
        is_directed = directed;
    }
    bool insertVertex(string id, TV vertex){
        if(vertexes[id] != 0) return false;
        data.emplace_back(vertex);
        adj.emplace_back(vector<pair<int,int> > ());
        vertexes[id] = cur_vertex++;
        number_vertexes++;
        return true;
    }  
    bool createEdge(string id1, string id2, TE w){

    }     
    bool deleteVertex(string id) = 0;     
    bool deleteEdge(string id) = 0;   
    TE &operator()(string start, string end)= 0;  
    float density() = 0;
    bool isDense(float threshold = 0.5) = 0;
    bool isConnected()= 0;
    bool isStronglyConnected() {
        if(!is_directed) return false;
        // KOSARAJU ALGORITHM IS OVERKILL 


    }
    bool empty();
    void clear()= 0;  
      
    void displayVertex(string id)= 0;
    bool findById(string id) = 0;
    void display() = 0;

   
   
    
    
    friend Graph<TV,TE> Kruskal(Graph<TV,TE> g);

    template<typename TV,typename TE>
    friend Graph<TV,TE> Prim(Graph<TV,TE> g);
    
    template<typename TV,typename TE>
    friend void Dijkstra(Graph<TV,TE> g);

    template<typename TV,typename TE>
    friend void Astar(Graph<TV,TE> g);
};


#endif