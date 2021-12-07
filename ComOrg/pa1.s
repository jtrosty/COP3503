.section .data

input_prompt    :   .asciz  "Input a string: "
input_spec      :   .asciz  "%[^\n]"
input_word      :   .space 8 
length_spec     :   .asciz  "String length: %d\n"
palindrome_spec :   .asciz  "String is a palindrome (T/F): %c\n"
# used for testing
# output_spec     :   .asciz  "String was: %s\n"

.section .text

.global main

main:
    #SP 
    #SUB SP, SP, #16

    # Print out prompt for user to 'input a string'
    # x0 is the argument into printf
    LDR x0, =input_prompt
    BL printf

    # Load x0 and x1 with format specifiers for user input
    # x0 and x1 are acting as the arguments for scanf
    LDR x0, =input_spec
    LDR x1, =input_word
    BL scanf

    # load register x19 with the address of the input string
    LDR x19, =input_word

    # used for testing
    # LDR x0, =output_spec
    # MOV x1, x19
    # BL printf

    # set x9 to zero, this will be the value to add to the char array
    ADD x9, xzr, xzr
    # This will be teh value that the car is added to and checkt o zero
    ADD x10, xzr, xzr 

    lengthLoop:
        LDRB w9, [x19, x10]
        CMP w9, #0
        B.EQ done 
        ADD x10, x10, #1

        B lengthLoop
        
    done:

    # Print out the lenght of the loop
    LDR x0, =length_spec
    MOV x1, x10 
    # save the result at x10 for later
    MOV x20, x10
    BL printf
    MOV x10, x20
    
    # Check if palindrome
    # x11 will start at 0, x10 will start at last digit
    # the last and first digit will be compared, then the front counter will be incremented
    # and the end pointer will be decremented
    SUB x10, x10, #1
    ADD x11, xzr, xzr
    palindrome:
    LDRB w9, [x19, x10]
    LDRB w12, [x19, x11]
    CMP w9, w12
    # compare if the chracters are equal
    B.NE fail
    SUB x10, x10, #1
    ADD x11, x11, #1
    # compare if the the end counter is less than begining counter
    CMP x11, x10
    B.LT palindrome
    # move onto success!

    # 83 is T in ASCII
    success:
        ADD x1, xzr, xzr
        MOV x1, #84
        b end

    # 70 is F in ASCII
    fail:
        ADD x1, xzr, xzr
        MOV x1, #70
        b end


    # Print Palindrome Result, T is 84 or 0x54, F is 70 or 0x46
    end:
        LDR x0, =palindrome_spec
        BL printf
        b exit

    # branch to this label on program completion
    b exit

exit:
    mov x0, 0
    mov x8, 93
    svc 0
    ret