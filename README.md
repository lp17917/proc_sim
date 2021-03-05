#Basic Processor Simulator

Simulation of a processor with a small instruction set to showcase processor optimisation techniques

Use makefile to build and run proc_sim to automatically execute the current benchmarks

##Current instructions

###Arithmetic functions:

ADD R3 R1 R2  
Adds R1 and R2 and stores the result in R3

ADDI R2 R1 X  
Adds R1 and X and stores the result in R2

MUL R3 R1 R2  
Multiplies R1 and R2 and stores the result in R3

CMP R3 R1 R2  
Compares R1 and R2, if R1 is lower than R2 -1 is stored in R3,
if R1 is equal to R2 0 is stored in R3,
if R1 is bigger than R2 then 1 is stored in R3
  

###Bitwise instructions:

AND R3 R1 R2  
Performs a bitwise AND on R1 and R2 and stores the result in R3

OR R3 R1 R2  
Performs a bitwise OR on R1 and R2 and stores the result in R3

L_SHIFT R3 R1 R2  
Left shift the contents of R1 by R2 and stores the result in R3

R_SHIFT R3 R1 R2  
Right shift the contents of R1 by R2 and stores the result in R3

NOT R2 R1 --
Performs a bitwise not on the contents of R1 and store the result in R2

###Stores and loads:

LOAD R3 R1 R2  
Loads the memory location of R1 + R2

LOAD_VALUE R1 X --
Loads the value of X to R1

STORE R3 R1 R2  
Stores R3 in memory address R1 + R2

STORE_VALUE X R1 R2  
Stores the value of X in address R1 + R2

###Branches and Jumps:

BRANCH_LT X R1 R2   
If R1 is less than R2 then branch to instruction X else the program continues

BRANCH_NOT_ZERO R1 X --
If R1 isn't 0 branch to X else the program continues

ABS_JUMP X -- --
Program jumps to instruction X

REL_JUMP -- R1 --  
Program jumps to instruction R1 relative to current position

###Print instuctions

PRINT_INT R1 -- --
Prints the value of R1

PRINT_CHAR R1 -- --
Prints the last character of the register


TODO:
Add benchmarks for using bitwise and add divide instruction
