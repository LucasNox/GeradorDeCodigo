#if !defined(__AST_TYPE_HPP__)
#define __AST_TYPE_HPP__
#include <map>
#include <string>
#include <vector>

namespace asttp
{
class variable;
class function;
class action;
class expression;
namespace command
{
class IF;
class DOWHILE;
class WHILE;
class FOR;
class PRINTF;
class SCANF;
class EXIT;
class RETURN;
class FUNC_CALL;
} // namespace command

} // namespace asttp

enum class VAR_TYPE
{
    INT,
    INT_VECT,
    CHAR,
    CHAR_VECT,
    VOID,
    VOID_VECT,
    NONE
};

enum class ACT_TYPE
{
    COMM_DO_WHILE,
    COMM_IF,
    COMM_WHILE,
    COMM_FOR,
    COMM_PRINTF,
    COMM_SCANF,
    COMM_EXIT,
    COMM_RETURN,
    EXPRESSION,
    FUNCTION_CALL,
    VAR_ACCESS,
    CONSTANT_USE,
    NONE
};

enum class EXP_TYPE
{
    BINARY_PLUS,
    BINARY_MINUS,
    BINARY_MULTIPLY,
    BINARY_DIV,
    BINARY_REMAINDER,
    BINARY_BITWISE_AND,
    BINARY_BITWISE_OR,
    BINARY_BITWISE_XOR,
    BINARY_LOGICAL_AND,
    BINARY_LOGICAL_OR,
    BINARY_EQUAL,
    BINARY_NOT_EQUAL,
    BINARY_LESS_THAN,
    BINARY_GREATER_THAN,
    BINARY_LESS_EQUAL,
    BINARY_GREATER_EQUAL,
    BINARY_R_SHIFT,
    BINARY_L_SHIFT,
    BINARY_ASSIGN,
    BINARY_ADD_ASSIGN,
    BINARY_MINUS_ASSIGN,
    UNARY_PLUS,
    UNARY_MINUS,
    UNARY_POINTER,
    UNARY_INC,
    UNARY_DEC,
    UNARY_BITWISE_NOT,
    UNARY_NOT,
    UNARY_BITWISE_AND,
    NONE
};

class asttp::variable
{
public:
    std::string name;
    VAR_TYPE variable_type;
    bool is_pointer;
    int pointer_level;
    variable(std::string new_name, std::string type_str);
    std::string toString();
    // ~variable();
    // bool hasSameName(asttp::variable); //? talvez seja necessário
};

class asttp::function
{
public:
    std::string name;
    VAR_TYPE return_type;
    std::map<std::string, asttp::variable> paramter_variables;
    std::map<std::string, asttp::variable> variables_list;
    std::vector<asttp::action *> command_list;

    function(std::string new_name, VAR_TYPE new_return_type)
        : name(new_name),
          return_type(new_return_type) {}
    // ~function();
    bool addParamter(asttp::variable);
    bool addVariable(asttp::variable);
    bool addCommand(asttp::action *);
    // bool deleteCommand(int pos); //? talvez seja necessário
};

class asttp::action
{
public:
    // tipo da ação
    ACT_TYPE action_type;
    // ponteiro para estrutura: expressaõ, commando, acesso à variável, etc...
    void *class_ptr;
    action(std::string raw_line);
    void print();
    ~action();
};

class asttp::command::DOWHILE
{
public:
    std::vector<action *> actions;
    asttp::action *condition;
    DOWHILE(std::string dowhile_str);
    void print();
    ~DOWHILE();
};

class asttp::expression
{
    public:

    asttp::action* right_act;
    asttp::action* left_act;
    EXP_TYPE exp_type;
    expression(std::string exp_str);
    void print();
    ~expression();
};
#endif // __AST_TYPE_HPP__
