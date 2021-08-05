#ifndef BESTFIRSTSEARCH
#define BESTFIRSTSEARCH

#include <vector>

template <typename VT,typename ET>
std::vector<int> best_first_search(Graph<VT,ET>& graph, int root = 0, int target = 0){

    vector<bool> vis(graph.cur_vertex,false);
    vector<int> order;

    priority_queue<pair<int,int> , vector< pair<int,int> >, greater< pair<int,int> > > pq;

    pq.push({0, root});
    vis[root] = true;

    while (!pq.empty()) {
        int x = pq.top().second;
        order.push_back(x);
        pq.pop();
        if (x == target)
            break;
        for (int i = 0; i < adj[x].size(); i++) {
            if (!vis[adj[x][i].first]) {
                vis[adj[x][i].first] = true;
                pq.push({graph.weight(adj[x][i].second), graph[x][i].first});
            }
        }
    }
    return order;
}
#endif