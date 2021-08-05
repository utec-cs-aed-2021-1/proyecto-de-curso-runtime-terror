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
#include <limits>
double infinite = numeric_limits<double>::max();
using json = nlohmann::json;
using namespace std;

void astar() {

}

void bellman_ford() {

}

void best_first_search() {

}

void bfs() {

}

void dfs() {

}

void dijkstra() {

}

void floyd_warshall() {

}

void kruskal() {

}

void prim() {
    
}

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

    Graph<json,double> graph;
    Parser parser(R"(C:\Users\Dom\Desktop\utec\4 ciclo\Algoritmos y estructura de datos\proyecto-de-curso-runtime-terror\Parser\Data\pe.json)");
    parser.readJSON();
    parser.GraphMake(graph);
    vector<vector<double>> vec;
    vec = floyd_warshall(graph);
    int op;
    do{
        switch (op) {
            case 1:

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
        }

        break;

    }while (op != 0);




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