#include "./Graph.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
int get_num(std::string str, const char *substr)
{
	char *c_str = (char *)calloc(str.size() + 1, sizeof(char));
	std::strcpy(c_str, str.c_str());
	char *c_str_num = std::strtok(c_str, substr);
	int num_graf = std::atoi(c_str_num);
	free(c_str);
	return num_graf;
}
const std::vector<std::string> split_str(const std::string &raw_str, const char &c)
{
	std::string buffer{""};
	std::vector<std::string> vect;
	for (auto raw_c : raw_str)
		if (raw_c != c)
			buffer += raw_c;
		else if (buffer != "")
			vect.push_back(buffer), buffer = "";
	if (buffer != "")
		vect.push_back(buffer);
	return vect;
}
bool regalloc(int num_k, int num_reg, Graph *graph)
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "K = " << num_reg << "\n\n";
	std::vector<int> pilha;
	size_t toStack = graph->varList.size() - num_k;
	bool success = true;
	// empilhando nós para serem pintados
	while (toStack > 0)
	{
		bool toSpill = true;
		int adjAmnt = __INT_MAX__;
		int idToStack = -1;
		// Primeira parte: remover só com K menor
		for (auto &&col : graph->matrix)
		{
			int size = 0;
			for (auto &&lin : col.second)
				if (lin.second == true)
					size++;
			if (size != 0)
				size--;
			if (size >= num_reg or
				size > adjAmnt or
				graph->varList[col.first]->isRegister or
				col.second[col.first] == false)
				continue;
			if (size == adjAmnt)
				if (col.first > idToStack)
					continue;
			adjAmnt = size;
			idToStack = col.first;
			toSpill = false;
		}
		if (toSpill == true)
		{
			adjAmnt = 0;
			for (auto &&col : graph->matrix)
			{
				int size = 0;
				for (auto &&lin : col.second)
					if (lin.second == true)
						size++;
				if (size < adjAmnt or
					graph->varList[col.first]->isRegister or
					col.second[col.first] == false)
					continue;
				if (size == adjAmnt)
					if (col.first > idToStack)
						continue;
				adjAmnt = size;
				idToStack = col.first;
			}
		}
		for (auto &&lin : graph->matrix[idToStack])
		{
			if (graph->varList[lin.first]->isRegister == true)
				continue;
			graph->matrix[lin.first][idToStack] = false;
			lin.second = false;
		}
		toStack--;
		std::cout << "Push: " << idToStack;
		if (toSpill == true)
			std::cout << " *";
		std::cout << "\n";
		pilha.push_back(idToStack);
	}
	// Select/Assign
	std::reverse(pilha.begin(), pilha.end());
	for (auto &&id : pilha)
	{
		for (int color = 0; graph->matrix[id][id] == false && color < num_reg; color++)
		{
			bool canColor = true;
			//? ele ta cuidando quando ele interfere diretamente com o registrador ?
			for (auto &&lin : graph->matrix[id])
			{
				if (lin.second == false)
					continue;
				if (graph->varList[lin.first]->color != color)
					continue;
				canColor = false;
				break;
			}
			if (canColor == false)
				continue;
			for (auto &&lin : graph->matrix[id])
				graph->matrix[lin.first][id] = true;
			graph->varList[id]->color = color;
		}

		std::cout << "Pop: " << id << " -> ";
		if (graph->matrix[id][id] == true and graph->varList[id]->color != -1)
		{
			std::cout << graph->varList[id]->color << std::endl;
			continue;
		}
		std::cout << "NO COLOR AVAILABLE" << std::endl;
		success = false;
		break;
	}

	// Resetando grafo
	for (auto &&i : graph->matrix)
		for (auto &&j : i.second)
			j.second = true;
	for (auto &&var : graph->varList)
	{
		if (var.second->isRegister == false)
			var.second->color = -1;
	}

	return success;
}
int main()
{
	std::list<std::string> raw_lines;
	// obetendo linhas da entrada !
	std::string arg_input;
	while (std::getline(std::cin, arg_input))
		raw_lines.push_front(arg_input);
	raw_lines.reverse();
	// nome do grafo
	int num_graf = get_num(raw_lines.front(), "Ggrafo: ");
	raw_lines.pop_front();
	// Quantidade de cores do grafo
	int num_k = get_num(raw_lines.front(), "Kk=");
	raw_lines.pop_front();
	std::cout << "Graph " << num_graf
			  << " -> Physical Registers: " << num_k
			  << std::endl
			  << "----------------------------------------" << std::endl;
	// Criando nós do grafo
	Graph graph;
	for (int i = 0; i < num_k; i++)
	{
		Node *new_node = new Node(i);
		new_node->defRegister();
		graph << new_node;
	}
	for (auto &&str : raw_lines)
	{
		std::vector<std::string> splited = split_str(str, ' ');
		// pegando id da nova variável
		int regst_id = std::atoi(splited[0].c_str());
		// adicionando nova variável
		Node *new_node = new Node(regst_id);
		graph << new_node;
		// adicionando adjacências
		for (size_t i = 2; i < splited.size(); i++)
		{
			int visi = std::atoi(splited[i].c_str());
			graph.matrix[visi][new_node->id] = true;
			graph.matrix[new_node->id][visi] = true;
		}
	}
	std::vector<bool> results;
	for (int i = num_k; i >= 2; i--)
		results.push_back(regalloc(num_k, i, &graph));
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "----------------------------------------";
	for (auto &&i : results)
	{
		std::cout << std::endl;
		std::cout << "Graph " << num_graf << " -> K = ";
		if (num_k < 10)
			std::cout << " ";
		std::cout << num_k << ": ";
		if (i == true)
			std::cout << "Successful Allocation";
		else
			std::cout << "SPILL";
		--num_k;
	}
	return 0;
}