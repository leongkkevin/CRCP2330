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

(INIT)          //Starts the variables
    @SCREEN
    D=A

    @pixel
    M=D

(LOOP) 

    @KBD        //Check Keyboard input
    D=M
    
    @ON         //Jump to either on or off
    D;JGT
    @ON
    D;JEQ

    @LOOP
    0;JMP

(ON)            //Sets pixelVal to Black
    @pixelValue
    M=-1
    @DRAW
    0;JMP

(OFF)           //Sets pixelVal to White
    @pixelValue
    M=0
    @DRAW
    0;JMP
    
(DRAW)          //Draws the Pixel
    @pixelValue //Checks value
    D=M

    @pixel      //Drawing it
    A=M
    M=D

    @pixel      //Incrementing pixel
    D=M+1
    A=M

    @KBD
    D=A-D

    @pixel      //If A=0, the whole screen is a color, so restart
    M=M+1
    A=M

    @INIT
    D;JEQ

    @LOOP
    0;JMP