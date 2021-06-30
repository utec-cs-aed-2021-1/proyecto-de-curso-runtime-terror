
#include "./Graph/graph.h"

template<typename TV,typename TE>
friend void Kruskal(Graph<TV,TE> g){
	
}

template<typename TV,typename TE>
class kruskal{
	Graph<TV,TE> graph;
public:
	kruskal();
	kruskal(Graph<TV,TE> g){
		graph = g;
	}
	~kruskal();
	Graph<TV,TE> apply(){
		return graph.Kruskal();
	}
};