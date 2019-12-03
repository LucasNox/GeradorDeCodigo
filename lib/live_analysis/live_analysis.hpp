#ifndef LIVE_ANALYSIS_HPP
#define LIVE_ANALYSIS_HPP

#include "../code_list/code_list.hpp"
#include "blocks.hpp"
#include <algorithm>
#include <vector>

class AnalysisNode
{
    public:
        std::vector<std::string> alive_before;
        std::vector<std::string> alive_after;

        MipsCode::CodeNode node;

        AnalysisNode();
        AnalysisNode(MipsCode::CodeNode);
};

#endif // !LIVE_ANALYSIS_HPP