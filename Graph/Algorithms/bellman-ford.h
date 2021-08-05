#ifndef BELLMANFORD
#define BELLMANFORD

#include <vector>
#include <algorithm>

template <typename VT,typename ET>
std::vector<ET> bellman_ford(Graph<VT,ET>& graph, ET inf, int root = 0){

    vector<ET> dis(graph.cur_vertex, inf);
    if(!graph.is_directed) return dis;

    dis[root] = 0;
    for (int i = 0; i < graph.cur_vertex - 1; i++) {
        for (auto const& [pair, edge]: num_edges)
            dis[pair.second] = min(dis[pair.second], dis[pair.first] + weight[edge]);
    }
    return dis;
};

#endif