#include <list>
#include <string>
#include "prog_din.hpp"

class ExpWrapper
{
	public:
		std::list<EXP_TYPE> tokens;
		int total_cost;
		asttp::expression *exp;
		ExpWrapper *l_exp;
		ExpWrapper *r_exp;
		
		ExpWrapper()
		{
			this->total_cost = 0;
			this->exp = nullptr;
			this->l_exp = nullptr;
			this->r_exp = nullptr;
		}
};

int ProgDin::runProgDin(asttp::expression *exp_root)
{
	ExpWrapper *exp_rootw = wrapExpression(exp_root);
	tokenizeExpression(exp_rootw);
}

void ProgDin::addPattern(std::list<EXP_TYPE> list)
{
	this->tree_patterns.insert(std::make_pair(list.front(), list));
}

ExpWrapper *wrapExpression(asttp::expression *exp)
{
	if(exp == nullptr)
		return nullptr;
	ExpWrapper *expw = new ExpWrapper();
	expw->exp = exp;
	expw->l_exp = wrapExpression(exp->left_exp);
	expw->r_exp = wrapExpression(exp->right_exp);
	return expw;
}

void tokenizeExpression(ExpWrapper *exp)
{
	if(exp == nullptr)
		return;
	searchTokens(exp, exp);
	tokenizeExpression(exp->l_exp);
	tokenizeExpression(exp->r_exp);
}

void searchTokens(ExpWrapper *exp_root, ExpWrapper *exp)
{
	if(exp == nullptr)
		return;
	exp_root->tokens.push_back(exp->exp->type);
	searchTokens(exp_root, exp->l_exp);
	searchTokens(exp_root, exp->r_exp);
	return;
}

void evaluateCost(ExpWrapper *exp, std::multimap< EXP_TYPE, std::list<EXP_TYPE> > tree_patterns)
{
	if(exp == nullptr)
		return;
	evaluateCost(exp->l_exp, tree_patterns);
	evaluateCost(exp->r_exp, tree_patterns);
	auto it_pair = tree_patterns.equal_range(exp->tokens.front());
	auto it = it_pair.first;
	for(; it != it_pair.second; it++)
	{
		if(evaluateCostByPattern(exp, it->second))
		{
			//CONTINUAR DAQUI

		}
	}
}

bool evaluateCostByPattern(ExpWrapper *exp, std::list<EXP_TYPE> tree_pattern)
{
	if(exp == nullptr || tree_pattern.empty())
		return false;
	auto it1 = exp->tokens.begin();
	auto it2 = tree_pattern.begin();
	for(; it1 != exp->tokens.end() && it2 != tree_pattern.end(); it1++, it2++)
	{
		if((*it1) != (*it2))
			return false;
	}	
	return true;
}

ProgDin MIPS_INSTRUCTIONS()
{

}