#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_FLOYD_WARSHALL_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_FLOYD_WARSHALL_H
#include <vector>
#include <limits>

template<typename VT, typename ET>
vector<vector<ET>> floyd_warshall(Graph<VT,ET>& graph, ET inf, int root = 0) {
    int n = graph.data.size();

    vector<vector<ET>> d(n, vector<ET>(n,inf));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(graph.num_edges[{i,j}] == ET{})
                d[i][j] = inf;
            else
                d[i][j] = graph.weight[graph.num_edges[{i,j}]];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < inf && d[k][j] < inf)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    return d;
}





#endif //PROYECTO_DE_CURSO_RUNTIME_TERROR_FLOYD_WARSHALL_H
