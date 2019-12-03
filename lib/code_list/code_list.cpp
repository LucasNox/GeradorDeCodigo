#include "code_list.hpp"
#include<sstream>

CodeNode::CodeNode(std::string instruction, std::string param_space, std::string param_comma1, std::string param_comma2, std::string param_parentheses_const, std::string param_parentheses)
{
	//Colocando os parametros no objeto
	this->instruction = instruction;
	this->param_space = param_space;
	this->param_comma1 = param_comma1;
	this->param_comma2 = param_comma2;
	this->param_parentheses_const = param_parentheses_const;
	this->param_parentheses = param_parentheses;
}

std::string CodeNode::toString()
{
	std::ostringstream buffer;
	buffer << this->instruction;
	
	if(this->param_space.compare("") != 0)
	{
		buffer << " " << this->param_space;
	}
	if(this->param_comma1.compare("") != 0)
	{
		buffer << ", " << this->param_comma1;
	}
	if(this->param_comma2.compare("") != 0)
	{
		buffer << ", " << this->param_comma2;
	}
	if(this->param_parentheses_const.compare("") != 0)
	{
		buffer << ", " << this->param_parentheses_const;
		if(this->param_parentheses.compare("") != 0)
		{
			buffer << "(" << this->param_parentheses << ")";
		}
	}
	else if(this->param_parentheses.compare("") != 0)
	{
		buffer << ", (" << this->param_parentheses << ")";
	}
	return buffer.str();
}