#include <cstdio>
#include <iostream>
#include <string>
#include "vm.hpp"

int main(int argc, char *argv[]) {

    if(argc < 2) {printf("Usage : <file_path>\n");  return 1;}

    std::string file_path = argv[1];

    VM vm;
    vm.run(file_path);



    //VM vm;

    //vm.run(argv[1])





    // Instancia os registradores da máquina
    // Instancia a memória principal
    //int8_t, int16_t is the type we want.


    // Crie uma memória que armazena 1000 palavras sequenciais de 16 bits (= 2 bytes).
    // As instrução estão no seguinte formato : (OP, TYPE, ARG1, ARG2) onde OP, TYPE
    // possuem 1 byte cada e os argumentos possuem 2 bytes cada (e sua presença ou
    // não depende de TYPE). Assim, uma instrução pode ter 2 bytes (OP,TYPE) de tamanho,
    // 4 bytes (caso tenha apenas ARG1) ou 6 bytes (caso tenha ARG1 e ARG2).
    // Leia as instruções sequenciamente do arquivo fonte e carregue-as na memória
    // principal.

    // (1) leia o arquivo fonte uma linha por vez.
    // (2) para cada linha quebre em tokens
    // (3) converta o 1o token para o código da operação e adicione à memória
    // (4) os próximos tokens indicam a configuração dos operandos :
    //      * 0 = não existe próximo token (sem operandos)
    //      * 1 = existe um único operando : nome de um registrador
    //      * 2 = existe um único operando : uma posição de memória (decimal de 0 a 1000)
    //      * 3 = existem dois operandos : um nome de registrador e uma posição de memória
    //      * 4 = existem dois operandos : uma posição de memória e um nome de registrador
    //      * 5 = existem dois operandos : dois nomes de registradores
    //      * 6 = existem dois operandos : uma posição de memória e um imediato (valor haxadecimal)
    //      * 7 = existem dois operandos : o nome de um registrador e um imediato
    //      * 8 = existe um único operando : imediato
    // Adiciona o identificador da configuração na memória
    // (5) Adicione à memória os operandos

    // 2 Classes = compilador (lingagem de montagem => linguagem de máquina)
    //

    // (1) leia o arquivo em linguagem de máquina (compilado)
    // (2) set n = 0 e tome linha[n] (2 bytes)
    // (3) tome op com o byte mais significativo de linha[n] e type como o byte menos significativo de linha[n]
    //     op determina a operação e, portanto, o número de operandos
    //     type determina o tipo de cada operando
    // (4) chame a função op(type, op1, op2) que vai obter o valor dos operandos de acordo com type, operar
    // esses valores e armazenar o resultado no local apropriado.



    // Instancia máquina virtual para execução do programa.

}
