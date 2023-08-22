#include <iostream>

#include "m8080.hpp"

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
