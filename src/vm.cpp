#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "vm.hpp"

using namespace std;

// Comente para desativar o debug
// #define DEBUG

VM::VM() {
}

int VM::load( std::string & path ) {
    ifstream file(path, ios::in | ios::binary);
    int size = 0;

    // TODO : Verifique tamanho do arquivo para ver se ele possui um multiplo de
    // 16 bits (para que possamos lê-lo de 2 em 2 bytes).

    if(file.is_open()) {
        // Toma o tamanho do arquivo (número de bytes)
        file.seekg (0, ios::end);   // move para o fim
        size = file.tellg();        // conta
        file.seekg (0, ios::beg);   // move para o início

        if(size % 2 != 0) {
            cout << "error : size must be multiple of 2 bytes" << endl; return -1;
        }

        // Lê para a memória.
        file.readsome((char*) &(this->IP), 2);
        file.read((char*)&mem , sizeof(this->mem));

        // Printamos a memória
        #ifdef DEBUG
        for(int i = 0; i < size/2; i++ )
            cout << i << ":" << this->mem[i] << " ";
        cout << endl;
        #endif

        return size/2;
    }

    return -1;
}

// Essa função decodifica a instrução e obtém quantos operandos ela exige.
int VM::decode(int16_t * opId, int16_t * opsType, int16_t * op1, int16_t * op2) {
    int16_t fullVal = this->mem[this->IP];
    *opId = (fullVal >> 8);              // 8 bits mais significativos
    *opsType = (fullVal & 0xff);            // 8 bits menos significativos

    switch (*opId) {
        // Operações com 2 operandos
        case 1:
        case 2:
        case 3:
        case 6:
        case 8:
        case 9: *op1 = this->mem[this->IP+1]; *op2 = this->mem[this->IP+2]; return 2;

        // Operações com 1 operando
        case 4:
        case 5:
        case 7:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 18:
        case 19: *op1 = this->mem[this->IP+1]; return 1;

        // Operações com 0 operandos
        case 14:
        case 17:
        case 20: return 0;
    }

    return -1;
}

// Essa função executa a próxima instrução.
void VM::execute(int16_t opId, int16_t opsType, int16_t op1, int16_t op2) {
    #ifdef DEBUG
    cout << "IP = " << hex << uppercase << setfill('0') << setw(2) << this->IP << endl;
    cout << "opId = " << hex << uppercase << setfill('0') << setw(2) << opId << endl;
    cout << "opsType = " << hex << uppercase << setfill('0') << setw(2) << opsType << endl;
    cout << "------------------------------" << endl;
    #endif

    OperandsType type = static_cast<OperandsType>(opsType);

    switch (opId) {
        // Operações com 2 operandos
        case 1: this->mov_fn(type, op1, op2);break;
        case 2: this->add_fn(type, op1, op2);break;
        case 3: this->sub_fn(type, op1, op2);break;
        case 6: this->and_fn(type, op1, op2);break;
        case 8: this->or_fn(type, op1, op2);break;
        case 9: this->cmp_fn(type, op1, op2);break;

        // Operações com 1 operando
        case 4: this->mul_fn(type, op1);break;
        case 5: this->div_fn(type, op1);break;
        case 7: this->not_fn(type, op1);break;
        case 10: this->jmp_fn(op1);break;
        case 11: this->jz_fn(op1);break;
        case 12: this->js_fn(op1);break;
        case 13: this->call_fn(op1);break;
        case 15: this->push_fn(type, op1);break;
        case 16: this->pop_fn(type, op1);break;
        case 18: this->read_fn(type, op1);break;
        case 19: this->write_fn(type, op1);break;

        // Operações com 0 operandos
        case 14: this->ret_fn();break;
        case 17: this->dump_fn();break;
        case 20: this->htl_fn();break;
    }

    #ifdef DEBUG
    cout << "==============================" << endl;
    #endif

}



void VM::run(std::string & path) {
    
    #ifdef DEBUG
    cout << "file_path = " << path << endl;
    #endif

    // Limpa máquina
    for(int j = 0; j < MEM_SIZE; j++) { this->mem[j] = 0; }
    this->setFlags(1);
    this->IP = 0;
    this->BP = MEM_SIZE+1;
    this->SP = this->BP;

    // Começamos lendo o arquivo
    int size = load(path), i = 0;

    #ifdef DEBUG
    cout << "size = " << size << endl;
    #endif
    // Temos algo com o que trabalhar
    if(size > 0) {
        while(true) {
            int16_t numOps, fullVal, opId, opsType, op1, op2;
            numOps = decode(&opId, &opsType, &op1, &op2);

            // Atualiza o IP
            this->IP += (numOps + 1);

            // Executa a instrução
            execute(opId, opsType, op1, op2);
        }
    }
}

// Essa função obtém o valor de um registrador.
int16_t VM::getRegVal(int16_t reg) {
    switch (reg) {
        case 0: return (this->AX & 0xff);        // 8 bits menos significativos de AX
        case 1: return (this->AX >> 8);          // 8 bits mais significativas de AX
        case 2: return this->AX;
        case 3: return (this->BX & 0xff);        // 8 bits menos significativos de BX
        case 4: return (this->BX >> 8);          // 8 bits mais significativas de BX
        case 5: return this->BX;
        case 6: return (this->CX & 0xff);        // 8 bits menos significativos de CX
        case 7: return (this->CX >> 8);          // 8 bits mais significativas de CX
        case 8: return this->CX;
        default: return -1;
    }
}

// Seta o valor de um registrador.
void VM::setRegVal(int16_t reg, int16_t val) {
    switch (reg) {
        case 0: this->AX = (this->AX & (0xff << 8)) | (0xff & val); break;             // 8 bits menos significativos de AX
        case 1: this->AX = (0xff & this->AX) | (val & (0xff << 8)); break;            // 8 bits mais significativas de AX
        case 2: this->AX = val; break;
        case 3: this->BX = (this->BX & (0xff << 8)) | (0xff & val); break;             // 8 bits menos significativos de AX
        case 4: this->BX = (0xff & this->BX) | (val & (0xff << 8)); break;            // 8 bits mais significativas de AX
        case 5: this->BX = val; break;
        case 6: this->CX = (this->CX & (0xff << 8)) | (0xff & val); break;             // 8 bits menos significativos de AX
        case 7: this->CX = (0xff & this->CX) | (val & (0xff << 8)); break;            // 8 bits mais significativas de AX
        case 8: this->CX = val; break;
    }
}

// Essa função obtém os valores dos operandos.
void VM::getVals(OperandsType type, int16_t op1, int16_t op2, int16_t * val1, int16_t * val2) {
    switch (type) {
        case OperandsType::REG : *(val1) = this->getRegVal(op1); break;
        case OperandsType::MEM : *(val1) = this->mem[op1]; break;
        case OperandsType::VAL : *(val1) = op1; break;
        case OperandsType::REG_MEM : *(val1) = this->getRegVal(op1); *(val2) = this->mem[op2]; break;
        case OperandsType::MEM_REG : *(val1) = this->mem[op1]; *(val2) = this->getRegVal(op2); break;
        case OperandsType::REG_REG : *(val1) = this->getRegVal(op1); *(val2) = this->getRegVal(op2); break;
        case OperandsType::MEM_VAL : *(val1) = this->mem[op1]; *(val2) = op2; break;
        case OperandsType::REG_VAL : *(val1) = this->getRegVal(op1); *(val2) = op2; break;
        case OperandsType::NONE : break;
    }
}

// Configura um valor de acordo com o tipo.
void VM::setVal(OperandsType type, int16_t op, int16_t val) {

    // Guarda resultado
    if(type == OperandsType::REG || type == OperandsType::REG_MEM || type == OperandsType::REG_REG || type == OperandsType::REG_VAL) {
        this->setRegVal(op, val);
        #ifdef DEBUG 
        cout << "set val " << val << ":" << this->getRegVal(op) << " in reg " << op << endl;
        #endif
    }
    else if(type == OperandsType::MEM || type == OperandsType::MEM_REG || type == OperandsType::MEM_VAL) {
        this->mem[op] = val;
        #ifdef DEBUG 
        cout << "set val " << val << ":" << this->mem[op] << " in mem " << op << endl;
        #endif
    }
}

// Seta as flags
void VM::setFlags(int16_t val) {
    if(val < 0) {this->SF = true; this->ZF = false;}
    else if(val == 0) {this->ZF = true; this->SF = false;}
    else {this->SF = false; this->ZF = false;}
}

void VM::mov_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    cout << "mov : " << (int)type << " : " << op1 << " : " << op2 << endl;
    int16_t val1, val2;
    this->getVals(type, op1, op2, &val1, &val2);

    #ifdef DEBUG 
    cout << "    vals : " << val1 << " : " << val2 << endl;
    #endif

    this->setVal(type, op1, val2);
}

void VM::add_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    #ifdef DEBUG 
    cout << "add : " << (int)type << " : " << op1 << " : " << op2 << endl;
    #endif
    int16_t val1, val2;

    this->getVals(type, op1, op2, &val1, &val2);

    // Realiza a operação.
    val1 += val2;

    this->setVal(type, op1, val1);
}

void VM::sub_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    #ifdef DEBUG 
    cout << "sub : " << (int)type << " : " << op1 << " : " << op2 << endl;
    #endif
    int16_t val1, val2;

    this->getVals(type, op1, op2, &val1, &val2);

    #ifdef DEBUG 
    cout << "    vals : " << val1 << " : " << val2 << endl;
    #endif

    // Realiza a operação.
    val1 -= val2;

    this->setFlags(val1);
    this->setVal(type, op1, val1);
}

void VM::and_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    #ifdef DEBUG 
    cout << "and : " << (int)type << " : " << op1 << " : " << op2 << endl;
    #endif
    int16_t val1, val2;

    this->getVals(type, op1, op2, &val1, &val2);

    // Realiza a operação.
    val1 = val1 & val2;

    this->setVal(type, op1, val1);
}



void VM::or_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    #ifdef DEBUG 
    cout << "or : " << (int)type << " : " << op1 << " : " << op2 << endl;
    #endif
    int16_t val1, val2;

    this->getVals(type, op1, op2, &val1, &val2);

    // Realiza a operação.
    val1 = val1 | val2;

    this->setVal(type, op1, val1);
}

void VM::cmp_fn( OperandsType type, int16_t op1, int16_t op2 ) {
    #ifdef DEBUG 
    cout << "cmp : " << (int)type << " : " << op1 << " : " << op2 << endl;
    #endif
    int16_t val1, val2;

    this->getVals(type, op1, op2, &val1, &val2);

    cout << "    vals : " << val1 << " : " << val2 << endl;

    // Realiza a operação.
    val1 -= val2;

    this->setFlags(val1);
}

void VM::mul_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "mul : " << (int)type << " : " << op1 << endl;
    #endif
    int16_t val1;

    // Se op1 é um registrador do tipo byte (AL, AH, BL, BH, CL, CH), então vamos
    // multiplicar com AL e colocar em AX.
    if(type == OperandsType::REG) {
        if(op1 == 0 || op1 == 1 || op1 == 3 || op1 == 4 || op1 == 6 || op1 == 7) {
            val1 = getRegVal(0) * getRegVal(op1);
        }
        else { val1 = getRegVal(2) * getRegVal(op1); }
    } else {
        val1 = getRegVal(2) * this->mem[op1];
    }

    // Set em AX
    this->setVal(OperandsType::REG, 2, val1);

}

void VM::div_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "div : " << (int)type << " : " << op1 << endl;
    #endif
    int16_t val1, val2;

    // Se op1 é um registrador do tipo byte (AL, AH, BL, BH, CL, CH), entao ...
    if(type == OperandsType::REG) {
        val1 = getRegVal(2) / getRegVal(op1);
        val2 = getRegVal(2) % getRegVal(op1);

        if(op1 == 0 || op1 == 1 || op1 == 3 || op1 == 4 || op1 == 6 || op1 == 7) {
            this->setVal(OperandsType::REG, 0, val1); // Set em AL a divisão
            this->setVal(OperandsType::REG, 1, val2); // Set em AH o resto
        }
        else {
            this->setVal(OperandsType::REG, 2, val1); // Set em AX a divisão
            this->setVal(OperandsType::REG, 5, val2); // Set em BX o resto
        }
    } else {
        val1 = getRegVal(2) / this->mem[op1];
        val2 = getRegVal(2) % this->mem[op1];

        this->setVal(OperandsType::REG, 2, val1); // Set em AX a divisão
        this->setVal(OperandsType::REG, 5, val2); // Set em BX o resto
    }
}

void VM::not_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "not : " << (int)type << " : " << op1 << endl;
    #endif
    int16_t val1;

    this->getVals(type, op1, -1, &val1, NULL);

    // Realiza a operação.
    val1 = ~val1;

    this->setVal(type, op1, val1);
}

void VM::jmp_fn( int16_t op1 ) {
    #ifdef DEBUG 
    cout << "jmp : " << op1 << endl;
    #endif

    this->IP = op1;
}

void VM::jz_fn( int16_t op1 ) {
    #ifdef DEBUG
    cout << "jz : " << op1 << endl;
    #endif

    if(this->ZF) {this->IP = op1;}
}

void VM::js_fn( int16_t op1 ) {
    #ifdef DEBUG 
    cout << "js : " << op1 << endl;
    #endif

    if(this->SF) {this->IP = op1;}
}

void VM::call_fn( int16_t op1 ) {
    #ifdef DEBUG 
    cout << "call : " << op1 << endl;
    #endif

    // manual push
    this->mem[this->SP-1] = this->IP;
    this->SP -= 1;

    this->jmp_fn(op1);
}

void VM::push_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "push : " << (int)type << " : " << op1 << endl;
    #endif
    int16_t val1;
    this->getVals(type, op1, -1, &val1, NULL);
    this->mem[this->SP-1] = val1;

    #ifdef DEBUG 
    cout << "    vals : " << val1 << " : " << this->mem[this->SP-1] << endl;
    #endif

    this->SP -= 1;
}

void VM::pop_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "pop : " << (int)type << " : " << op1 << endl;
    #endif
    if(this->SP == this->BP){return;}

    int16_t val1 = this->mem[this->SP];
    this->setVal(type, op1, val1);
    this->SP += 1;
}

void VM::read_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG 
    cout << "read : " << (int)type << " : " << op1 << endl;
    #endif
    int16_t val;
    cout << "enter a value to read: ";
    cin >> hex >> val;

    // Armazenamos o valor.
    if(type == OperandsType::REG) {
        setRegVal(op1, val);
        #ifdef DEBUG 
        cout << "read value = " << getRegVal(op1) << endl;
        #endif
    }
    else if(type == OperandsType::MEM){
        this->mem[op1] = val;
        #ifdef DEBUG 
        cout << "read value = " << this->mem[op1] << endl;
        #endif
    }

    // Configuramos flags
    this->setFlags(val);
}

void VM::write_fn( OperandsType type, int16_t op1 ) {
    #ifdef DEBUG
    cout << "write : " << (int)type << " : " << op1 << endl;
    #endif
    
    if(type == OperandsType::REG)
        cout << hex << uppercase << setfill('0') << setw(4) << getRegVal(op1) << endl;
    else if(type == OperandsType::MEM)
        cout << hex << uppercase << setfill('0') << setw(4) << this->mem[op1] << endl;
}

void VM::ret_fn() {
    #ifdef DEBUG
    cout << "ret" << endl;
    #endif

    // Manual pop
    int16_t val1 = this->mem[this->SP];
    this->SP += 1;

    this->jmp_fn(val1);
}

void VM::dump_fn() {
    #ifdef DEBUG
    cout << "dump" << endl;
    #endif
    cout << hex << uppercase;
    cout << "AX   BX   CX   SP   BP   IP   ZF   SF   " << endl;
    cout <<
        setfill('0') << setw(4) << this->AX << " " <<
        setfill('0') << setw(4) << this->BX << " " <<
        setfill('0') << setw(4) << this->CX << " " <<
        setfill('0') << setw(4) << this->SP << " " <<
        setfill('0') << setw(4) << this->BP << " " <<
        setfill('0') << setw(4) << this->IP << " " <<
        setfill('0') << setw(4) << this->ZF << " " <<
        setfill('0') << setw(4) << this->SF << " " << endl;
}

void VM::htl_fn() {
    #ifdef DEBUG
    cout << "htl" << endl;
    #endif
    exit(0);
}
