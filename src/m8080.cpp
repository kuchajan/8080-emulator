#include <iostream>

#include "m8080.hpp"

m8080::word m8080::combineBytes(byte hi, byte lo) {
    return (((word) hi) << 8) | lo;
}

m8080::CMemory::CMemory() {
    data = new byte[maxSize];
}

m8080::CMemory::CMemory(const CMemory& src) {
    data = new byte[maxSize];
    for (unsigned int i = 0; i < maxSize; ++i) {
        data[i] = src.data[i];
    }
}

m8080::CMemory::CMemory(CMemory&& src) : data(src.data) {}

m8080::CMemory::~CMemory() {
    delete[] data;
}

void m8080::CMemory::clear() {
    for (unsigned int i = 0; i < maxSize; ++i) {
        data[i] = 0;
    }
}

m8080::byte m8080::CMemory::operator[](unsigned int address) const {
    if (address >= maxSize) {
        throw std::out_of_range("Address is out of range");
    }
    return data[address];
}

m8080::byte& m8080::CMemory::operator[](unsigned int address) {
    if (address >= maxSize) {
        throw std::out_of_range("Address is out of range");
    }
    return data[address];
}

m8080::byte m8080::CCPU::readByte(word address) {
    return m_mem[address];
}

m8080::word m8080::CCPU::readWord(word address) {
    return ((word) m_mem[address]) | (((word) m_mem[address+1]) << 8);
}

void m8080::CCPU::writeByte(word address, byte data) {
    m_mem[address] = data;
}

m8080::byte m8080::CCPU::fetchByte() {
    return readByte(PC++);
}

m8080::word m8080::CCPU::fetchWord() {
    PC += 2;
    return readWord(PC-2);
}

void m8080::CCPU::push(word data) {
    SP -= 2;
    (void*)data;
}

m8080::word m8080::CCPU::pop() {
    //word tmp = 0;
    SP += 2;
    return 0;
}

m8080::word m8080::CCPU::getWord(byte reg) {
    switch (reg) {
    case 0b00: {
        return combineBytes(B,C);
    }
    case 0b01: {
        return combineBytes(D,E);
    }
    case 0b10: {
        return combineBytes(H,L);
    }
    case 0b11: {
        return SP;
    }
    default:
        throw std::invalid_argument("Invalid address of register.");
    }
}

m8080::byte &m8080::CCPU::interpretRegister(byte reg)
{
    switch (reg) {
    case 0b000: {
        return B;
    }
    case 0b001: {
        return C;
    }
    case 0b010: {
        return D;
    }
    case 0b011: {
        return E;
    }
    case 0b100: {
        return H;
    }
    case 0b101: {
        return L;
    }
    case 0b110: {
        return m_mem[getWord(0b10)];
    }
    case 0b111: {
        return A;
    }
    default: {
        throw std::invalid_argument("Invalid address of register.");
    }
    }
}

m8080::CCPU::CCPU(const CMemory &mem) : m_mem(mem) {
    flag.U1 = 0;
    flag.U2 = 0;
    flag.U3 = 1;
}

/// @brief Simulates one instruction cycle if applicable
void m8080::CCPU::step() {
    if (!READY) { return; }

    if (RESET) {
        PC = 0;
        HALT = false;
        return;
    }

    // TODO: Check and handle interrupt

    if (HALT) { return; }

    // All passed, fetch an instruction
    byte instruction = fetchByte();

    // and execute it
    // LXI
    if(instruction == 0x01) {
        C = fetchByte();
        B = fetchByte();
        return;
    }
    if(instruction == 0x11) {
        E = fetchByte();
        D = fetchByte();
        return;
    }
    if(instruction == 0x21) {
        L = fetchByte();
        H = fetchByte();
        return;
    }
    if(instruction == 0x31) {
        SP = fetchWord();
        return;
    }
}