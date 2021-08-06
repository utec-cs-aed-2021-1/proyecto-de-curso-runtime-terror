#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_ASTAR_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_ASTAR_H
#include "./Graph/graph.h"



template <typename VT,typename ET>
ET astar(Graph<VT,ET>& graph, vector<ET> heuristic, ET inf, int s , int t ){
    while(heuristic.size() < graph.cur_vertex)
            heuristic.push_back( rand()  % (inf/(graph.cur_vertex+1)) );
    vector<ET> dis(graph.cur_vertex);
    priority_queue< pair<ET,int> , vector< pair<ET,int> >, greater< pair<ET,int> > > q;
    for(int i = 0; i < graph.cur_vertex; i++) dis[i] = inf; // TIPO DE DATO?
    dis[s] = heuristic[s];
    q.push({dis[s],s});

    while(!q.empty()){
        auto aux = q.top();
        q.pop();
        int u = aux.second;
        if(u == t) return dis[u];
        if(dis[u] < aux.first) continue;
        for(auto v:graph.adj[u]){
            if( dis[v.first] > dis[u] + graph.weight[v.second] + heuristic[v.first]){
                dis[v.first] = dis[u] + graph.weight[v.second] + heuristic[v.first];
                q.push({dis[v.first],v.first} );
            }
        }
    }

    return inf;
}

#endif