#if !defined(__AST_HPP__)
#define __AST_HPP__
#include "asttype.hpp"
#include <map>
#include <string>
#include <vector>
class Ast
{
public:
    std::map<std::string, asttp::variable *> *global_variables;
    std::map<std::string, int> *constants;
    std::map<std::string, asttp::function *> *function_list;
    std::map<std::string, asttp::variable *> *main_variables;
    std::vector<asttp::action *> *action_list;
    Ast(std::vector<std::string> raw_lines);
    ~Ast();
};

#endif // __AST_HPP__
