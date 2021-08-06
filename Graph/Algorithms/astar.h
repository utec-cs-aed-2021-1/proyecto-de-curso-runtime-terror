#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_ASTAR_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_ASTAR_H



template <typename VT,typename ET>
Graph<VT,ET> astar(Graph<VT,ET>& graph, vector<ET> heuristic, ET inf, string s_ver , string t_ver ){
    while(heuristic.size() < graph.cur_vertex)
            heuristic.push_back( rand()  %  int(inf/(graph.cur_vertex+1)) );
    vector<ET> dis(graph.cur_vertex);
    priority_queue< pair<ET,int> , vector< pair<ET,int> >, greater< pair<ET,int> > > q;
    for(int i = 0; i < graph.cur_vertex; i++) dis[i] = inf; // TIPO DE DATO?
    int s = graph.vertexes[s_ver], t = graph.vertexes[t_ver];
    for(int i = 0; i < graph.cur_vertex; i++) dis[i] = inf; // TIPO DE DATO?
    vector<int> parent(graph.cur_vertex);
    vector<ET> weight(graph.cur_vertex);
    Graph<VT,ET> tree;
    
    for(int i = 0; i < graph.cur_vertex; i++) 
        tree.insertVertex(graph.names[i],graph.data[i]);
    
    int root = graph.vertexes[s_ver];

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
                parent[v.first] = u;
                weight[v.first] = graph.weight[v.second];
                dis[v.first] = dis[u] + graph.weight[v.second] + heuristic[v.first];
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