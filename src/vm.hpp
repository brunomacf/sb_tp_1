#include <string>
#include <stdint.h>
#include "loader.hpp"

#ifndef VM_H
#define VM_H

#define MEM_SIZE 1000

enum class OperandsType {
  NONE, REG, MEM, REG_MEM, MEM_REG, REG_REG, MEM_VAL, REG_VAL, VAL
};

enum class RegID {
    AL, AH, AX, BH, BL, BX, CL, CH, CX
}

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
    int16_t getRegVal(RegID id);

    // Essa função estabelece o valor de um operando.
    void setRegVal(RegID id, int16_t val);

public:
    VM();

    // Essa função executa um programa em linguagem de máquina.
    void run( std::string & path );
};

#endif
