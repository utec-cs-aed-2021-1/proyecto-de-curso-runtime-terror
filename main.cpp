#include <iostream>

//#include "Tester/tester.h"
#include "Parser/parser.h"
#include "json.hpp"
#include "Algorithms/bfs.h"
#include "Algorithms/dijkstra.h"
#include "Algorithms/dfs.h"
#include "Algorithms/prim.h"
#include "Algorithms/kruskal.h"
#include "Algorithms/floyd_warshall.h"
#include "Algorithms/astar.h"

#include <limits>
double infinite = numeric_limits<double>::max();
using json = nlohmann::json;
using namespace std;
template <typename T>
void print_vector(vector<T>& vec) {
    for (auto &i : vec) {
        cout << i << ' ';
    }
}

int main(int argc, char *argv[]) {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Airports");
    Graph<json,double> graph(&window);
    Parser parser(R"(C:\Users\Dom\Desktop\utec\4 ciclo\Algoritmos y estructura de datos\proyecto-de-curso-runtime-terror\Parser\Data\airports.json)"); // puede cambiar airports por pe.json
    parser.readJSON();
    parser.GraphMake(graph);
    /* mostrar solo el grafo de aeropuertos
   graph.display();
   window.display();

   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
       }

   }
     */
    /* mostrar dijkstra
   Graph<json,double> minimun_tree(&window);
   vector<double> vec(18,0.0);
   minimun_tree = dijkstra(graph,infinite,"Bocas Del Toro");
   minimun_tree.display();
   window.display();
   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
       }

   }

    */

    /*mostrar kruskal
    Graph<json,double> minimun_tree(&window);
    vector<double> vec(18,0.0);
    minimun_tree = kruskal(graph);
    minimun_tree.display();
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }
    */

    parser.clear();



    return EXIT_SUCCESS;
}