#include <list>
#include <string>
#include "prog_din.hpp"

//Classe com dados extra da expressão
class ExpWrapper
{
	public:
		//Tipo de nó de expressão
		EXPRESSION_TYPE type;
		//Lista de tokens descrevendo a árvore abaixo deste nó
		std::list<ExpNode *> tokens;
		//Objeto com os dados da 
		matchResult *pattern_matched;
		//Estrutura básica onde fica a expressão, caso seja necessário usa-la
		asttp::action *action;
		//Nó da esquerda
		ExpWrapper *l_exp;
		//Nó da direita
		ExpWrapper *r_exp;
		
		//Construtor padrão
		ExpWrapper()
		{
			this->pattern_matched = nullptr;
			this->action = nullptr;
			this->l_exp = nullptr;
			this->r_exp = nullptr;
		}
};

//Construtor de ProgDin
ProgDin::ProgDin() 
{
	//Inicializa o ID inicial como 1 para os futuros padrões
	this->current_id_pattern = 1;
}

//Função para adicionar um padrão de arvore no objeto da programação dinamica
int ProgDin::addPattern(std::list<ExpNode*> list, std::string instruction, int cost)
{
	//Adiciona uma entrada com o EXPRESSION_TYPE inicial com um ID unico
	this->operator_id.insert(std::make_pair(list.front()->type, this->current_id_pattern));
	//Cria um PatternData para o padrão usando o ID
	PatternData *ptdata = new PatternData();
	ptdata->ID = current_id_pattern;
	ptdata->cost = cost;
	ptdata->instruction = instruction;
	ptdata->tree_pattern = list;
	//Insere o PatternData num map com o ID unico
	this->id_treePattern.insert(std::make_pair(this->current_id_pattern, ptdata));
	return this->current_id_pattern++;
}

//Função que retorna a lista de instruções da expressão raiz fornecida
ExpWrapper *ProgDin::runProgDin(asttp::action *exp_root)
{
	//Insere os nós na estrutura ExpWrapper
	ExpWrapper *exp_rootw = wrapExpression(exp_root);
	//Cria a lista de tokens descrevendo a sub-arvore de cada nó
	tokenizeExpression(exp_rootw);
	//Chama a função recursiva que ira casar os padrões em cada nó
	evaluateCost(exp_rootw, this);
}

//Função que "embrulha" as expressões com um wrapper a fim de ajudar nas proximas funções
ExpWrapper *wrapExpression(asttp::action *exp)
{
	//Verifica se o nó é null
	if(exp == nullptr)
		return nullptr;
	//Cria o wrapper de expressão
	ExpWrapper *expw = new ExpWrapper();
	expw->action = exp;
	//Analisa o tipo de action para adicionar o tipo correto
	if(exp->action_type == ACT_TYPE::EXPRESSION)
	{
		expw->type = (EXPRESSION_TYPE) static_cast<asttp::expression *>(exp->class_ptr)->exp_type;
		expw->l_exp = wrapExpression(static_cast<asttp::expression *>(exp->class_ptr)->right_act);
		expw->l_exp = wrapExpression(static_cast<asttp::expression *>(exp->class_ptr)->left_act);
	}
	else if(exp->action_type == ACT_TYPE::FUNCTION_CALL)
	{
		expw->type = EXPRESSION_TYPE::FUNCTION_CALL;
	}
	else if(exp->action_type == ACT_TYPE::VAR_ACCESS)
	{
		expw->type = EXPRESSION_TYPE::VAR_ACCESS;
	}
	else
	{
		expw->type = EXPRESSION_TYPE::CONSTANT_USE;
	}
	
	return expw;
}

//Função onde é criado uma lista de tokens em cada nó que representa a sub-arvore onde o dado nó é raiz
void tokenizeExpression(ExpWrapper *exp)
{
	if(exp == nullptr)
		return;
	//Realiza a tokenização
	searchTokens(exp, exp, 0);
	//Desce recursivamente para os proximos nós realizando a tokenização
	tokenizeExpression(exp->l_exp);
	tokenizeExpression(exp->r_exp);
}

//Função que realiza a tokenização
void searchTokens(ExpWrapper *exp_root, ExpWrapper *exp, int depth)
{
	if(exp == nullptr)
		return;
	//Cria um objeto do token
	ExpNode *node = new ExpNode();
	//Adiciona o tipo dele, a profundidade e um ponteiro para o ExpWrapper para auxilio futuro
	node->type = exp->type;
	node->depth = depth;
	node->expw = exp; 
	//Adiciona no fim da lista
	exp_root->tokens.push_back(node);
	//Desce recursivamente tokenizando os proximos nós
	searchTokens(exp_root, exp->l_exp, depth + 1);
	searchTokens(exp_root, exp->r_exp, depth + 1);
	return;
}

//Função onde é casado um padrão de arvore e dado seu custo
void evaluateCost(ExpWrapper *exp, ProgDin *pg)
{
	if(exp == nullptr)
		return;
	//Desce recursivamente para iniciar a avaliação nos nós mais profundos
	evaluateCost(exp->l_exp, pg);
	evaluateCost(exp->r_exp, pg);

	// std::pair< std::multimap< EXPRESSION_TYPE, int >::iterator, std::multimap<EXPRESSION_TYPE, int>::iterator > it_pair = pg->operator_id.equal_range(exp->type);
	// std::multimap<EXPRESSION_TYPE, int>::iterator it = it_pair.first;
	//Objeto para armazenar o melhor padrão encontrado de todos os padrões avaliados para o nó atual
	matchResult *best_result;
	auto it_pair = pg->operator_id.equal_range(exp->type);
	for(auto it = it_pair.first; it != it_pair.second; it++)
	{
		//Chama a função de casamento de padrão que resultará num objeto de resultado
		matchResult *result = matchingPattern(exp, it->second, pg);
		//O objeto de resultado é avaliado contra o melhor encontrado anteriormente, e se este for melhor que o anterior, passará a ser o melhor resultado
		if(result->pattern != 0 && result->total_cost < best_result->total_cost)
		{
			best_result = result;
		}
	}
	//Feita a analise de todos os padrões possiveis, o objeto do melhor resultado é armazenado no ExpWrapper do nó atual
	exp->pattern_matched = best_result;
}

// Uma classe que armazena um resultado de matchingPattern, possuindo o custo total do padrão, a lista de nós anexados e o ID do padrão
class matchResult
{
	public:
	int total_cost;
	std::list<ExpWrapper*> exp_attached;
	int pattern;

	matchResult()
	{
		this->total_cost = 0;
		this->pattern = 0;
	}
};

//Função que testa um casamento de padrão de arvore no nó analisado
matchResult *matchingPattern(ExpWrapper *exp, int id, ProgDin *pg)
{
	//Ultima profundida onde houve um anexo
	int last_depth = 0;
	//Booleano de analise de profundidade
	bool analize_depth = false;
	//Cria uma instancia de matchResult
	matchResult *result = new matchResult();

	//Iterador contendo padrão de arvore do ID único
	auto it_map = pg->id_treePattern.find(id);
	//Pegando unico padrão de arvore correspondente ao ID
	auto list = it_map->second->tree_pattern;
	//Neste for é inicializado o iterador it_listp (iterador da lista do padrão de arvore) e
	//o iterador it_listt (iterador da lista de tokens da expressão). O for roda enquanto nenhum iterador chegar ao fim.
	auto it_listp = list.begin(), it_listt = exp->tokens.begin();
	for(; it_listp != list.end() && it_listt != exp->tokens.end();
		it_listp++, it_listt++)
	{
		//Primeiro pegamos os nós de cada iterador
		ExpNode *nodep = *it_listp;
		ExpNode *nodet = *it_listt;
		//Caso analize_depth esteja true, este for itera sobre it_listt até que encontre um token que tenha depth menor ou igual à last_depth
		//Isso é usado para subir na sub-arvore do nó exp analisado após encontrar um EXPRESSION_TYPE::ANYTHING na it_listp, que indica um ponto de anexo que recebe qualquer sub-padrão
		for(; analize_depth && it_listt != exp->tokens.end(); it_listt++)
		{
			if((*it_listt)->depth <= last_depth)
			{
				analize_depth = false;
				break;
			}
		}
		//Vericação extra caso o for acima tenha acabado devido ter chegado ao fim da lista
		if(it_listt == exp->tokens.end())
			break;
		//Caso seja esperado um tipo ANYTHING, significa que é um anexo para o resto da sub-arvore, onde não é necessario ser um tipo especifico 
		if(nodep->type == EXPRESSION_TYPE::ANYTHING && nodep->depth == nodet->depth)
		{
			//Adiciona o ExpWrapper* do token que será anexado numa lista de anexos no result.
			result->exp_attached.push_back(nodet->expw);
			//Adiciona o custo do nó anexado ao custo total do result
			result->total_cost += nodet->expw->pattern_matched->total_cost;
			//Deixa analize_depth como true para subir na sub-arvore do nó anexado
			analize_depth = true;
			//Marca a profundidade desejada de analise como sendo igual à do nó anexado
			last_depth = nodet->depth;
		}
		//Caso não seja um ANYTHING, ele deve ser compativel com o mesmo tipo e mesma profundidade, se não for, o padrão não é casado imediatamente
		else if(nodep->type != nodet->type || nodep->depth != nodet->depth)
		{
			result->total_cost = 0;
			result->pattern = 0;
			return result;
		}
	}
	//Passado do for anterior, o padrão somente é casado no caso de ambos os iteradores chegarem ao fim juntos
	if(it_listt == exp->tokens.end() && it_listp == list.end())
	{
		result->total_cost += it_map->second->cost;
		return result;
	}
	else
	{
		result->total_cost = 0;
		result->pattern = 0;
		return result;
	}
}

//Função onde é preparado um objeto ProgDin que realiza a programação dinamica para instruções de código assembly MIPS
ProgDin MIPS_INSTRUCTIONS()
{
	// ProgDin pg = ProgDin();
	// std::list<EXPRESSION_TYPE> elist;

	// elist = std::list<EXPRESSION_TYPE>({EXPRESSION_TYPE::CONSTANT_USE});
	// pg.assignInstruction(pg.addPattern(elist), "addi");
	// elist = std::list<EXPRESSION_TYPE>({EXPRESSION_TYPE::BINARY_PLUS, EXPRESSION_TYPE::ANYTHING, EXPRESSION_TYPE::ANYTHING});
	// pg.assignInstruction(pg.addPattern(elist), "add");
	// elist = std::list<EXPRESSION_TYPE>({EXPRESSION_TYPE::BINARY_PLUS, EXPRESSION_TYPE::ANYTHING, EXPRESSION_TYPE::CONSTANT_USE});
	// pg.assignInstruction(pg.addPattern(elist), "addi");

}