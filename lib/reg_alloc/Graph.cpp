#include "./Graph.hpp"
#include <cstring>
#include <iostream>

Graph::Graph()
{
}

Graph::~Graph()
{
    if (!this->varList.empty())
        for (auto &&var : this->varList)
            delete var.second;
}

bool Graph::operator<<(Node *var)
{
    this->varList[var->id] = var;
    this->matrix[var->id][var->id] = true;
    return true;
}

void Graph::print()
{
    if (this->matrix.size() > 0)
        for (auto &&i : this->matrix)
        {
            std::cout << "[" << i.first << "]: ";
            for (auto &&j : i.second)
                if (j.first != i.first)
                    if (this->matrix[i.first][j.first] == true)
                        std::cout << j.first << " ";
            std::cout << "\n";
        }

    std::cout << "\n";
}

Node *Graph::getNode(int id)
{
    for (auto &&i : this->varList)
    {
        if (i.first == id)
            return i.second;
    }
    return nullptr;
}
