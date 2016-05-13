#include <string>
#include <stdint.h>

#ifndef VM_H
#define VM_H

#define MEM_SIZE 1000

enum class OperandsType {
  NONE, REG, MEM, REG_MEM, MEM_REG, REG_REG, MEM_VAL, REG_VAL, VAL
};

// Máquina virtual
class VM {
private:
    // Memória principal
    int16_t mem[MEM_SIZE];

    // Registradores
    int16_t AX, BX, CX, BP, SP, IP;

    // Flags
    bool ZF, SF;

    // Essa função obtém o valor de um registrador.
    int16_t getRegVal(int16_t reg);

    // Seta o valor de um registrador.
    void setRegVal(int16_t reg, int16_t val);

    // Essa função obtém o valor de um registrador.
    void getVals(OperandsType type, int16_t op1, int16_t op2, int16_t * val1, int16_t * val2);

    // Configura um valor de acordo com o tipo.
    void setVal(OperandsType type, int16_t op, int16_t val);

    // Seta as flags
    void setFlags(int16_t val);

    // Essa função carrega o arquivo binário na memória.
    int load(std::string & path);

    // Essa função decodifica a instrução e obtém quantos operandos ela exige.
    int decode(int16_t * opId, int16_t * opsType, int16_t * op1, int16_t * op2);

    // Essa função executa a próxima instrução.
    void execute(int16_t opId, int16_t opsType, int16_t op1, int16_t op2);

    // Funções que executam cada uma das instruções definidas na especificação.
    void mov_fn(OperandsType type, int16_t op1, int16_t op2);
    void add_fn(OperandsType type, int16_t op1, int16_t op2);
    void sub_fn(OperandsType type, int16_t op1, int16_t op2);
    void and_fn(OperandsType type, int16_t op1, int16_t op2);
    void or_fn(OperandsType type, int16_t op1, int16_t op2);
    void cmp_fn(OperandsType type, int16_t op1, int16_t op2);
    void mul_fn(OperandsType type, int16_t op1);
    void div_fn(OperandsType type, int16_t op1);
    void not_fn(OperandsType type, int16_t op1);
    void jmp_fn(int16_t op1);
    void jz_fn(int16_t op1);
    void js_fn(int16_t op1);
    void call_fn(int16_t op1);
    void push_fn(OperandsType type, int16_t op1);
    void pop_fn(OperandsType type, int16_t op1);
    void read_fn(OperandsType type, int16_t op1);
    void write_fn(OperandsType type, int16_t op1);
    void ret_fn();
    void dump_fn();
    void htl_fn();

public:
    VM();

    // Essa função executa um programa em linguagem de máquina.
    void run( std::string & path );
};

#endif
