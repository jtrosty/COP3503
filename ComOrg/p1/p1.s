.section .data

input_prompt    :   .asciz  "Input a string: "
input_spec      :   .asciz  "%[^\n]"
input_word      :   .space 8 
length_spec     :   .asciz  "String length: %d\n"
palindrome_spec :   .asciz  "String is a palindrome (T/F): %c\n"

.section .text

.global main

main:
    # Print out prompt for user to 'input a string'
    # x0 is the argument into printf
    LDR x0, =input_promp
    BL printf

    # Load x0 and x1 with format specifiers for user input
    # x0 and x1 are acting as the arguments for scanf
    LDR x0, =input_spec
    LDR x1, =length_spec
    BL scanf

    # load register x19 with the address of the input string
    LDR x19, =input_word
    ADD x9, xzr, xzr      # set x9 to zero, this will be the value to add to the char array
    ADD x10, xzr, xzr     # This will be teh value that the car is added to and checkt o zero
    lengthLoop:
        #add x11, x9, xzr # Set x11 to x9 
        # lsl x11, x11, #3 # multiply x11 by 8 to get the byte shift for the next character
        LDR x11, [x19, #0]
        SUB x11, xzr, x11
        CBZ x11, done
        ADD x9, x9, #1
        ADD x19, x19, #1
        B lengthLoop
        
    done:
    
    # Print out the lenght of the input string
    LDR x0, =length_spec
    LDR x1, x9
    BL printf

    # Check if palindrome




    # branch to this label on program completion
    b exit

exit:
    mov x0, 0
    mov x8, 93
    svc 0
    ret