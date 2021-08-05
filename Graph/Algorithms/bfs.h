#ifndef BFS_H
#define BFS_H
#include <vector>

template <typename VT,typename ET>
vector<string> bfs_graph(Graph<VT,ET>& graph,string root){
    vector<bool> vis(graph.cur_vertex,false);
    vector<string> order;
    if(graph.vertexes.find(root) == graph.vertexes.end()) return order;
    int r = graph.vertexes[root];
    vis[r] = true;
    queue<int> q;
    q.push(r);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order.push_back(graph.names[u]);
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