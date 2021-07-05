#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

using namespace std;

template<typename TV, typename TE>
class Graph{
protected:
    int cur_vertex = 0, cur_edge = 0;
    vector<TV> data; // data[i] = data del i-esimo vertice
    vector<TE> weight; // weight[i] = peso de la i-esima arista 
    map< pair<int,int> , int> num_edges; // dado un par de vertices devuelve el numero de la arista
    vector<string> names;
    unordered_map< string,int>  vertexes; // dado el id devuelve el numero del vertice
    vector< vector< pair<int,int> > > adj; // lista de adjacencia (numero vecino, id de la arista)
    bool is_directed = false;

public:
    TV getDataById(string id) {
        int index = vertexes[id];
        return data[index];
    }

    Graph(bool directed = false){
        is_directed = directed;
    }


    bool insertVertex(const string& id, TV vertex){
        if(vertexes[id] != 0) return false;
        data.emplace_back(vertex);
        names.push_back(id);
        adj.emplace_back(vector<pair<int,int> > ());
        vertexes[id] = cur_vertex++;
        return true;
    }  
    bool createEdge(string id1, string id2, TE w){
        if(id1 == id2 || vertexes.find(id1) == vertexes.end() || vertexes.find(id2) == vertexes.end())
            return false;
        int u = vertexes[id1], v = vertexes[id2];
     
        if(is_directed){
            if(num_edges.find({u,v}) != num_edges.end()) return false;
            num_edges[{u,v}] = cur_edge++;
            weight.push_back(w);
            adj[u].push_back({v,num_edges[{u,v}]});
        }
        else{
            if(u > v) swap(u,v);
            if(num_edges.find({u,v}) != num_edges.end()) return false;
            num_edges[{u,v}] = cur_edge++;
            weight.push_back(w);
            adj[u].push_back({v,num_edges[{u,v}]});
            adj[v].push_back({u,num_edges[{u,v}]});

        }
   
        return true;
    }
    bool deleteVertex(string id){
        if(vertexes.find(id) == vertexes.end()) return false;
        int ver = vertexes[id];
        Graph<TV,TE> new_graph;
        for(int i = 0; i < cur_vertex; i++){
            if(i == ver) continue;
            new_graph.insertVertex(names[i],data[i]);
        }
        for(int u = 0; u < cur_vertex; u++){
            for(auto v:adj[u]){
                if( (is_directed || ( !is_directed && u < v.first)) && v.first != ver){
                    new_graph.createEdge(names[u],names[v.first],weight[v.second]);
                }
            }
        }
        *this = new_graph;
        return true;
    }    
   
    // TE &operator()(string start, string end)= 0;  
     
    float density(){
        if(cur_vertex < 2) return 0;
        return (  (is_directed?0.5:1.0)*cur_edge/(0.5*(cur_vertex*(cur_vertex-1)) ));
    }
    bool isDense(float threshold = 0.5){
        if(cur_vertex < 2) return false;
        if(threshold < density())
            return true;
        return false;
    }
    bool isConnected(){
        if(is_directed) return false;
        vector<bool> vis(cur_vertex,false);
        int cont = 0;
        function <void(int)> dfs = [&](int u){

            vis[u] = true;
            for(auto v:adj[u]){
                if(!vis[v.first]) dfs(v.first);
            }
            cont++;
        };
        return cont == cur_vertex;
    }
    bool isStronglyConnected() {
        if(!is_directed) return false;
        if(cur_vertex == 0) return true;
        // KOSARAJU ALGORITHM IS OVERKILL?
        int n = cur_vertex;
        vector<bool> vis(n,false);
        vector<int> toposort;
        vector< vector<int> > adj_rev(n);
      
        for(int i = 0; i < n; i++){
            for(auto v:adj[i]){
                adj_rev[v.first].push_back(i);
         //       cout << v.first << " " << i << endl;
            }
        }
     
        function <void(int)> dfs = [&](int u){

            vis[u] = true;
            for(auto v:adj[u]){
                if(!vis[v.first]) dfs(v.first);
            }
            toposort.push_back(u);
        };

        int cont = 0;
        function <void(int)> dfs_rev = [&](int u){
            vis[u] = true;
            cont++;
            for(int v:adj_rev[u]){
                if(!vis[v]) dfs_rev(v);
            }
        };

        for(int i = 0; i < n; i++){
            if(!vis[i]) dfs(i);
        }
        
        int root = toposort[toposort.size() - 1]; 
        for(int i = 0; i < n; i++) vis[i] = false;
        
        dfs_rev(root);       
        // se puede adaptar para obtener las componentes fuertemente conexas facilmente
        if(toposort.size() == n)
            return true;
        return false;
    }
    
    bool empty(){
        return cur_vertex == 0;
    }
    void clear(){
        names.clear();
        data.clear();
        weight.clear();
        vertexes.clear();
        adj.clear();
        num_edges.clear();
        cur_vertex = cur_edge = 0;
    }  
    void displayVertex(string id){
        if(vertexes.find(id) != vertexes.end())
            cout << vertexes[id] <<  " " << data[vertexes[id]] << endl;
        else cout << "-1\n";
    }
    bool findById(string id){
        return vertexes.find(id) != vertexes.end();
    }
    void display(){
        // ¿Que se muestra? 
    }

   

    vector<int> dfs_graph(){
        vector<bool> vis(cur_vertex,false);
        vector<int> order;
        function <void(int)> dfs = [&](int u){
            vis[u] = true;
            order.push_back(u);
            for(auto v:adj[u]){
                if(!vis[v.first]) dfs(v.first);
            }
        };
        for(int i = 0; i < cur_vertex; i++) 
            if(!vis[i]) dfs(i);
        return order;
    }

    vector<int> bfs_graph(int root = 0){
        vector<bool> vis(cur_vertex,false);
        vector<int> order;
        vis[root] = true;
        queue<int> q;
        while(!q.empty()){
            int u = q.front();
            order.push_back(u);
            for(auto v:adj[u]){
                if(!vis[v.first]){
                    vis[v.first] = true;
                    q.push(v.first);
                }
            }
        }
        return order;
    }

    vector<TE> dijkstra(TE inf, int root = 0){
        vector<TE> dis(cur_vertex);
        priority_queue< pair<TE,int> , vector< pair<TE,int> >, greater< pair<TE,int> > > q;
        for(int i = 0; i < cur_vertex; i++) dis[i] = inf; // TIPO DE DATO?
        dis[root] = 0;
        q.push({0,root});
        while(!q.empty()){
            auto aux = q.top();
            q.pop();
            int u = aux.second;
            if(dis[u] < aux.first) continue;             
            for(auto v:adj[u]){
                if(dis[v.first] > dis[u] + weight[v.second]){
                    dis[v.first] = dis[u] + weight[v.second];
                    q.push({dis[v.first],v.first} );
                }
            }
        }

        return dis;
    }

    Graph<TV,TE> kruskal(){
        if(is_directed) return Graph<TV,TE>();
        int n = cur_vertex;
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
        Graph<TV,TE> ans;
        for(int i = 0; i < n; i++){
            ans.insertVertex(names[i],data[i]);
        }
        vector<pair<TE,int>> edges;
        vector<pair<int,int>> list_edges(cur_edge);
        for(int i = 0; i < cur_edge; i++) edges.push_back({weight[i],i});

        for(auto it:num_edges){
            list_edges[it.second] = it.first;
        }

        sort(edges.begin(),edges.end());
        int cont = 0;
        for(int i = 0; i < cur_edge; i++){
            int u = list_edges[ edges[i].second ].first, v = list_edges[ edges[i].second ].second;
            if(uni(u,v)){
                ans.createEdge(names[u],names[v],weight[ edges[i].first ]);
                cont++;
            }
        }
        if(cont < n-1) return Graph<TV,TE>(); 
        return ans;

    }

    Graph<TV,TE> prim(TE inf){
        if(is_directed) return Graph<TV,TE>(); 
        Graph<TV,TE> ans;
        int n = cur_vertex;
        for(int i = 0; i < n; i++){
            ans.insertVertex(names[i],data[i]);
        }
        vector<TE> min_dis(n,inf), min_ver(n,-1);
        min_dis[0] = 0;
        vector<pair<int,int>> list_edges(cur_edge);
        vector<bool> used(cur_vertex);        
        for(auto it:num_edges){
            list_edges[it.second] = it.first;
        }
        set<pair<TE,int>> edges;
        edges.insert({0,0});
        for(int i = 0; i < n; i++){
            if(edges.size() == 0){
                return Graph<TV,TE>(); 
            }
            int u = edges.begin() -> second;
            used[u] = true;
            edges.erase(edges.begin());
            if(min_ver[u] != -1 ){
                ans.createEdge(names[u],names[min_ver[u]],min_dis[u]);
            }
            for(auto v:adj[u]){
                if(!used[v.first] && weight[v.second] < min_dis[v.first] ){
                    if(min_ver[v.second] != -1)
                        edges.erase({min_dis[v.first],min_ver[v.first]});
                    min_dis[v.first] = weight[v.second];
                    min_ver[v.first] = u;
                    edges.insert({min_dis[v.first],v.first});
                }
            }
        }

        return ans;
    }

 
};

#endif