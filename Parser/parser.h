#ifndef PROYECTO_DE_CURSO_RUNTIME_TERROR_PARSER_H
#define PROYECTO_DE_CURSO_RUNTIME_TERROR_PARSER_H

#include "json.hpp"
#include "graph.h"
#include <fstream>
#include <utility>
using json = nlohmann::json;


class Parser{
private:
    json* data;
    string dir;
public:
    Parser(){data = nullptr;}
    Parser(string dir_){data = nullptr; dir = std::move(dir_);}
    void clear(); // Clears parser saved atributes
    void readJSON(); // Parses JSON file and saves data into class NOTE: each derived class has its own readJSON method
    void GraphMake(Graph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph
    void set_dir(string dir_){dir = std::move(dir_)}
};

void Parser::readJSON() {
    if(dir.empty()) return;
    std::ifstream i(dir)        //lee el json
    auto temp = json::parse(i); //convierte el archivo json a
    data = new json;
    *data = temp;
    i.close();
}

void Parser::clear() {
    data = nullptr;
}

template<typename TV, typename TE>
void Parser::GraphMake(Graph<string ,double> &tempGraph) {
    if(data == nullptr) return;
    for(auto & i : *data) {
        tempGraph.insertVertex(i["Airport ID"],i);
        for(int j = 0; j < i["destinations"].size(); ++j)
            tempGraph.createEdge(i["Airport ID"], i["destinations"][j], 5);
    }
}



#endif //PROYECTO_DE_CURSO_RUNTIME_TERROR_PARSER_H
