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
    bool isValid();
    ACT_TYPE getType();
    std::vector<action *> actions;
    asttp::action *condition;
    DOWHILE(std::string dowhile_str);
    void print();
    ~DOWHILE();
};
class asttp::command::IF
{
public:
    bool isValid();
    ACT_TYPE getType();
    std::vector<action *> then_actions;
    std::vector<action *> else_actions;
    asttp::action *condition;
    IF(std::string if_str);
    void print();
    ~IF();
};
class asttp::command::WHILE
{
public:
    bool isValid();
    ACT_TYPE getType();
    std::vector<action *> actions;
    asttp::action *condition;
    WHILE(std::string while_str);
    void print();
    ~WHILE();
};
class asttp::command::FOR
{
public:
    bool isValid();
    ACT_TYPE getType();
    std::vector<action *> actions;
    asttp::action *initialization;
    asttp::action *condition;
    asttp::action *increment;
    FOR(std::string for_str);
    void print();
    ~FOR();
};
class asttp::command::PRINTF
{
public:
    bool isValid();
    ACT_TYPE getType();
    std::vector<action *> actions;
    std::string to_print;
    PRINTF(std::string printf_str);
    void print();
    ~PRINTF();
};
class asttp::command::SCANF
{
public:
    bool isValid();
    ACT_TYPE getType();
    asttp::expression *pointer;
    std::string to_read;
    SCANF(std::string scanf_str);
    void print();
    ~SCANF();
};
class asttp::command::EXIT
{
public:
    bool isValid();
    ACT_TYPE getType();
    asttp::action *action;
    EXIT(std::string exit_str);
    void print();
    ~EXIT();
};
class asttp::command::RETURN
{
public:
    bool isValid();
    ACT_TYPE getType();
    asttp::action action;
    RETURN(std::string return_str);
    void print();
    ~RETURN();
};
class asttp::command::FUNC_CALL
{
public:
    bool isValid();
    ACT_TYPE getType();
    std::string name;
    std::vector<asttp::action *> params;
    FUNC_CALL(std::string return_str);
    void print();
    ~FUNC_CALL();
};

class asttp::expression
{
public:
    EXP_TYPE exp_type;
    asttp::action *right_act;
    asttp::action *left_act;
    expression(std::string exp_str);
    void print();
    ~expression();
};
#endif // __AST_TYPE_HPP__
