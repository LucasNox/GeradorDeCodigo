#ifndef __NODE_CLASS__
#define __NODE_CLASS__
#include <vector>
class Node
{
public:
    int id;
    int color;
    bool isRegister;
    std::vector<Node *> adj;

    Node(int id) : id(id), isRegister(false) { this->color = -1; };
    // ~Node();
    // Adciona novo vizinho
    bool operator<<(Node *new_adj);
    // // Compara se um nó é igual ao outro
    // bool operator==(Node comp_node);
    // Verifica se ele pode assumir uma dada cor
    bool checkColorAssign(int color);
    // Define este nó como registrador
    bool defRegister();
};

#endif // __NODE_CLASS__
