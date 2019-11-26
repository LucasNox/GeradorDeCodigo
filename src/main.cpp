#include <iostream>
#include <list>
#include "ast.hpp"
int main()
{
    std::vector<std::string> raw_lines;
	// obetendo linhas da entrada !
	std::string arg_input;
	while (std::getline(std::cin, arg_input))
		raw_lines.push_back(arg_input);
    // raw_lines.reverse();
    // for (auto &&i : raw_lines)
    //     std::cout << i << std::endl;
    // talvez eu troque para ele rodar uma função na main (ou em uma classe chamada Parser) que vai inserindo as coisas na ast
    // Atualmente ele vai criar a ast a partir das linhas de entrada de forma direta
    Ast originalAst = Ast(raw_lines);
    return 0;
}
