// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(INIT)
    @SCREEN
    D=A

    @pixel
    M=D

(LOOP)
    @curr
    M=0

    @KBD
    D=M
    
    @ON
    D;JEQ
    @OFF
    0;JMP

(ON)
    @pixel
    M=-1
    @DRAW
    0;JMP

(OFF)
    @pixel
    M=0
    @DRAW
    0;JMP
    
(DRAW)
    @pixel
    D=M+1
    M=D

    @KBD
    D=A-D

    @INIT
    D;JEQ

    @LOOP
    0;JMP