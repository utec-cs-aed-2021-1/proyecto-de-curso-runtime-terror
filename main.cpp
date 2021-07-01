#include <iostream>

//#include "Tester/tester.h"
#include "Parser/parser.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    //Tester::executeExamples();
    // Tester::executeParser();
    Graph<json,double> graph;
    Parser parser(R"(C:\Users\Dom\Desktop\utec\4 ciclo\Algoritmos y estructura de datos\proyecto-de-curso-runtime-terror\Parser\Data\pe.json)");
    parser.GraphMake(graph);




    return EXIT_SUCCESS;
}