# proc_sim
Simulation of a basic processor


Current instructions

Arithmetic functions:

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

Add divide  

Bitwise instructions:

AND R3 R1 R2  
Performs a bitwise AND on R1 and R2 and stores the result in R3

OR R3 R1 R2  
Performs a bitwise OR on R1 and R2 and stores the result in R3

L_SHIFT R3 R1 R2  
Left shift the contents of R1 by R2 and stores the result in R3

R_SHIFT R3 R1 R2  
Right shift the contents of R1 by R2 and stores the result in R3

NOT R2 R1  
Performs a bitwise not on the contents of R1 and store the result in R2
