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