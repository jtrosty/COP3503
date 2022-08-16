#include <cstdint>

class Chip8 {

    // SYSTEM MEMORY MAP 
    // 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
    // 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    // 0x200-0xFFF - Program ROM and work RAM
    // Register
    // memory and stack
    uint8_t* vRegisters;
    uint8_t* memory;
    uint8_t* programCounter;
    uint8_t* stack;
    uint8_t* stackPointer;
    uint8_t* memoryStart;
    uint8_t* memoryInstructionStart;
    uint8_t* startOfRam;

    // 
    uint16_t* opcode;
    uint16_t* indexRegister;

    uint8_t delayTimer;
    uint8_t soundTimer;

    uint16_t firstOpcodeNibble(uint16_t& _opcode);
    uint16_t secondOpcodeNibble(uint16_t& _opcode);
    uint16_t thirdOpcodeNibble(uint16_t& _opcode); 
    uint16_t fourthOpcodeNibble(uint16_t& _opcode); 

    void initialize(); 
    void emulateCycle();
    
    void fetch(uint16_t& _opcode, uint8_t& _programCounter);
    void decode();
    void execute();

    


};