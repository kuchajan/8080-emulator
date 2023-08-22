#pragma once

namespace m8080 {
    using sbyte = char;
	using byte = unsigned char;
	using word = unsigned short;

	struct SStatus;

    class CCPU;
    class CMemory;
}

struct m8080::SStatus {
	byte S : 1; // Sign
    byte Z : 1; // Zero
    byte U1: 1; // Unused - always 0
    byte AC: 1; // Auxilary Carry
    byte U2: 1; // Unused - always 0
    byte P : 1; // Parity
    byte U3: 1; // Unused - always 1
    byte C : 1; // Carry
};

class m8080::CMemory {
private:
    static constexpr unsigned int maxSize = 65536; // 2 ^ 16
public:
    byte* data;

    CMemory();
    CMemory(const CMemory& src);
    CMemory(CMemory&& src);
    ~CMemory();

    void clear();

    byte operator[](unsigned int address) const;
    byte& operator[](unsigned int address);
};

// intel 8080 is little endian

class m8080::CCPU {
private:
    CMemory m_mem; // represents connected devices
    // Registers

    word SP, PC;
    byte A, B, C, D, E, H, L;

    //Program status
    union 
    {
        byte PS;
        SStatus flag;
    };

    // Internal routines

    byte readByte(word address);
    word readWord(word address);
    void writeByte(word address, byte data);
    void writeWord(word address, word data);

    byte fetchByte();
    word fetchWord();

    void push(word data);
    word pop();
public:
    CCPU(const CMemory & mem);

    void reset();
    void step();
};
