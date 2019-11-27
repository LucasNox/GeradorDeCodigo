#include "code_list.hpp"
#include<sstream>

MipsCode::CodeNode::CodeNode(std::string instruction, std::string param1, std::string param2, std::string param3)
{
	//Colocando os parametros no objeto
	this->instruction = instruction;
	this->param1 = param1;
	this->param2 = param2;
	this->param3 = param3;
}

std::string MipsCode::CodeNode::toString()
{
	std::ostringstream buffer;
	buffer << this->instruction;
	
	if(this->param1.compare("") != 0)
	{
		buffer << " " << this->param1;
		if(this->param2.compare("") != 0)
		{
			buffer << ", " << this->param2;
			if(this->param3.compare("") != 0)
			{
				buffer << ", " << this->param3;
			}
		}
	}
	return buffer.str();
}