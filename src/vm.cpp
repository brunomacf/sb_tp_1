#include <cstdio>
#include <iostream>
#include "vm.hpp"

VM::VM() {

}

void VM::run(std::string & path) {
    std::cout << "file_path = " << path << std::endl;
}

// Essa função obtém o valor de um registrador.
int16_t VM::getRegVal(RegID id) {
    
}

// Essa função estabelece o valor de um operando.
void VM::setRegVal(RegID id, int16_t val) {

}

/*
// Funções que executam cada uma das instruções definidas na especificação.
void mov( int16_t op1, int16_t op2, OperandsType type );
void add( int16_t op1, int16_t op2, OperandsType type );
void sub( int16_t op1, int16_t op2, OperandsType type );
void mul( int16_t op1, bool isByteOp1, OperandsType type );
void div( int16_t op1, bool isByteOp1, OperandsType type );
void and( int16_t op1, int16_t op2, OperandsType type );
void not( int16_t op1, OperandsType type );
void or( int16_t op1, int16_t op2, OperandsType type );
void cmp( int16_t op1, int16_t op2, OperandsType type );
void jmp( int16_t op1 );
void jz( int16_t op1 );
void js( int16_t op1 );
void call( int16_t op1 );
void push( int16_t op1, OperandsType type );
void pop( int16_t op1, OperandsType type );
void read( int16_t op1, OperandsType type );
void write( int16_t op1, OperandsType type );
void ret();
void dump();
void htl();

void VM::mov( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::add( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::sub( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::mul( word op1, bool isByteOp1, OPERANDS_TYPE type) {
}

void VM::div( word op1, bool isByteOp1, OPERANDS_TYPE type) {
}

void VM::and( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::not( word op1, OPERANDS_TYPE type) {
}

void VM::or( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::cmp( word op1, word op2, OPERANDS_TYPE type) {
}

void VM::jmp( word op1 ) {
}

void VM::jz( word op1 ) {
}

void VM::js( word op1 ) {
}

void VM::call( word op1 ) {
}

void VM::push( word op1, OPERANDS_TYPE type) {
}

void VM::pop( word op1, OPERANDS_TYPE type) {
}

void VM::read( word op1, OPERANDS_TYPE type) {
}

void VM::write( word op1, OPERANDS_TYPE type) {
}

void VM::ret() {
}

void VM::dump() {
}

void VM::htl() {
}*/
