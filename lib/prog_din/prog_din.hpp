#if !defined(__PROG_DIN_HPP__)
#define __PROG_DIN_HPP__

#include "../../src/asttype.hpp"
#include <map>
#include <list>

class ProgDin
{

	public:
		std::multimap< EXPRESSION_TYPE, int > operator_id;
		std::map< int, PatternData*> id_treePattern;

		int current_id_pattern;
		
		ProgDin();
		ExpWrapper *runProgDin(asttp::action *exp);
        int addPattern(std::list<ExpNode*> list, std::string instruction, int cost);
};

class ExpNode
{
	public:

	EXPRESSION_TYPE type;
	int depth;
	ExpWrapper *expw;

	ExpNode()
	{
		this->type = EXPRESSION_TYPE::NONE;
		this->depth = 0;
		this->expw = nullptr;
	}
};

class PatternData
{
    public:

    int ID;
    std::list<ExpNode*> tree_pattern;
    std::string instruction;
    int cost;

    PatternData()
    {
        this->ID = 0;
        this->cost = 0;
    }
};

enum class EXPRESSION_TYPE
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
    NONE,
	FUNCTION_CALL,
    VAR_ACCESS,
    CONSTANT_USE,
    ANYTHING,
};

ProgDin MIPS_INSTRUCTIONS();

#endif // __PROG_DIN_HPP__
