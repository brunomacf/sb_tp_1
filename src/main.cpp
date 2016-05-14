#include <cstdio>
#include <iostream>
#include <string>
#include "vm.hpp"

int main(int argc, char *argv[]) {
	
	// Testa se o processador é little-endian
	short teste_endian_a = 0, teste_endian_b = 0; 
	char *ptr_teste_b = (char *)&teste_endian_b; 
	teste_endian_a = 0x0102; 
	ptr_teste_b[0] = 0x02; 
	ptr_teste_b[1] = 0x01; 

	if (teste_endian_a != teste_endian_b) { 
		std::cout << "Processador não é little-endian" << std::endl; 
		return -1; 
	} 
	
	if(argc < 2) {printf("Usage : <file_path>\n");  return 1;}

    std::string file_path = argv[1];

    VM vm;
    vm.run(file_path);

}
