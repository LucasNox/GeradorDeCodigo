#include "live_analysis.hpp"

using namespace MipsCode;

/*
    TODO:
        - Definir: Separa código em blocos e roda algoritmo para blocos? Ou trata como monólito?

    NOTES:
        - Tipos de instrução relevantes: Definição e uso
            - Definição (sempre define apenas 1): 
                ADD(1º), ADDI(1º), ADDU(1º), ADDIU(1º), 
                SUB(1º), SUBU(1º), 
                MUL(1º), 
                AND(1º), OR(1º), ANDI(1º), ORI(1º), SLL(1º), SRL(1º)
                LW(1º), SW(memória --> 1º), LUI(1º) ?
                MFHI(1º), MFLO(1º)
                SLT(1º), SLTI(1º)

            - Uso:
                ADD(2 --> 2, 3), ADDI(1 -> 2), ADDU(2 -> 2, 3), ADDIU(1 -> 2),
                SUB(2 --> 2, 3), SUBU(2 -> 2, 3),
                MUL(2 --> 2, 3),
                AND(2 --> 2, 3), OR(2 -> 2, 3), ANDI(1 -> 2), ORI(1 -> 2), SLL(1 -> 2), SRL(1 -> 2)
                LW, SW, LUI ?
                MFHI, MFLO --> hi e lo especificamente, contam?
                BEQ(2 --> 1, 2), BNE(2 --> 1, 2)
                SLT(2 --> 2, 3), SLTI(1 --> 2)
                JR(1 --> 1)

        - Instruções Especiais:
            - Pulos:
                BEQ, BNE, J, JR, JAL
*/

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
    // Modifica liveness --> TODO: registro para resultados de liveness linha a linha/bloco a bloco?

    // Lista com ponto a ponto da liveness analysis
    std::list<AnalysisNode*> liveness_list; 
    
    for(auto i = CODELIST.end; i != CODELIST.begin; i--)
    {
        // Cria novo nó na lista de liveness analysis
        AnalysisNode* node = new AnalysisNode(*i);

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
! checkInstructionVariables(): Verifica se existem variáveis na instrução.
*/
void checkInstructionVariables()
{

}

/*
! getInstructionDef(): Obtem variáveis que a instrução define.
*/
void getInstructionDef()
{

}

/*
! getInstructionUse(): Obtem variáveis que a instrução usa.
*/
void getInstructionUse()
{

}