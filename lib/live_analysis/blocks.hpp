#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include "../code_list/code_list.hpp"
#include <algorithm>
#include <vector>
#include <string>

// INSTRUCTION CATEGORIES
const std::vector<std::string> type0 = {"lui", "mfhi", "mflo"};
const std::vector<std::string> type1 = {"addi", "addiu", "andi", "ori", "sll", "slr", "lw", "sw", "slti"};
const std::vector<std::string> type2 = {"add", "sub", "addu", "subu", "mul", "and", "or", "slt"};
const std::vector<std::string> type3 = {"j", "jal"};
const std::vector<std::string> type4 = {"jr"};
const std::vector<std::string> type5 = {"beq", "bne"};

class Diagram
{
    public:
        std::list<MipsCode::CodeNode> codelist;
        std::list<Block> blocklist;
        
        MipsCode::CodeNode root;

        Diagram();
        void initializeDiagram(std::list<MipsCode::CodeNode> CODELIST);
};

class Block
{
    public:
        MipsCode::CodeNode* start;
        MipsCode::CodeNode* end;

        std::vector<Block> children;

        Block();
        Block(MipsCode::CodeNode*, MipsCode::CodeNode*);
};

#endif // !BLOCKS_HPP