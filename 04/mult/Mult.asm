// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@R2
M=0 //Initialize R2 to 0

(LOOP)

//Set R2, Add R1 to it, Load it back to R2
    @R2
    D=M

    @R1
    D=D+M

    @R2
    M=D

//Reduce counter (R1)
    @R0
    D=M-1
    M=D

//Loop if GT
    @LOOP
    D;JGT

(END)
    @END
    0;JMP
