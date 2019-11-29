#include "./Node.hpp"

bool Node::operator<<(Node *new_adj)
{
    if(new_adj == nullptr)
        return false;
    std::vector<Node *>::iterator it = this->adj.begin();
    for (size_t i = 0; i < this->adj.size(); i++, ++it)
    {
        if (this->adj[i]->id < new_adj->id)
            continue;
        if (this->adj[i]->id > new_adj->id)
            break;
        if (this->adj[i]->id == new_adj->id)
            return false;
    }
    this->adj.insert(it, new_adj);
    return true;
}

bool Node::checkColorAssign(int color)
{
    for (auto &&i : this->adj)
    {
        if(i->color == color)
            return false;
    }
    this->color = color;
    return true;
}

bool Node::defRegister()
{
    this->isRegister = true;
    this->color = this->id;
    return true;
}
