#include "chip8.h"

Chip8::Chip8() {
    vRegisters = new uint8_t[16];
    memory = new uint8_t[4096];
    programCounter = (memory + 20);
    stack = new uint8_t[32];
    stackPointer = stack;
    memoryStart = memory;
    opcode = 0;
    indexRegister = 0;
}

Chip8::~Chip8() { 
    delete[] vRegisters;
    delete[] memory;
    delete[] stack;
    delete[] pixelBuffer;
}

void Chip8::fetch( uint16_t& _opcode, uint8_t& _programCounter) {
    _opcode = (memory[_programCounter] << 8) | (memory[_programCounter + 1]);
    _programCounter = _programCounter + 2;
}  

void Chip8::pixelBufferTestCode(void* pixelBuffer, int seed) {
    uint8_t* buffer = (uint8_t*)pixelBuffer;
    int length = CHIP8_HEIGHT * CHIP8_WIDTH * sizeof(uint32_t);
    for (int i = 0; i < length; i = i + 4) {
       buffer[i]     = 0;
       buffer[i + 1] = seed++;
       buffer[i + 2] = 255;
       buffer[i + 3] = 0;
    }
}

void Chip8::decode() {
    uint16_t firstNibble = firstOpcodeNibble(*opcode);
    uint16_t secondNibble = secondOpcodeNibble(*opcode);
    uint16_t thridNibble = thirdOpcodeNibble(*opcode);
    uint16_t fourthNibble = fourthOpcodeNibble(*opcode);
    uint16_t mask = 0x0fff;

    switch (firstNibble)
    {
    case 0x0:
        switch(fourthNibble) {
            case 0x0:
                OPCODE_00E0();
                break;
            case 0xE:
                OPCODE_00EE();
                break;
            default:
                std::cout << "OPCODE_0 failure. " << std::endl;
                break;
        }
        break;
    case 0x1:
        OPCODE_1nnn();
        break;
    case 0x2:
        OPCODE_2nnn();
        break;
    case 0x3:
        OPCODE_3xnn();
        break;
    case 0x4:
        OPCODE_4xnn();
        break;
    case 0x5:
        OPCODE_5xy0();
        break;
    case 0x6:
        OPCODE_6xnn();
        break;
    case 0x7:
        OPCODE_7xnn();
        break;
    case 0x8:
        switch (fourthNibble) {
        case 0x0:
            OPCODE_8xy0();
            break;
        case 0x1:
            OPCODE_8xy1();
            break;
        case 0x2:
            OPCODE_8xy2();
            break;
        case 0x3:
            OPCODE_8xy3();
            break;
        case 0x4:
            OPCODE_8xy4();
            break;
        case 0x5:
            OPCODE_8xy5();
            break;
        case 0x6:
            OPCODE_8xy6();
            break;
        case 0x7:
            OPCODE_8xy7();
            break;
        case 0xE:
            OPCODE_8xyE();
            break;
        default:
            std::cout << "OPCODE_8 failure. " << std::endl;
            break;
        }
        break;
    case 0x9:
        OPCODE_9xy0();
        break;
    case 0xA:
        OPCODE_Annn();
        break;
    case 0xB:
        OPCODE_Bnnn();
        break;
    case 0xC:
        OPCODE_Cxnn();
        break;
    case 0xD:
        OPCODE_Dxyn();
        break;
    case 0xE:
        switch (fourthNibble) {
        case 0xE: 
            OPCODE_Ex9E();
            break;
        case 0x1: 
            OPCODE_ExA1();
            break;
        default:
            std::cout << "OPCODE_E failure. " << std::endl;
            break;
        }
        break;
    case 0xF:
        switch (thridNibble) {
            case 0x0: 
                switch (fourthNibble) {
                case 0x7:
                    OPCODE_Fx07();
                    break;
                case 0xA:
                    OPCODE_Fx0A();
                    break;
                default:
                    std::cout << "OPCODE_Fx failure. " << std::endl;
                    break;
                }
            case 0x1: 
                switch (fourthNibble) {
                case 0x5:
                    OPCODE_Fx15();
                    break;
                case 0x8:
                    OPCODE_Fx18();
                    break;
                case 0xE:
                    OPCODE_Fx1E();
                    break;
                default:
                    std::cout << "OPCODE_Fx1 failure. " << std::endl;
                    break;
                }
                break;
            case 0x2: 
                OPCODE_Fx29();
                break;
            case 0x3: 
                OPCODE_Fx33();
                break;
            case 0x5: 
                OPCODE_Fx55();
                break;
            case 0x6: 
                OPCODE_Fx65();
                break;
            }
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

void Chip8::OPCODE_NULL() /* NOP instruction */ {

}
void Chip8::OPCODE_00E0() /* CLS */ {
    for (int i = 0; i < (CHIP8_WIDTH * CHIP8_HEIGHT); i++) {
        pixelBuffer[i] = 0x00000000;
    }
}
void Chip8::OPCODE_00EE() /* RET */ {
    // Decremet the stack and assign value to program coutner, the oposite of 2nnn
    programCounter = stack[--stackPointer];

}
void Chip8::OPCODE_1nnn() /* JP addr */ {
    programCounter = *opcode & (uint16_t)0x0FFF; 

}
void Chip8::OPCODE_2nnn() /* CALL addr */ {
    // Store PC value on stack and SP is incremented
    stack[(stackPointer)++] = programCounter;
    // set PC to NNN address
    programCounter = *opcode & (uint16_t)0x0FFF; 
}
void Chip8::OPCODE_3xnn() /* SE Vx, byte */ {
    // skip next intruction, add 2 to programCounter if Vx = nn
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t nn = *opcode & 0x00FF;
    if (vRegisters[x] == nn) {
        programCounter += 2;
    }
}
void Chip8::OPCODE_4xnn() /* SNE Vx, byte */ {
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t nn = *opcode & 0x00FF;
    if (vRegisters[x] != nn) {
        programCounter += 2;
    }
}
void Chip8::OPCODE_5xy0() /* SE Vx, Vy */ {
    //Skip next instruction if Vx = Vy.
    //The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2./
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    if (vRegisters[x] == vRegisters[y]) {
        programCounter += 2;
    }
}
void Chip8::OPCODE_6xnn() /* LD Vx, byte */ {
    //The interpreter puts the value kk into register Vx.
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t nn = *opcode & 0x0001;
    vRegisters[x] = nn;
}
void Chip8::OPCODE_7xnn() /* ADD Vx, byte */ {
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t nn = *opcode & 0x0001;
    vRegisters[x] = x + nn;
}
void Chip8::OPCODE_8xy0() /* LD Vx, Vy */ {
    //Stores the value of register Vy in register Vx.
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    vRegisters[x] = vRegisters[y];
}
void Chip8::OPCODE_8xy1() /* OR Vx, Vy */ {
    //Set Vx = Vx OR Vy. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    vRegisters[x] = vRegisters[y] | vRegisters[x];
}
void Chip8::OPCODE_8xy2() /* AND Vx, Vy */ {
    //Set Vx = Vx AND Vy.
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    vRegisters[x] = vRegisters[y] & vRegisters[x];
}
void Chip8::OPCODE_8xy3() /* XOR Vx, Vy */ {
    //Set Vx = Vx XOR Vy. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    vRegisters[x] = vRegisters[y] ^ vRegisters[x];
}
void Chip8::OPCODE_8xy4() /* ADD Vx, Vy */ {
    //Set Vx = Vx + Vy, set VF = carry. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    uint8_t tempX = vRegisters[x];
    vRegisters[x] = vRegisters[y] + vRegisters[x];
    if (vRegisters[x] < tempX && vRegisters[x] < vRegisters[y]) {
        vRegisters[15] = 1;
    }
    else {
        vRegisters[15] = 0;
    }
}
void Chip8::OPCODE_8xy5() /* SUB Vx, Vy */ {
    //Set Vx = Vx - Vy, set VF = NOT borrow. 
    //If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    if (vRegisters[y] > vRegisters[x]) vRegisters[15] = 1;
    else vRegisters[15] = 0;
    vRegisters[x] = vRegisters[y] - vRegisters[x];
}
void Chip8::OPCODE_8xy6() /* SHR Vx */ {
    // Set Vx = Vx SHR 1. 
    // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    if (vRegisters[x] == 0b00000001)    vRegisters[15] = 1;
    else                                vRegisters[15] = 0;
    vRegisters[x] = vRegisters[x] >> 1;
}
void Chip8::OPCODE_8xy7() /* SUBN Vx, Vy */ {
    //Set Vx = Vy - Vx, set VF = NOT borrow. 
    // If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx. 
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    if (vRegisters[y] > vRegisters[x])  vRegisters[15] = 1;
    else                                vRegisters[15] = 0;
    vRegisters[x] = vRegisters[y] - vRegisters[x];
}
void Chip8::OPCODE_8xyE() /* SHL Vx, {, Vy} */ {
    // Set Vx = Vx SHL 1.
    // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
    uint8_t x = (*opcode >> 8) & 0x00FF;
    if ((vRegisters[x] & 0b10000000) == 0b10000000) vRegisters[15] = 1;
    else                                            vRegisters[15] = 0;
    vRegisters[x] = vRegisters[x] << 1;
}
void Chip8::OPCODE_9xy0() /* SNE Vx, Vy */ {
    // Skip next instruction if Vx != Vy.
    // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
    uint8_t x = (*opcode >> 8) & 0x00FF;
    uint8_t y = (*opcode >> 4) & 0x00FF;
    if (vRegisters[x] != vRegisters[y]) {
        programCounter += 2;
    }
}
void Chip8::OPCODE_Annn() /* LD I, addr */ {
    //  Set I = nnn. 
    indexRegister = *opcode & (uint16_t)0x0FFF; 
}
void Chip8::OPCODE_Bnnn() /* JP V0, addr */ {
    //  Jump to location nnn + V0. 
    programCounter = *opcode & (uint16_t)0x0FFF + vRegisters[0]; 
}
void Chip8::OPCODE_Cxnn() /* RND Vx, byte */ {
    // Set Vx = random byte AND kk. 
    //  The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.  

}
void Chip8::OPCODE_Dxyn() /* DRW Vx, Vy, nibble */ {
    // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision. 

}
void Chip8::OPCODE_Ex9E() /* SKP Vx    */ {
    // Skip next instruction if key with the value of Vx is pressed. 

}
void Chip8::OPCODE_ExA1() /* SKNP Vx */ {
    // Skip next instruction if key with the value of Vx is not pressed.
 

}
void Chip8::OPCODE_Fx07() /* LD Vx, DT */ {
    //  Set Vx = delay timer value. 

}
void Chip8::OPCODE_Fx0A() /* LD Vx, K */ {
    // Wait for a key press, store the value of the key in Vx.
 

}
void Chip8::OPCODE_Fx15() /* LD DT, Vx */ {
    // Set delay timer = Vx. 

}
void Chip8::OPCODE_Fx18() /* LD ST, Vx */ {
    // Set sound timer = Vx 

}
void Chip8::OPCODE_Fx1E() /* ADD I, Vx */ {
    // Set I = I + Vx. 

}
void Chip8::OPCODE_Fx29() /* LD F, Vx */ {
    // Set I = location of sprite for digit Vx. 

}
void Chip8::OPCODE_Fx33() /* LD B, Vx */ {
    // Store BCD representation of Vx in memory locations I, I+1, and I+2. 


}
void Chip8::OPCODE_Fx55() /* LD [I], Vx */ {
    // Store registers V0 through Vx in memory starting at location I. 

}
void Chip8::OPCODE_Fx65() /* LD Vx, [I] */ {
    // Read registers V0 through Vx from memory starting at location I. 

}
