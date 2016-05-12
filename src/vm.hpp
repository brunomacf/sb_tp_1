#include <string>
#include <stdint.h>
#include "loader.hpp"

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

public:
    VM();

    // Essa função executa um programa em linguagem de máquina.
    void run( std::string & path );
};

#endif
