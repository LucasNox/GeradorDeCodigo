#include "ast.hpp"
#include <cstring>
#include <iostream>
static std::vector<char *> get_tokens(const char *str, const char *substr)
{
    std::vector<char *> tokens;
    char *m_str = (char *)calloc(std::strlen(str) + 1, sizeof(char));
    std::strcpy(m_str, str);
    tokens.push_back(m_str);
    char *temp = std::strtok(m_str, substr);
    while (temp != NULL && std::strlen(temp) > 0)
    {
        tokens.push_back(temp);
        temp = std::strtok(NULL, substr);
    }
    return tokens;
}
static bool add_constant(const char *c_str, std::map<std::string, int> *constants)
{
    std::clog << "Adicionando CONSTANT\n";
    std::vector<char *> tokens = get_tokens(c_str, " ");
    if (tokens.size() != 4) // caso não tenha o formato correto
    {
        std::clog << "Erro ao adicionar constante! [quantidade incorreta de parametros]\n";
        return false;
    }
    constants[0][tokens[1]] = std::atoi(tokens[3]); // inserindo chave
    free(tokens[0]);
    return true;
}
static bool add_variable(const char *c_str, std::map<std::string, asttp::variable *> *global_vars)
{
    std::clog << "Adicionando variável\n";
    std::vector<char *> tokens = get_tokens(c_str, " ");
    if (tokens.size() != 4) // caso não tenha o formato correto
    {
        std::clog << "Erro ao adicionar variavel global! [quantidade incorreta de parametros]\n";
        return false;
    }
    asttp::variable *new_var = new asttp::variable(tokens[1], tokens[3]);
    global_vars[0][tokens[1]] = new_var;
    free(tokens[0]);
    return true;
}
static bool add_command(const char *c_str, std::vector<asttp::action *> *global_vars)
{
    switch (c_str[0])
    {
    case 'D': // DO-WHILE
        break;
    case 'I': // IF
        break;
    case 'W': // WHILE
        break;
    case 'F': // FOR
        break;
    case 'P': // PRINTF
        
        break;
    case 'S': // SCANF
        break;
    case 'E': // EXIT
        break;
    case 'R': // RETURN
        break;

    default:
        break;
    }
    return true;
}

Ast::Ast(std::vector<std::string> raw_lines)
{
    this->constants = new std::map<std::string, int>;
    this->global_variables = new std::map<std::string, asttp::variable *>;
    this->main_variables = new std::map<std::string, asttp::variable *>;
    this->action_list = new std::vector<asttp::action *>;
    for (size_t i = 0; i < raw_lines.size(); ++i)
    {
        bool stop_flag = false;
        switch (raw_lines[i][0])
        {
        // CONSTANT: h
        // GLOBAL VARIABLE: j
        // FUNCTION
        // VARIABLE: j
        case 'C': // CONSTANT
            stop_flag = !add_constant(raw_lines[i].c_str() + 10, this->constants);
            break;
        case 'G':
            stop_flag = !add_variable(raw_lines[i].c_str() + 17, this->global_variables);
            break;
        case 'F':
            // função
            break;
        case 'V':
            stop_flag = !add_variable(raw_lines[i].c_str() + 10, this->main_variables);
            break;
        default:
            stop_flag = !add_command(raw_lines[i].c_str(), this->action_list);
            break;
        }
        if (stop_flag)
        {
            std::clog << "Erro na criação da AST!\n";
            break;
        }
    }
    for (auto &&key : *this->constants)
        std::clog << "CONSTANTE: " << key.first << " = " << key.second << "\n";
    for (auto &&key : *this->global_variables)
        std::clog << "VARIÁVEL GLOBAL: " << key.first << " = " << key.second->toString() << "\n";
    for (auto &&key : *this->main_variables)
        std::clog << "VARIÁVEL MAIN: " << key.first << " = " << key.second->toString() << "\n";
}

Ast::~Ast()
{
    delete this->constants;
    for (auto &&entry : *this->global_variables)
        delete entry.second;
    delete this->global_variables;
    for (auto &&entry : *this->main_variables)
        delete entry.second;
    delete this->main_variables;
    for (auto &&entry : *this->action_list)
        delete entry;
    delete this->action_list;
}