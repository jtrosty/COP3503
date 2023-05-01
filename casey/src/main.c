#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char* regTable[2][8] = {{"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"}, 
                        {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"}};

struct Inst_PC_Data {
    uint8_t byte_one;
    uint8_t byte_two;
    uint8_t byte_three;
    uint8_t byte_four;
    uint32_t pc;
} inst_PC_data;

long getfileSize(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File failed to open.");
    }
    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        perror("File failed to open.");
    }
    long length = ftell(fp);
    fclose(fp);
    return length;
}

void print_mov_r_to_r(char regTo, char regFrom, char w) {
    printf("MOV %s, %s \n", regTable[w][regTo], regTable[w][regFrom]);
}

void print_mov_i_to_r(char regTo, uint16_t data, char w) {
    printf("MOV %s, %i \n", regTable[w][regTo], data);
}

void movRtoR(struct Inst_PC_Data* inst) {
    // MOV register to register
    char dir;
    char word;
    char mod;
    char regFrom;
    char regTo;

    // Get direciton of move
    if ((inst->byte_two & 0x02) > 0) dir = 1;
    else dir = 0;
    // Get if it is a full word or not
    if ((inst->byte_two & 0x01) > 0) word = 1;
    else word = 0;

    mod = (inst->byte_two & 0xC0) >> 14;
    regFrom = (inst->byte_two & 0x38) >> 11;
    regTo = (inst->byte_two & 0x07) >> 8;
    print_mov_r_to_r(regTo, regFrom, word);
}

void move_i_to_r_8bit(struct Inst_PC_Data* inst) {
    // MOV immediate to register
    char data;
    char regTo;

    data = (inst->byte_two & 0xFF) >> 8;
    regTo = (inst->byte_two & 0x03) >> 8;
    printMovInst(regTo, data, 0);
}

void move_i_to_r_16bit(struct Inst_PC_Data* inst) {

}

void decode_one_byte_inst(struct Inst_PC_Data* inst) {

}

void decode_two_byte_inst(struct Inst_PC_Data* inst) {
    uint8_t opcode_six_bits = (uint8_t)(inst->byte_one & 0x00FC); // need the first 6 bits
    switch (opcode_six_bits)
    {
    case 0x3C: // CMP: Immediate with Accumlator 
        /* code */
        break;
    case 0x88: // MOV: Register to Register  
        movRtoR(inst);
        break;
    default:
        // Handle to 3rd byte if w = 1 case.
        uint8_t opcode_four_bits = (uint8_t)(inst->byte_one & 0xF0);
        if ((opcode_four_bits == 0xB0) > 0) {
            uint8_t w_field = (uint8_t)(inst->byte_one & 0x08);
            if (w_field) {
                // MOV Immediate to Reg 16 bits
                move_i_to_r_16bit(inst);
            }
            else {
                // MOV Immediate to Reg 8 bits
                move_i_to_r_8bit(inst);
            }
        }
        break;
    }
}

void decode_three_byte_inst(struct Inst_PC_Data* inst) {

}

void decode_four_byte_inst(struct Inst_PC_Data* inst) {

}

void decode(struct Inst_PC_Data* inst) {
    uint8_t first_bit = (inst->byte_one & 0x80); // need the first 6 bits
    uint8_t opcode_four_bits = (inst->byte_one & 0xF0); // need the first 6 bits
    uint8_t mod = (inst->byte_two & 0xC000) >> 14;
    uint8_t r_m_field = (inst->byte_two & 0x0300) >> 8;

    if (!first_bit) {
        // First byte is a 0, does not necessarily mean only a 1 byte inst
        decode_one_byte_inst(inst);
    }
    else {
        switch (mod){
            case 0x0:
                if (r_m_field = 0x03) 
                break;
            case 0x1:
                decode_three_byte_inst(inst);
                break;
            case 0x2:
                decode_three_byte_inst(inst);
                break;
            case 0x3:
                decode_two_byte_inst(inst);
                break;
            default:
                printf("should never enter here. @Decode.\n");
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    FILE* fp;
    char* rawInstructionsData;
    char* debug_fileName;
    long fileSize = 0;


    if (argc == 2) {
        fileSize = getfileSize(argv[1]);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
    }
    else if (argc == 1) {
        //debug_fileName = "short_test.bin";
        debug_fileName = "..\\data\\many_test.bin";

        fileSize = getfileSize(debug_fileName);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
        size_t bytes = sizeof(char) * ((int)fileSize);
        //rawInstructionsData = (char*)malloc(bytes);
        rawInstructionsData = (char*)malloc(bytes * sizeof(char));
        if (!rawInstructionsData) {
            perror("Failed to get memory.");
        }
        fp = fopen(debug_fileName, "r");
    }
    else {
        return 1;
    }
    // It worked. 

    // Copy raw data into new array to be passed to encoding.
    int c;
    for (long i = 0; i < fileSize; i++) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        char temp = (char)(c & 0x000000FF);
        rawInstructionsData[i] = temp;
    }
    fclose(fp);

    if (fileSize % 2 ==1) {
        perror("odd number of bytes in instructions.");
    }

    long numOfBytes = fileSize;
    uint8_t* inst_stream = (uint8_t*)rawInstructionsData;
    //Four_Inst_And_Pc inst_to_decode = {0};
    //inst_data = {0};
    struct Inst_PC_Data inst_pc_data = {0};
    inst_pc_data.pc = 0;
    while (inst_pc_data.pc < numOfBytes) {
        inst_pc_data.byte_one = inst_stream[inst_pc_data.pc];
        inst_pc_data.byte_two = inst_stream[inst_pc_data.pc + 1];
        inst_pc_data.byte_three = inst_stream[inst_pc_data.pc + 2];
        inst_pc_data.byte_four = inst_stream[inst_pc_data.pc + 3];
        decode(&inst_pc_data);
    }

    free(rawInstructionsData);
    printf("you did it. \n");
    return 0;
}