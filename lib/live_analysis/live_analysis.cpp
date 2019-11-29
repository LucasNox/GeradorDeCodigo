#include "live_analysis.hpp"

using namespace MipsCode;

/*
    TODO:
        - Definir: Separa código em blocos e roda algoritmo para blocos? Ou trata como monólito?
*/

/*
! runLivenessAnalysis: Executa função principal da análise.
*/
void runLivenessAnalysis()
{
    // Percorre a lista de nós de código
    // A cada nó executa checkInstructionVariables
    // Verifica variáveis definidas e usadas por instrução
    // Modifica liveness --> TODO: registro para resultados de liveness linha a linha/bloco a bloco?
}

/*
! checkInstructionVariables: Verifica se existem variáveis na instrução.
*/
void checkInstructionVariables()
{

}

/*
! getInstructionDef: Obtem variáveis que a instrução define.
*/
void getInstructionDef()
{

}

/*
! getInstructionUse: Obtem variáveis que a instrução usa.
*/
void getInstructionUse()
{

}