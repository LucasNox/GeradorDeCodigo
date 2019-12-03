#ifndef __GRAPH_CLASS__
#define __GRAPH_CLASS__
#include "./Node.hpp"
#include <string>
#include <vector>
#include <map>
class Graph
{
public:
    // int id;
    // int grau;
    // int cor;
    // std::vector<int> vizinhos;
    // std::vector<Node *> variables;
    std::map<int, Node*> varList;
    std::map<int, std::map<int, bool>> matrix;

    Graph();
    ~Graph();
    // Adciona uma nova variável
    bool operator<<(Node *var);
    // Imprime cada lista de nós com as adjacências
    void print();
    // Retorna o ponteiro de um nó com dado id
    Node *getNode(int id);
};

#endif // __GRAPH_CLASS__