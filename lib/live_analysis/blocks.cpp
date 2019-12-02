#include "blocks.hpp"

// INSTRUCTION CATEGORIES
std::vector<std::string> type0 = {"lui", "mfhi", "mflo"};
std::vector<std::string> type1 = {"addi", "addiu", "andi", "ori", "sll", "slr", "lw", "sw", "slti"};
std::vector<std::string> type2 = {"add", "sub", "addu", "subu", "mul", "and", "or", "slt"};
std::vector<std::string> type3 = {"j", "jal"};
std::vector<std::string> type4 = {"jr"};
std::vector<std::string> type5 = {"beq", "bne"};

/*
! initializeDiagram(): Inicializa blocos do diagrama.
*/
void Diagram::initializeDiagram(std::list<MipsCode::CodeNode> CODELIST)
{
    this->codelist = CODELIST;
    this->blocklist = setBlocks(this->codelist, getLeaders(this->codelist));
    linkBlocks(this->blocklist, this->codelist);
}


/*
! Block(CodeNode): Construtor que inicializa bloco com nó de linha de código.
*/
Block::Block(MipsCode::CodeNode* start, MipsCode::CodeNode* end)
{
    this->start = start;
    this->end = end;
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
! searchTargetBlock(): Busca bloco que começa com a label especificada.
*/
Block searchTargetBlock(std::list<Block> BLOCKLIST, std::string label)
{
    for(auto i = BLOCKLIST.begin; i != BLOCKLIST.end; i++)
    {
        if((*i).start == label)
        {
            return (*i);
        }
    }
}

/*
! searchReturnInstruction(): Busca retorno de uma instrução jump-and-link.
*/
MipsCode::CodeNode* searchReturnInstruction(std::list<MipsCode::CodeNode> CODELIST, MipsCode::CodeNode* jal)
{
    auto target = searchTargetLabel(CODELIST, jal->param1);

    for(auto i = target; i != CODELIST.end; i++)
    {
        if((*i).instruction == "jr")
        {
            return i;
        }
    }

    return nullptr;
}

/*
!  getLeaders(): Obtém linhas líderes do código.
*/
std::vector<MipsCode::CodeNode*> getLeaders(std::list<MipsCode::CodeNode> CODELIST)
{
    // Inicializa vetor de líderes
    std::vector<MipsCode::CodeNode*> leaders;
    leaders.insert(leaders.begin, CODELIST.begin);

    // Variável para valor do jal
    MipsCode::CodeNode jumped;

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
            // Marca linha seguinte como líder
            leaders.insert(leaders.end, std::next(i));
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
std::list<Block> setBlocks(std::list<MipsCode::CodeNode> CODELIST, std::vector<MipsCode::CodeNode*> leaders)
{
    std::list<Block> BLOCKLIST;
    MipsCode::CodeNode* start = nullptr;

    for(auto i = CODELIST.begin; i != CODELIST.end; i++)
    {
        if(std::find(leaders.begin, leaders.end, i))
        {
            if(start == nullptr){ start = i; }
            else 
            { 
                BLOCKLIST.insert(BLOCKLIST.end, Block(start, i-1));
                start = i;
            }
        }
    }

    if(start != nullptr)
    { BLOCKLIST.insert(BLOCKLIST.end, Block(start, CODELIST.end)); }

    return BLOCKLIST;
}

/*
! linkBlocks(): Conecta blocos criados de acordo com fluxo de instruções.
*/
void linkBlocks(std::list<Block> BLOCKLIST, std::list<MipsCode::CodeNode> CODELIST)
{
    Diagram diagram;

    // Percorre blocos da lista de blocos
    for(auto i = BLOCKLIST.begin; i != BLOCKLIST.end; i++)
    {
        Block block = (*i);

        // JAL
        if(block.end->instruction == "jal") 
        {  
            Block jr = searchTargetBlock(BLOCKLIST, (*searchReturnInstruction(CODELIST, block.end)).instruction);
            block.children.insert(block.children.end, jr);
        }
        // J
        else if(block.end->instruction == "j")
        {
            Block target = searchTargetBlock(BLOCKLIST, block.end->param1);
            block.children.insert(block.children.end, target);
        }
        // BEQ, BNE
        else if(std::find(type5.begin, type5.end, block.end->instruction)) 
        {  
            // If jumps
            Block target = searchTargetBlock(BLOCKLIST, block.end->param3);
            block.children.insert(block.children.end, target);

            // If not jumps
            
        }
        
    }
}