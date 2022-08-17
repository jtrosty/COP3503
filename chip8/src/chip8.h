#include <iostream>
#include <cstdint>

class Chip8 {

    // SYSTEM MEMORY MAP 
    // 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
    // 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    // 0x200-0xFFF - Program ROM and work RAM
    // Register
    // memory and stack
public:
    uint8_t* vRegisters;
    uint8_t* memory;
    uint8_t* stack;
    uint8_t programCounter = 0;
    uint8_t stackPointer = 0;
    uint8_t memoryStart = 0;
    uint8_t memoryInstructionStart = 0;
    uint8_t startOfRam = 0;
    const int CHIP8_HEIGHT = 64;
    const int CHIP8_WIDTH = 32;
    uint8_t keypad[16] {}; // initialized to zero

    // Pixel buffer initialized to 0
    uint32_t* pixelBuffer = new uint32_t[CHIP8_HEIGHT * CHIP8_WIDTH] {};

    uint16_t* opcode;
    uint16_t indexRegister = 0;

    uint8_t delayTimer;
    uint8_t soundTimer;

    Chip8(); 
    ~Chip8(); 

    uint16_t firstOpcodeNibble(uint16_t& _opcode);
    uint16_t secondOpcodeNibble(uint16_t& _opcode);
    uint16_t thirdOpcodeNibble(uint16_t& _opcode); 
    uint16_t fourthOpcodeNibble(uint16_t& _opcode); 

    void emulateCycle();
    
    void pixelBufferTestCode(void* pixelBuffer, int seed);

    void fetch(uint16_t& _opcode, uint8_t& _programCounter);
    void decode();
    void execute();

    void OPCODE_NULL(); // NOP instruction
    void OPCODE_00E0(); // CLS
    void OPCODE_00EE(); // RET
    void OPCODE_1nnn(); // JP addr
    void OPCODE_2nnn(); // CALL addr
    void OPCODE_3xnn(); // SE Vx, byte
    void OPCODE_4xnn(); // SNE Vx, byte
    void OPCODE_5xy0(); // SE Vx, Vy
    void OPCODE_6xnn(); // LD Vx, byte
    void OPCODE_7xnn(); // ADD Vx, byte
    void OPCODE_8xy0(); // LD Vx, Vy
    void OPCODE_8xy1(); // OR Vx, Vy
    void OPCODE_8xy2(); // AND Vx, Vy
    void OPCODE_8xy3(); // XOR Vx, Vy
    void OPCODE_8xy4(); // ADD Vx, Vy
    void OPCODE_8xy5(); // SUB Vx, Vy
    void OPCODE_8xy6(); // SHR Vx
    void OPCODE_8xy7(); // SUBN Vx, Vy
    void OPCODE_8xyE(); // SHL Vx, {, Vy}
    void OPCODE_9xy0(); // SNE Vx, Vy
    void OPCODE_Annn(); // LD I, addr
    void OPCODE_Bnnn(); // JP V0, addr
    void OPCODE_Cxnn(); // RND Vx, byte
    void OPCODE_Dxyn(); // DRW Vx, Vy, nibble
    void OPCODE_Ex9E(); // SKP Vx   
    void OPCODE_ExA1(); // SKNP Vx
    void OPCODE_Fx07(); // LD Vx, DT
    void OPCODE_Fx0A(); // LD Vx, K
    void OPCODE_Fx15(); // LD DT, Vx
    void OPCODE_Fx18(); // LD ST, Vx
    void OPCODE_Fx1E(); // ADD I, Vx
    void OPCODE_Fx29(); // LD F, Vx
    void OPCODE_Fx33(); // LD B, Vx
    void OPCODE_Fx55(); // LD [I], Vx
    void OPCODE_Fx65(); // LD Vx, [I]


};