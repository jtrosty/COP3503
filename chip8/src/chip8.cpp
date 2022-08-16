#include "chip8.h"

void Chip8::initialize() {
    vRegisters = new uint8_t[16];
    memory = new uint8_t[4096];
    programCounter = (memory + 20);
    stack = new uint8_t[32];
    stackPointer = stack;
    memoryStart = memory;
    opcode = 0;
    indexRegister = 0;
}


void Chip8::fetch( uint16_t& _opcode, uint8_t& _programCounter) {
    _opcode = (memory[_programCounter] << 8) | (memory[_programCounter + 1]);
    programCounter = programCounter + 2;
}



void Chip8::decode() {
    uint16_t firstNibble = firstOpcodeNibble(opcode);
    uint16_t secondNibble = secondOpcodeNibble(opcode);
    uint16_t thridNibble = thirdOpcodeNibble(opcode);
    uint16_t fourthNibble = fourthOpcodeNibble(opcode);

    switch (firstNibble)
    {
    case 0x1:
        break;
    case 0x2:
        break;
    case 0x3:
        break;
    case 0x4:
        break;
    case 0x5:
        break;
    case 0x6:
        break;
    case 0x7:
        break;
    case 0x8:
        break;
    case 0x9:
        break;
    case 0xA:
        // ANNN: Sets index register to address NNN
        indexRegister = opcode & 0x0fff; 
        break;
    case 0xB:
        break;
    case 0xC:
        break;
    case 0xD
        break;
    case 0xE:
        break;
    case 0xF:
        break;
    default:
        break;
    }
}

    uint16_t Chip8::firstOpcodeNibble(uint16_t& _opcode) {
        return (_opcode & 0b1111000000000000) >> 12;
    }
    uint16_t Chip8::secondOpcodeNibble(uint16_t& _opcode) {
        return (_opcode & 0b0000111100000000) >> 8;
    }
    uint16_t Chip8::thirdOpcodeNibble(uint16_t& _opcode) {
        return (_opcode & 0b0000000011110000) >> 4;
    }
    uint16_t Chip8::fourthOpcodeNibble(uint16_t& _opcode) {
        return (_opcode & 0b0000000000001111);
    }