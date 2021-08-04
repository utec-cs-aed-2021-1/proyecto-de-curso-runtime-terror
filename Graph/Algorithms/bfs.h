#ifndef BFS_H
#define BFS_H
#include <vector>

template <typename VT,typename ET>
vector<int> bfs_graph(Graph<VT,ET>& graph, int root = 0){
    vector<bool> vis(graph.cur_vertex,false);
    vector<int> order;
    vis[root] = true;
    queue<int> q;
    while(!q.empty()){
        int u = q.front();
        order.push_back(u);
        for(auto v:graph.adj[u]){
            if(!vis[v.first]){
                vis[v.first] = true;
                q.push(v.first);
            }
        }
    }
    return order;
}

#endif