#include <iostream>

//#include "Tester/tester.h"
#include "Parser/parser.h"
#include "json.hpp"
#include "Algorithms/bfs.h"
#include "Algorithms/dijkstra.h"
#include "Algorithms/dfs.h"
#include "Algorithms/prim.h"
#include "Algorithms/kruskal.h"
#include <limits>
long double infinite = numeric_limits<double>::max();
using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[]) {
    /*
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    //Tester::executeExamples();
    // Tester::executeParser();
    Graph<json,double> graph;
    Parser parser(R"(C:\Users\Dom\Desktop\utec\4 ciclo\Algoritmos y estructura de datos\proyecto-de-curso-runtime-terror\Parser\Data\airports.json)");
    parser.readJSON();
    parser.GraphMake(graph);
    vector<double> vec;
    vec = graph.dijkstra(infinite,0);
    cout << graph.density()<<endl;
    for(auto &i : vec){
        cout << i << ", ";
    }

    */
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    Graph<json,double> graph;
    Parser parser(R"(C:\Users\Dom\Desktop\utec\4 ciclo\Algoritmos y estructura de datos\proyecto-de-curso-runtime-terror\Parser\Data\airports.json)");
    parser.readJSON();
    parser.GraphMake(graph);
    Graph<json, double> graph2(kruskal(graph));
    graph2.size();


    //graph.display();
    //window.display();
    /*
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