#ifndef DFS_H
#define DFS_H
#include <vector>


template <typename VT,typename ET>
vector<string> dfs_graph(Graph<VT,ET>& graph){
    vector<bool> vis(graph.cur_vertex,false);
    vector<string> order;
    function <void(int)> dfs = [&](int u){
        vis[u] = true;
        order.push_back(graph.names[u]);
        for(auto v:graph.adj[u]){
            if(!vis[v.first]) dfs(v.first);
        }
    };
    for(int i = 0; i < graph.cur_vertex; i++)
        if(!vis[i]) dfs(i);
    return order;
}




#endif