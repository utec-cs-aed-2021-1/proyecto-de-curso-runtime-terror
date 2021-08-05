/*
    Testeado con el problema de SPOJ : https://www.spoj.com/problems/MST/

    Accepted

*/
#include <bits/stdc++.h>
using namespace std;

template<typename TV, typename TE>
class Graph{
protected:
//   sf::RenderWindow* window;
    int cur_vertex = 0, cur_edge = 0;

    vector<TV> data; // data[i] = data del i-esimo vertice
    vector<TE> weight; // weight[i] = peso de la i-esima arista 
    map< pair<int,int> , int> num_edges; // dado un par de vertices devuelve el numero de la arista
    vector<string> names;
    unordered_map< string,int>  vertexes; // dado el id devuelve el numero del vertice
    vector< vector< pair<int,int> > > adj; // lista de adjacencia (numero vecino, id de la arista)
    bool is_directed = false;

public:
    void size() {
        cout << data.size() << endl;
        cout << weight.size();
    }
    bool is_directed2() {return is_directed;}

    template <typename VT,typename ET> friend vector<int> dfs_graph(Graph<VT,ET>& graph);
    template <typename VT,typename ET> friend vector<int> bfs_graph(Graph<VT,ET>& graph, int root);

    template <typename VT,typename ET> friend vector<ET> dijkstra(Graph<VT,ET>& graph, TE inf, int root);
    template <typename VT,typename ET> friend Graph<VT,ET> kruskal(Graph<VT,ET>& graph);
    template <typename VT,typename ET> friend Graph<VT,ET> prim(Graph<VT,ET>& graph, ET inf);

//    Graph(/*sf::RenderWindow* wnd, */ bool directed = false ): /*window{wnd}*/{is_directed = directed;}

    TV getDataById(string id) {
        int index = vertexes[id];
        return data[index];
    }

    Graph(bool directed = false){
        is_directed = directed;
    }

    Graph<TV,TE>& operator = (const Graph<TV,TE>& another) {
        this->cur_vertex = another.cur_vertex;
        this->cur_edge = another.cur_edge;
        this->data = another.data;
        this->weight = another.weight;
        this->num_edges = another.num_edges;
        this->names = another.names;
        this->vertexes = another.vertexes;
        this->adj = another.adj;
        this->is_directed = another.is_directed;
        return *this;
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
    int number_connected_components(){
        if(is_directed) return false;
        vector<bool> vis(cur_vertex,false);
        int cont = 0,ans = 0;
        function <void(int)> dfs = [&](int u){
     
            vis[u] = true;
            for(auto v:adj[u]){
                if(!vis[v.first]) dfs(v.first);
            }
            cont++;
        };
        for(int i = 0; i < cur_vertex; i++)
            if(!vis[i]) ans++,dfs(i);
        return ans; 
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
    void display() {
        /*
        for(int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < adj[i].size(); ++j) {
                json temp1 = data[i];
                json temp2 = data[adj[i][j].first];
                sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(convert_to<double>(temp1["Longitude"].template get<string>())*scalar+centerx, convert_to<double>(temp1["Latitude"].template get<string>())*scalar+centery)),
                        sf::Vertex(sf::Vector2f(convert_to<double>(temp2["Longitude"].template get<string>())*scalar+centerx, convert_to<double>(temp2["Latitude"].template get<string>())*scalar+centery))
                };
                window->draw(line, 2, sf::Lines);
            }
        }

        for (auto &p: data) {
            sf::CircleShape shape(5);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(convert_to<double>(p["Longitude"].template get<string>()) * scalar+centerx,
                              convert_to<double>(p["Latitude"].template get<string>()) * scalar+centery);
            window->draw(shape);
        }
        */
    }

};

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
    return ans;

}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    Graph<int,int> g;
    for(int i = 1; i <= n; i++) g.insertVertex(to_string(i),i);
    int u,v,w;
    for(int i = 0; i < m ; i++){
        cin >> u >> v >> w;
        g.createEdge(to_string(u),to_string(v),w);
    }
    auto mst =  kruskal(g);


    return 0;
}