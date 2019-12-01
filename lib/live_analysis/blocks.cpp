#include "blocks.hpp"

// INSTRUCTION CATEGORIES
std::vector<std::string> type0 = {"lui", "mfhi", "mflo"};
std::vector<std::string> type1 = {"addi", "addiu", "andi", "ori", "sll", "slr", "lw", "sw", "slti"};
std::vector<std::string> type2 = {"add", "sub", "addu", "subu", "mul", "and", "or", "slt"};
std::vector<std::string> type3 = {"j", "jal"};
std::vector<std::string> type4 = {"jr"};
std::vector<std::string> type5 = {"beq", "bne"};

/*
! Block(CodeNode): Construtor que inicializa bloco com nó de linha de código.
*/
Block::Block(MipsCode::CodeNode node)
{
    this->node = node;
}

/*
! searchTargetLabel(): Busca posição da label alvo da instrução.
*/
MipsCode::CodeNode* searchTargetLabel(std::list<MipsCode::CodeNode> CODELIST, std::string label)
{
    return(std::find_if(CODELIST.begin, CODELIST.end, [] (const MipsCode::CodeNode& node, std::string label) 
    { return node.instruction == label; }));
}

/*
!  getLeaders(): Obtém linhas líderes do código.
    TODO: Função jr;
*/
std::vector<MipsCode::CodeNode*> getLeaders(std::list<MipsCode::CodeNode> CODELIST)
{
    // Inicializa vetor de líderes
    std::vector<MipsCode::CodeNode*> leaders;
    leaders.insert(leaders.begin, CODELIST.begin);

    // Define líderes
    for(auto i = CODELIST.begin+1; i != CODELIST.end; i++)
    {
        // Procura instrução nas listas de jumps

        // Tipo 3 => Sem var, vai para rótulo
        if(std::find(type3.begin, type3.end, (*i).instruction))
        {
            // Marca rótulo alvo como líder
            leaders.insert(leaders.end, searchTargetLabel(CODELIST, (*i).param1));

            // Marca linha seguinte como líder
            leaders.insert(leaders.end, std::next(i));
        }
        // Tipo 4 => Uma var, vai para endereço da variável
        else if(std::find(type4.begin, type4.end, (*i).instruction))
        {
            // Marca endererço alvo como líder

        }
        // Tipo 5 => Duas vars, vai para rótulo
        else if(std::find(type5.begin, type5.end, (*i).instruction))
        {
            // Marca rótulo alvo como líder
            leaders.insert(leaders.end, searchTargetLabel(CODELIST, (*i).param3));

            // Marca linha seguinte como líder
            leaders.insert(leaders.end, std::next(i));
        }
    }

    return leaders;
}

/*
! setBlocks(): Utiliza linhas líderes para dividr código em blocos.
*/
void setBlocks(std::list<MipsCode::CodeNode> CODELIST, std::vector<MipsCode::CodeNode*> leaders)
{

}