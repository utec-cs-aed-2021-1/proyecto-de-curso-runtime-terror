#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_KRUSKAL_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_KRUSKAL_H


template <typename VT,typename ET>
Graph<VT,ET> kruskal(Graph<VT,ET>& graph){
    if(graph.is_directed) return Graph<VT,ET>();
    int n = graph.cur_vertex;
    // DSU
    vector<int> parent(n);
    for(int i = 0; i < n; i++) parent[i] = i;
    function<int(int)> find = [&](int u){
        return (parent[u] == u? u: parent[u] = find(parent[u]));
    };
    function<bool(int,int)> uni = [&](int u,int v){
        u = find(u), v = find(v);
        if(u == v) return false;
        parent[v] = u;
        return true;
    };
    // END DSU
    Graph<VT,ET> ans;
    for(int i = 0; i < n; i++){
        ans.insertVertex(graph.names[i],graph.data[i]);
    }
    vector<pair<ET,int>> edges;
    vector<pair<int,int>> list_edges(graph.cur_edge);

    for(auto it:graph.num_edges){
        list_edges[it.second] = it.first;
        edges.push_back({graph.weight[it.second],it.second});
    }

    sort(edges.begin(),edges.end());
    int cont = 0;
    long long answer = 0;
    for(int i = 0; i < graph.cur_edge; i++){
        int u = list_edges[ edges[i].second ].first, v = list_edges[ edges[i].second ].second;
        if(uni(u,v)){
   
            answer += graph.weight[ edges[i].second];
            ans.createEdge(graph.names[u],graph.names[v],graph.weight[ edges[i].first ]);
            cont++;
        }
    }
    cout << answer << endl;
    return ans;
}


#endif