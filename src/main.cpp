#include <iostream>

#include "m8080.hpp"

int main() {
    using namespace std;
    using namespace m8080;
    
    CMemory mem;
    mem[0x0000] = 0x01;
    mem[0x0001] = 0xad;
    mem[0x0002] = 0xde;
    mem[0x0003] = 0x62;
    CCPU cpu(mem);
    cpu.READY = 1;
    cpu.RESET = 1;
    cpu.step();
    cpu.RESET = 0;
    
    while(true) {
        cpu.step();
    }

    return 0;
}