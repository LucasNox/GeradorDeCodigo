#if !defined(__PROG_DIN_HPP__)
#define __PROG_DIN_HPP__

#include "../../src/asttype.hpp"
#include <map>
#include <list>

class ProgDin
{
	public:
		std::multimap< EXP_TYPE, std::list<EXP_TYPE> > tree_patterns;

		int runProgDin(asttp::expression *exp);
		void addPattern(std::list<EXP_TYPE> list);
};

ProgDin MIPS_INSTRUCTIONS();

#endif // __PROG_DIN_HPP__
