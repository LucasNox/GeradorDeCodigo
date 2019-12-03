#if !defined(__CODE_LIST_HPP__)
#define __CODE_LIST_HPP__
#include<list>
#include<string>

class CodeNode
{
	class CodeNode;
	class CodeList;
}

class MipsCode::CodeNode
{
	std::string instruction;
	std::string param1;
	std::string param2;
	std::string param3;

	CodeNode(std::string, std::string = "", std::string = "", std::string = "");
	std::string toString();
};

class MipsCode::CodeList
{
	std::list<CodeNode> code_list;
};

#endif // __CODE_LIST_HPP__
