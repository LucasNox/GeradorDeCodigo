#if !defined(__CODE_LIST_HPP__)
#define __CODE_LIST_HPP__
#include<list>
#include<string>

class CodeNode
{
	std::string instruction;
	std::string param_space;
	std::string param_comma1;
	std::string param_comma2;
	std::string param_parentheses_const;
	std::string param_parentheses;

	CodeNode(std::string, std::string = "", std::string = "", std::string = "", std::string = "", std::string = "");
	std::string toString();
};

#endif // __CODE_LIST_HPP__
