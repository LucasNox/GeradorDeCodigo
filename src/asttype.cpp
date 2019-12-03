#include "asttype.hpp"

// separa subexpressões
std::vector<std::string> get_sub_exps(std::string exp)
{
    std::vector<std::string> result;
    std::string aux;
    size_t level = 0;
    for (size_t i = 0; i < exp.size(); i++)
    {
        if (exp[i] == '(')
        {
            if (level >= 1)
                aux += exp[i];
            level++;
        }
        else if (exp[i] == ')')
        {
            level--;
            if (level >= 1)
                aux += exp[i];
            else
                result.push_back(aux);
        }
        else if (exp[i] == ',')
        {
            if (level == 1)
                result.push_back(aux),
                    aux.clear();
            else
                aux += exp[i];
        }
        else
            aux += exp[i];
    }
    return result;
}

//! extra funcions
EXP_TYPE get_unary_type(std::string exp_string)
{
    static std::string operators = "+ - * ++ -- ~ ! &";
    size_t pos_found = operators.find(exp_string);
    switch (pos_found)
    {
    case 0:
        return EXP_TYPE::UNARY_PLUS;
    case 2:
        return EXP_TYPE::UNARY_MINUS;
    case 4:
        return EXP_TYPE::UNARY_POINTER;
    case 6:
        return EXP_TYPE::UNARY_INC;
    case 9:
        return EXP_TYPE::UNARY_DEC;
    case 12:
        return EXP_TYPE::UNARY_BITWISE_NOT;
    case 14:
        return EXP_TYPE::UNARY_NOT;
    case 16:
        return EXP_TYPE::UNARY_BITWISE_AND;
    default:
        return EXP_TYPE::NONE;
    }
}
// Dado inicio de uma expressão retora o tipo binário
EXP_TYPE get_binary_type(std::string exp_string)
{
    static std::string operators = "+ - * / % & | ^ && || == != < > <= >= >> << = += -=";
    size_t pos_found = operators.find(exp_string);
    switch (pos_found)
    {
    case 0:
        return EXP_TYPE::BINARY_PLUS;
    case 2:
        return EXP_TYPE::BINARY_MINUS;
    case 4:
        return EXP_TYPE::BINARY_MULTIPLY;
    case 6:
        return EXP_TYPE::BINARY_DIV;
    case 8:
        return EXP_TYPE::BINARY_REMAINDER;
    case 10:
        return EXP_TYPE::BINARY_BITWISE_AND;
    case 12:
        return EXP_TYPE::BINARY_BITWISE_OR;
    case 14:
        return EXP_TYPE::BINARY_BITWISE_XOR;
    case 16:
        return EXP_TYPE::BINARY_LOGICAL_AND;
    case 19:
        return EXP_TYPE::BINARY_LOGICAL_OR;
    case 22:
        return EXP_TYPE::BINARY_EQUAL;
    case 25:
        return EXP_TYPE::BINARY_NOT_EQUAL;
    case 28:
        return EXP_TYPE::BINARY_LESS_THAN;
    case 30:
        return EXP_TYPE::BINARY_GREATER_THAN;
    case 32:
        return EXP_TYPE::BINARY_LESS_EQUAL;
    case 35:
        return EXP_TYPE::BINARY_GREATER_EQUAL;
    case 38:
        return EXP_TYPE::BINARY_R_SHIFT;
    case 41:
        return EXP_TYPE::BINARY_L_SHIFT;
    case 44:
        return EXP_TYPE::BINARY_ASSIGN;
    case 46:
        return EXP_TYPE::BINARY_ADD_ASSIGN;
    case 49:
        return EXP_TYPE::BINARY_MINUS_ASSIGN;
    default:
        return EXP_TYPE::NONE;
    }
}

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

#define MACRO_1(x)                        \
    if (x->isValid() == true)             \
    {                                     \
        this->class_ptr = x;              \
        this->action_type = x->getType(); \
        return;                           \
    }

asttp::action::action(std::string act_str)
{
    // checar se não é uma expressão
    asttp::expression *new_exp = new asttp::expression(act_str);
    if (new_exp->exp_type != EXP_TYPE::NONE)
    {
        this->class_ptr = new_exp;
        this->action_type == ACT_TYPE::NONE;
        return;
    }
    // checar se não é um comando
    asttp::command::DOWHILE *new_dowhile = new asttp::command::DOWHILE(act_str);
    MACRO_1(new_dowhile);
    asttp::command::EXIT *new_exit = new asttp::command::EXIT(act_str);
    MACRO_1(new_exit);
    // asttp::command::FOR *new_for = new asttp::command::FOR(act_str);
    // MACRO_1(new_for);
    // asttp::command::IF *new_if = new asttp::command::IF(act_str);
    // MACRO_1(new_if);
    // asttp::command::PRINTF *new_printf = new asttp::command::PRINTF(act_str);
    // MACRO_1(new_printf);
    // asttp::command::SCANF *new_scanf = new asttp::command::SCANF(act_str);
    // MACRO_1(new_scanf);
    // asttp::command::WHILE *new_while = new asttp::command::WHILE(act_str);
    // MACRO_1(new_while);
    // checar se não é uma chamada de função
    // asttp::command::FUNC_CALL *new_funccall = new asttp::command::FUNC_CALL(act_str);
    // MACRO_1(new_funccall);
    // checar se é variável ou constante
}

asttp::expression::expression(std::string exp_str)
{
    this->exp_type = EXP_TYPE::NONE;
    size_t pos_open = exp_str.find('(');
    if (pos_open == std::string::npos)
        return; // não é expressão
    // capturando subexpressões
    std::vector<std::string> subexps = get_sub_exps(std::string(exp_str, pos_open, exp_str.size() - pos_open - 1));
    // se tem duas subexpressões, é pq é binário
    if (subexps.size() == 2)
        this->exp_type = get_binary_type(std::string(exp_str, 0, pos_open));
    else if (subexps.size() == 1)
        this->exp_type = get_unary_type(std::string(exp_str, 0, pos_open));
    else
        return; // erro ???
    // colocando sub arvore sempre à esquerda
    this->left_act = new asttp::action(subexps[0]);
    if (subexps.size() == 2)
        this->right_act = new asttp::action(subexps[1]);
}

asttp::action::~action()
{
}

asttp::command::DOWHILE::DOWHILE(std::string dowhile_str)
{
    // ver se o início é igual
    size_t pos_open = dowhile_str.find('(');
    static std::string comp_string = "DO_WHILE";
    size_t pos_found = comp_string.find(std::string(dowhile_str, 0, pos_open));
    if (pos_found == std::string::npos)
        return; // não é um do_while
    // separar subexpressões
    std::vector<std::string> subexps = get_sub_exps(std::string());
    for (size_t i = 0; i >= subexps.size() - 1; i++)
        this->actions.push_back(new asttp::action(subexps[i]));
    // pegar ultima para condicional
    this->condition = new asttp::action(subexps.back());
}

bool asttp::command::DOWHILE::isValid()
{
    if (this->actions.size() != 0 and this->condition != nullptr)
        return true;
    return false;
}

ACT_TYPE asttp::command::DOWHILE::getType()
{
    return ACT_TYPE::COMM_DO_WHILE;
}
asttp::command::EXIT::EXIT(std::string exit_str)
{
    // ver se o início é igual
    size_t pos_open = exit_str.find('(');
    static std::string comp_string = "EXIT";
    size_t pos_found = comp_string.find(std::string(exit_str, 0, pos_open));
    if (pos_found == std::string::npos)
        return; // não é um do_while
    // separar subexpressões
    this->action = new asttp::action(std::string(exit_str, pos_found + 1, exit_str.size() - pos_found - 1));
}

bool asttp::command::EXIT::isValid()
{
    if (this->action != nullptr)
        return true;
    return false;
}

ACT_TYPE asttp::command::EXIT::getType()
{
    return ACT_TYPE::COMM_DO_WHILE;
}