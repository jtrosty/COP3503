#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char* regTable[2][8] = {{"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"}, 
                        {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"}};
char* eff_address_table[3][8] = { 
                                  {"BX + SI", "BX + DI", "BP + SI", "BP + DI", "SI", "DI", "Direct Address", "BX"},
                                  {"BX + SI", "BX + DI", "BP + SI", "BP + DI", "SI", "DI", "BP", "BX"},
                                  {"BX + SI", "BX + DI", "BP + SI", "BP + DI", "SI", "DI", "BP", "BX"}
                                };
struct Inst_PC_Data {
    uint8_t byte_one;
    uint8_t byte_two;
    uint8_t byte_three;
    uint8_t byte_four;
    uint32_t pc;
} inst_PC_data;

long getfileSize(char* filename) {
    FILE* fp; 
    fopen_s(&fp, filename, "r");
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

void print_mov_mem(char regTo, uint16_t data, char w, char d) {
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
    if ((inst->byte_one & 0x02) > 0) dir = 1;
    else dir = 0;
    // Get if it is a full word or not
    if ((inst->byte_one & 0x01) > 0) word = 1;
    else word = 0;

    mod = (inst->byte_two & 0xC0) >> 6; // Maybe we just know that mode is 11 when we get here?
    regFrom = (inst->byte_two & 0x38) >> 3;
    regTo = (inst->byte_two & 0x07);
    print_mov_r_to_r(regTo, regFrom, word);
    inst->pc += 2;
}

void mov_general(struct Inst_PC_Data* inst) {
    char dir = 0;
    char word = 0;
    char mod = 0;
    char from = 0;
    char to = 0;
    char r_m = inst->byte_two & 0x07;
    uint16_t displacement = 0;

    // Get direciton of move
    if ((inst->byte_one & 0x02) > 0) dir = 1;
    else dir = 0;
    // Get if it is a full word or not
    if ((inst->byte_one & 0x01) > 0) word = 1;
    else word = 0;

    mod = (inst->byte_two & 0xC0) >> 6; // Maybe we just know that mode is 11 when we get here?
    switch (mod) {
        case 0x00:
            /* code */
            if (r_m == 0x06) {
                // Special case
                printf("Not coded, r_m == 0x06 mod 00 special case.");
                inst->pc += 4;
            }
            else if (dir > 0) {
                to = (inst->byte_two & 0x38) >> 3;
                from = inst->byte_two & 0x7;
                printf("MOV %s, [%s] \n", regTable[word][to], eff_address_table[mod][from]);
            }
            else {
                from = (inst->byte_two & 0x38) >> 3;
                to = inst->byte_two & 0x7;
                printf("MOV [%s], %s \n", eff_address_table[mod][to], regTable[word][from]);
            }
            inst->pc += 2;
            break;
        case 0x01:
            /* code */
            displacement = inst->byte_three; 
            if (dir > 0) {
                to = (inst->byte_two & 0x38) >> 3;
                from = inst->byte_two & 0x7;
                if (displacement == 0) {
                    printf("MOV %s, [%s]\n", regTable[word][to], eff_address_table[mod][from]);
                }
                else {
                    printf("MOV %s, [%s + %i]\n", regTable[word][to], eff_address_table[mod][from], displacement);
                }
            }
            else {
                from = (inst->byte_two & 0x38) >> 3;
                to = inst->byte_two & 0x7;
                if (displacement == 0) {
                    printf("MOV [%s], %s \n", eff_address_table[mod][to], regTable[word][from]);
                }
                else {
                    printf("MOV [%s + %i], %s \n", eff_address_table[mod][to], displacement, regTable[word][from]);
                }
            }
            inst->pc += 3;
            break;
        case 0x02:
            displacement = inst->byte_four << 8; 
            displacement = displacement | inst->byte_three; 
            if (dir > 0) {
                to = inst->byte_two & 0x38 >> 3;
                from = inst->byte_two & 0x7;
                printf("MOV %s, [%s + %i]\n", regTable[word][to], eff_address_table[mod][from], displacement);
            }
            else {
                from = inst->byte_two & 0x38 >> 3;
                to = inst->byte_two & 0x7;
                printf("MOV [%s + %i], %s \n", eff_address_table[mod][from], displacement, regTable[word][to]);
            }
            inst->pc += 4;
            break;
        case 0x03:
            /* code */
            movRtoR(inst);
            break;
        default:
            printf("move_general, should never hit.\n");
            break;
    }
}

void move_i_to_r_8bit(struct Inst_PC_Data* inst) {
    // MOV immediate to register
    uint16_t data;
    char regTo;
    char word = 0;
    // Get if it is a full word or not

    data = (inst->byte_two & 0xFF);
    regTo = (inst->byte_one & 0x07);
    print_mov_i_to_r(regTo, data, word);
    inst->pc += 2;
}

void move_i_to_r_16bit(struct Inst_PC_Data* inst) {
    uint16_t data;
    char regTo;
    char word = 1;

    data = ((uint16_t)inst->byte_three) << 8;
    data = (data | (uint16_t)inst->byte_two);
    regTo = (inst->byte_one & 0x03);
    print_mov_i_to_r(regTo, data, word);
    inst->pc += 3;
}

void add_reg_mem(struct Inst_PC_Data* inst) {
    char dir = 0;
    char word = 0;
    char mod = 0;
    char from = 0;
    char to = 0;
    char r_m = inst->byte_two & 0x07;
    uint16_t value = 0;

    // Get direciton of move
    if ((inst->byte_one & 0x02) > 0) dir = 1;
    else dir = 0;
    // Get if it is a full word or not
    if ((inst->byte_one & 0x01) > 0) word = 1;
    else word = 0;

    mod = (inst->byte_two & 0xC0) >> 6; // Maybe we just know that mode is 11 when we get here?

    if (mod == 0) {

        inst->pc += 2;
    }
    else if (mod == 0x01) {

        inst->pc += 3;
    }
    else if (mod == 0x02) {

        inst->pc += 4;
    }
    else if (mod == 0x03) {

        inst->pc += 2;
    }
}

void add_i_reg_mem(struct Inst_PC_Data* inst) {

}

void add_i_accumulator(struct Inst_PC_Data* inst) {

}

void decode_one_byte_inst(struct Inst_PC_Data* inst) {
    printf("Not done yet cheif, one byte inst \n.");
    inst->pc +=1;
}

void decode_two_byte_inst(struct Inst_PC_Data* inst) {
    uint8_t opcode_six_bits = (uint8_t)(inst->byte_one & 0xFC); // need the first 6 bits
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
    printf("Not done yet cheif, three byte inst \n.");
    inst->pc += 3;
}

void decode_four_byte_inst(struct Inst_PC_Data* inst) {
    printf("Not done yet cheif, four byte inst \n.");
    inst->pc += 4;
}

void decode(struct Inst_PC_Data* inst) {
    uint8_t first_bit = (inst->byte_one & 0x80); // need the first 6 bits
    uint8_t opcode_three_bits = (inst->byte_one & 0xE0); // need the first 6 bits
    uint8_t opcode_four_bits = (inst->byte_one & 0xF0); // need the first 6 bits
    uint8_t opcode_six_bits = (inst->byte_one & 0xFC); // need the first 6 bits
    uint8_t mod = (inst->byte_two & 0xC0) >> 6;
    uint8_t r_m_field = (inst->byte_two & 0x03);
    char found_inst = 0;

    // three bit instructions
    switch (opcode_three_bits) {
        case 0x00: {
            // Check if w bit is 0 or 1
            printf("should never enter here. 3 bit opcode.\n");
            break;
        }
    }

    // Four bit instructions
    switch (opcode_four_bits) {
        case 0xB0: {
            // Check if w bit is 0 or 1
            char word = inst->byte_one & 0x08;
            if (word > 0) {
                move_i_to_r_16bit(inst);
            }
            else {
                move_i_to_r_8bit(inst);
            }
            found_inst = 1;
            break;
        }
    }

    switch (opcode_six_bits) {
        case 0x88: {
            mov_general(inst);
            found_inst = 1;
            break;
        }
        case 0x00: {
            add_reg_mem(inst);
            found_inst = 1;
            break;
        }
        case 0x80: {
            add_i_reg_mem(inst);
            found_inst = 1;
            break;
        }
        case 0x02: {
            add_i_accumulator(inst);
            found_inst = 1;
            break;
        }

    }

    // Instructiosn with mode
    if (!first_bit && !found_inst) {
        // First byte is a 0, does not necessarily mean only a 1 byte inst
        decode_one_byte_inst(inst);
    }
    else if (!found_inst) {
        switch (mod){
            case 0x0:
                if (r_m_field == 0x03) 
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
        //path = "..\\data\\";
        debug_fileName = "..\\data\\many_test.bin";
        //debug_fileName = "..\\data\\listing_0039_more_movs.bin";

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
        fopen_s(&fp, debug_fileName, "r");
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