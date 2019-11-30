#include "live_analysis.hpp"

/*
    TODO:
        - Definir: Separa código em blocos e roda algoritmo para blocos? Ou trata como monólito?
            - Ideia: Tratar como monólito e seguir instruções de jump para fluxo.
*/

using namespace MipsCode;

// INSTRUCTION CATEGORIES
std::vector<std::string> type0 = {"lui", "mfhi", "mflo"};
std::vector<std::string> type1 = {"addi", "addiu", "andi", "ori", "sll", "slr", "lw", "sw", "slti"};
std::vector<std::string> type2 = {"add", "sub", "addu", "subu", "mul", "and", "or", "slt"};
std::vector<std::string> type3 = {"j", "jal"};
std::vector<std::string> type4 = {"jr"};
std::vector<std::string> type5 = {"beq", "bne"};


/*
! AnalysisNode(CodeNode): Construtor que inicializa nó com CodeNode.
*/
AnalysisNode::AnalysisNode(MipsCode::CodeNode node)
{
    this->node = node;
}

/*
! runLivenessAnalysis(): Executa função principal da análise.
*/
void runLivenessAnalysis(std::list<CodeNode> CODELIST)
{
    // Percorre a lista de nós de código
    // A cada nó executa checkInstructionVariables
    // Verifica variáveis definidas e usadas por instrução

    // Declaração de vetores de liveness
    std::vector<std::string> defined;
    std::vector<std::string> used;

    // Lista com ponto a ponto da liveness analysis
    std::list<AnalysisNode*> liveness_list; 
    
    for(auto i = CODELIST.end; i != CODELIST.begin; i--)
    {
        // Cria novo nó na lista de liveness analysis
        AnalysisNode* node = new AnalysisNode(*i);


        // Obtém conjuntos de definição e uso
        switch(checkInstructionType(*i))
        {
            case 0: 
                    defined = getInstructionDef(*i);
                    break;
            case 1: 
                    defined = getInstructionDef(*i);
                    used    = getInstructionUse(*i, 1);
                    break;
            case 2: 
                    defined = getInstructionDef(*i);
                    used    = getInstructionUse(*i, 2);
                    break;
            case 3: 
                    break;
            case 4:
                    used    = getInstructionUse(*i, 4);
                    break;
            case 5:
                    used    = getInstructionUse(*i, 5);
                    break;
        }


        // Verifica casos especiais
        if(i == CODELIST.end) // Última linha de código
        {
            // node->alive_after -> Vazio
            // node->alive_before -> Insere usos
        }
        else if(i == CODELIST.begin) // Primeira linha de código
        {
            // node->alive_after -> Herda do node->alive_before anterior
            // node->alive_before -> Vazio
        }
        else // Linhas intermediárias
        {
            // node->alive_after -> Herda do node->alive_before anterior
            // node->alive_before -> Remove definições, insere usos (em ordem)
        }
        
        liveness_list.insert(i, node);
    }

}

/*
! checkInstructionType(): Verifica distribuição de variáveis na instrução.
    => Tipos:
            TIPO 0 -> DEF
            TIPO 1 -> DEF, USO
            TIPO 2 -> DEF, USO, USO
            TIPO 3 -> JUMPS SEM USO
            TIPO 4 -> JUMPS COM USO
            TIPO 5 -> JUMPS COM USO, USO
*/
int checkInstructionType(MipsCode::CodeNode code)
{
    if(std::find(type0.begin, type0.end, code.instruction)) { return 0; }
    else if(std::find(type1.begin, type1.end, code.instruction)) { return 1; }
    else if(std::find(type2.begin, type2.end, code.instruction)) { return 2; }
    else if(std::find(type3.begin, type3.end, code.instruction)) { return 3; }
    else if(std::find(type4.begin, type4.end, code.instruction)) { return 4; }
    else if(std::find(type5.begin, type5.end, code.instruction)) { return 5; }

    return -1;
}

/*
! getInstructionDef(): Obtem variáveis que a instrução define.
*/
std::vector<std::string> getInstructionDef(MipsCode::CodeNode node)
{
    std::vector<std::string> defined;
    defined.insert(defined.begin, node.param1);
    return defined;
}

/*
! getInstructionUse(): Obtem variáveis que a instrução usa.
*/
std::vector<std::string> getInstructionUse(MipsCode::CodeNode node, int type)
{
    std::vector<std::string> used;

    switch (type)
    {
        case 1:
                used.insert(used.begin, node.param2);
                break;
        case 2:
                used.insert(used.begin, node.param2);
                used.insert(used.begin, node.param3);
                break;
        case 4:
                used.insert(used.begin, node.param1);
                break;
        case 5:
                used.insert(used.begin, node.param1);
                used.insert(used.begin, node.param2);
                break;
    }

    return used;
}