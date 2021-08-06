#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_DIJKSTRA_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_DIJKSTRA_H

template <typename VT,typename ET>
Graph<VT,ET> dijkstra(Graph<VT,ET>& graph, ET inf, string ver){
    vector<ET> dis(graph.cur_vertex);
    priority_queue< pair<ET,int> , vector< pair<ET,int> >, greater< pair<ET,int> > > q;
    for(int i = 0; i < graph.cur_vertex; i++) dis[i] = inf; // TIPO DE DATO?
    vector<int> parent(graph.cur_vertex);
    vector<ET> weight(graph.cur_vertex);
    Graph<VT,ET> tree;
    
    for(int i = 0; i < graph.cur_vertex; i++) 
        tree.insertVertex(graph.names[i],graph.data[i]);
    
    int root = graph.vertexes[ver];
    dis[root] = 0;
    q.push({0,root});
    

    while(!q.empty()){
        auto aux = q.top();
        q.pop();
        int u = aux.second;
        if(dis[u] < aux.first) continue;
        for(auto v:graph.adj[u]){
            if(dis[v.first] > dis[u] + graph.weight[v.second]){
                parent[v.first] = u;
                weight[v.first] = graph.weight[v.second];
                dis[v.first] = dis[u] + graph.weight[v.second];
                q.push({dis[v.first],v.first} );
            }
        }
    }
    
    for(int i = 0; i < graph.cur_vertex; i++){
        if(i == root) continue;
        tree.createEdge(graph.names[i],graph.names[parent[i]],weight[i]);
    }

    return tree;
}

#endif