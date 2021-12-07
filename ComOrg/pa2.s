.section .data

    input_x_prompt : .asciz "Please enter x: "
    input_y_prompt : .asciz "Please enter y: "
    input_spec     : .asciz "%d"
    result         : .asciz "x^y = %d\n"

.section .text

.global main

main:

    ############################################################################
    ##              Input section, load x and y                               ##
    ############################################################################
    
    # Input x
    # Create room on Stack
    SUB SP, SP, #8
    # print statement
    LDR x0, =input_x_prompt
    BL printf
    # Scan input
    LDR x0, =input_spec
    MOV x1, SP
    BL scanf
    # store number
    LDRSW x19, [SP]

    # Input y
    # Create room on Stack
    SUB SP, SP, #8
    # print statement
    LDR x0, =input_y_prompt
    BL printf
    # Scan input
    LDR x0, =input_spec
    mov x1, SP
    BL scanf
    # store number
    LDRSW x20, [SP]

    # Store values in x0 and x1 and call power funtion
    MOV x0, x19
    MOV x1, x20
    BL power_start

    # have results Print them out
    LDR x0, =result
    MOV x1, x2
    BL printf
    
    # Restore stack
    ADD SP, SP, #16

    B exit

    ############################################################################
    ##               Power Function Entrance x0 is x, x1 is y                 ##
    ############################################################################

    power_start:
        #  Check if x is zero
        CBZ x0, power_base_x_is_zero

        # check case of y is less than zero
        CMP x1, XZR
        B.LT power_base_y_is_negative

        # Check case y is zero
        CBZ x1, power_base_y_is_zero

        # now if all base cases passed, perform recursion.
        CBNZ x1, power_recurse

    
    ############################################################################
    ##                      Base Cases                                        ##
    ############################################################################
    power_base_x_is_zero:
        # if x is zero, set return value, x2 to zero and return
        ADD x2, XZR, XZR 
        RET

    power_base_y_is_negative:
        # if x is zero, set return value, x2 to zero and return
        ADD x2, XZR, XZR 
        RET

    power_base_y_is_zero:
        #if zero return 1
        ADD x12, XZR, XZR
        ADD x2, x12, #1 
        RET

    ############################################################################
    ##                      Recursion Cases                                   ##
    ############################################################################
    power_recurse:
    # Set up stack for teh return register.
    SUB SP, SP, 8
    STR x30, [sp]

    # Make room on stack for x0 and x1
    SUB SP, SP, 8
    STR x0, [SP]
    SUB SP, SP, 8
    STR x1, [SP]
    
    # Recursively call 
    SUB x1, x1, 1
    BL power_start:

    # Back from recursion, restore stack, restore stack 24 total
    LDR x1, [SP]
    LDR x0, [SP, 8]
    LDR x30, [SP, 16]
    ADD SP, SP, 24

    # Multiply
    MUL x2, x2, x0

    RET
exit:
    MOV x0, 0
    MOV x8, 93
    SVC 0
    RET