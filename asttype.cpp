#include "asttype.hpp"
asttp::variable::variable(std::string name, std::string type_str)
{
    this->name = name;
    size_t offset = 0;
    // selecionando tipo
    switch (type_str[0])
    {
    case 'i':
        this->variable_type = VAR_TYPE::INT;
        offset = 3;
        break;
    case 'c':
        this->variable_type = VAR_TYPE::CHAR;
        offset = 4;
        break;
    case 'v':
        this->variable_type = VAR_TYPE::VOID;
        offset = 4;
        break;

    default:
        return;
    }
    this->is_pointer = false;
    if (type_str.size() > offset)
    {
        if (type_str[offset] == '[') // se for vetor
        {
            // obtendo valor entra os brackets
            std::string vect_size(type_str.c_str() + offset + 1, type_str.size() - 1);
            this->pointer_level = std::atoi(vect_size.c_str());
            switch (this->variable_type) // trocando tipo de variável para vetor
            {
            case VAR_TYPE::INT:
                this->variable_type = VAR_TYPE::INT_VECT;
                break;
            case VAR_TYPE::CHAR:
                this->variable_type = VAR_TYPE::CHAR_VECT;
                break;
            case VAR_TYPE::VOID:
                this->variable_type = VAR_TYPE::VOID_VECT;
                break;

            default:
                return;
            }
        }
        else
        { // se não for vetor mas tem mais conteudo
            this->is_pointer = true;
            this->pointer_level = type_str.size() - offset;
        }
    }
}
std::string asttp::variable::toString()
{
    std::string out;
    switch (this->variable_type)
    {
    case VAR_TYPE::INT:
        out = "INT";
        break;
    case VAR_TYPE::CHAR:
        out = "CHAR";
        break;
    case VAR_TYPE::VOID:
        out = "VOID";
        break;
    case VAR_TYPE::INT_VECT:
        out = "INT_VECT";
        out.append("[");
        out.append(std::to_string(this->pointer_level));
        out.append("]");
        break;
    case VAR_TYPE::CHAR_VECT:
        out = "CHAR_VECT";
        out.append("[");
        out.append(std::to_string(this->pointer_level));
        out.append("]");
        break;
    case VAR_TYPE::VOID_VECT:
        out = "VOID_VECT";
        out.append("[");
        out.append(std::to_string(this->pointer_level));
        out.append("]");
        break;
    }
    if (this->is_pointer)
        for (int i = 0; i < this->pointer_level; i++)
            out.append("*");
    out.append(" ");
    out.append(this->name);
    return out;
}