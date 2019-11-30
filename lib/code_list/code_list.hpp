#if !defined(__CODE_LIST_HPP__)
#define __CODE_LIST_HPP__

#include<list>
#include<string>

namespace MipsCode
{
	class CodeNode;
	class CodeList;
}

class MipsCode::CodeNode
{
	public:
		std::string instruction;
		std::string param1;
		std::string param2;
		std::string param3;

		CodeNode();
		CodeNode(std::string, std::string = "", std::string = "", std::string = "");
		std::string toString();
};

class MipsCode::CodeList
{
	public:
		std::list<CodeNode> code_list;
};

#endif // __CODE_LIST_HPP__
