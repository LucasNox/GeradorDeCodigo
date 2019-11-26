#if !defined(__AST_TYPE_HPP__)
#define __AST_TYPE_HPP__
#include <map>
#include <string>
#include <vector>

namespace asttp
{
class variable;
class function;
class command;
class expression;
namespace command_class
{
class IF;
class DOWHILE;
class WHILE;
class FOR;
class PRINTF;
class SCANF;
class EXIT;
class RETURN;
} // namespace command_class

} // namespace asttp

enum VAR_TYPE
{
    INT,
    INT_VECT,
    CHAR,
    CHAR_VECT,
    VOID,
    VOID_VECT
};

enum COMM_TYPE
{
    DO_WHILE,
    IF,
    WHILE,
    FOR,
    PRINTF,
    SCANF,
    EXIT,
    RETURN
};

enum EXP_TYPE
{
    NONE,
    VARIABLE,
    CONSTANT,
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
    UNARY_BITWISE_AND
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
    int return_type;
    std::map<std::string, asttp::variable> paramter_variables;
    std::map<std::string, asttp::variable> variables_list;
    std::vector<asttp::command> command_list;

    function(std::string new_name, int new_return_type)
        : name(new_name),
          return_type(new_return_type) {}
    // ~function();
    bool addParamter(asttp::variable);
    bool addVariable(asttp::variable);
    bool addCommand(asttp::variable);
    // bool deleteCommand(int pos); //? talvez seja necessário
};

class asttp::command
{
public:
    void *command_ptr;
    COMM_TYPE command_type;
    command(std::string comm_str);
    // ~command(); // vai drestuir o comando devidamente quando o destrutor for chamado
};

class asttp::expression
{
public:
    EXP_TYPE type;
    expression *right_exp;
    expression *left_exp;
    std::string var_name;
    expression(std::string exp_str);
    ~expression();
};

class asttp::command_class::DOWHILE
{
public:
    std::vector<command *> commands;
    asttp::expression *condition;
    DOWHILE(std::string dowhile_str);
    ~DOWHILE();
};

#endif // __AST_TYPE_HPP__
