#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_FLOYD_WARSHALL_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_FLOYD_WARSHALL_H
#include <vector>
#include <limits>
double inf = numeric_limits<double>::max();

template<typename VT, typename ET>
vector<vector<ET>> floyd_warshall(Graph<VT,ET>& graph) {
    int n = graph.data.size();

    vector<vector<ET>> d(n, vector<ET>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j] = graph.weight[graph.num_edges[{i,j}]] == 0 ? inf : graph.weight[graph.num_edges[{i,j}]];

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
