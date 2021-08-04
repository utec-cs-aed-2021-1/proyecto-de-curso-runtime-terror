#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_PRIM_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_PRIM_H

template <typename VT,typename ET>
Graph<VT,ET> prim(Graph<VT,ET>& graph, ET inf){
    if(graph.is_directed) return Graph<VT,ET>();
    Graph<VT,ET> ans;
    int n = graph.cur_vertex;
    for(int i = 0; i < n; i++){
        ans.insertVertex(graph.names[i],graph.data[i]);
    }
    vector<ET> min_dis(n,inf), min_ver(n,-1);
    min_dis[0] = 0;
    vector<pair<int,int>> list_edges(graph.cur_edge);
    vector<bool> used(graph.cur_vertex);
    for(auto it:graph.num_edges){
        list_edges[it.second] = it.first;
    }
    set<pair<ET,int>> edges;
    edges.insert({0,0});
    for(int i = 0; i < n; i++){
        if(edges.size() == 0){
            return Graph<VT,ET>();
        }
        int u = edges.begin() -> second;
        used[u] = true;
        edges.erase(edges.begin());
        if(graph.min_ver[u] != -1 ){
            ans.createEdge(graph.names[u],graph.names[graph.min_ver[u]],min_dis[u]);
        }
        for(auto v:graph.adj[u]){
            if(!used[v.first] && graph.weight[v.second] < min_dis[v.first] ){
                if(graph.min_ver[v.second] != -1)
                    edges.erase({min_dis[v.first],graph.min_ver[v.first]});
                min_dis[v.first] = graph.weight[v.second];
                graph.min_ver[v.first] = u;
                edges.insert({min_dis[v.first],v.first});
            }
        }
    }

    return ans;
}



#endif