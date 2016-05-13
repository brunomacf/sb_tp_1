#include <cstdio>
#include <iostream>
#include <string>
#include "vm.hpp"

int main(int argc, char *argv[]) {

    if(argc < 2) {printf("Usage : <file_path>\n");  return 1;}

    std::string file_path = argv[1];

    VM vm;
    vm.run(file_path);

}
