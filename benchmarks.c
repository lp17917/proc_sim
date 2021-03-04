#include <stdio.h>


#define ADD 0
#define ADD_I 1
#define MUL 2
#define CMP 3

#define AND 100
#define OR 101
#define L_SHIFT 102
#define R_SHIFT 103
#define NOT 104

#define LOAD 200
#define LOAD_VALUE 201
#define STORE 202
#define STORE_VALUE 203

#define BRANCH_LT 300
#define BRANCH_NOT_ZERO 301
#define ABS_JUMP 302
#define REL_JUMP 303

#define PRINT_INT 400
#define PRINT_CHAR_REG 401
#define PRINT_CHAR 402

#define HALT 500

void vector_addition_set_reg_store(int *INSTR_opcode, int *INSTR_operandres, int *INSTR_operand1, int *INSTR_operand2){
  int i = 0;
  int a[10] = {10,5,2,2,50,7,1,99,52,0};
  int b[10] = {15,1,100,100,10,13,0,1,132,0};
  /*000*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 10; INSTR_operand1[i] = 100; INSTR_operand2[i] = 0; i++;
  /*001*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 11; INSTR_operand1[i] = 150; INSTR_operand2[i] = 0; i++;
  /*002*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 12; INSTR_operand1[i] = 200; INSTR_operand2[i] = 0; i++;
  for (int r = 0; r < 10; r++){
    /*003*/INSTR_opcode[i] = STORE_VALUE; INSTR_operandres[i] = 10; INSTR_operand1[i] = a[r]; INSTR_operand2[i] = 0; i++;
    /*004*/INSTR_opcode[i] = STORE_VALUE; INSTR_operandres[i] = 11; INSTR_operand1[i] = b[r]; INSTR_operand2[i] = 0; i++;
    /*005*/INSTR_opcode[i] = ADD_I; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 1; i++; //set counter to counter + 1
  }
  /*033*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;//resets counter to 0
  /*034*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 5; INSTR_operand1[i] = 10; INSTR_operand2[i] = 2; i++;
  //Add to allow for the printing of the arrays corretly


  //Load a[i] into register 1
  /*035*/INSTR_opcode[i] = LOAD; INSTR_operandres[i] = 1; INSTR_operand1[i] = 10; INSTR_operand2[i] = 0; i++;
  //Prints value of a[i]
  /*036*/INSTR_opcode[i] = PRINT_INT; INSTR_operandres[i] = 1; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;
  //Prints a space
  /*037*/INSTR_opcode[i] = PRINT_CHAR; INSTR_operandres[i] = 32; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;


  //Load b[i] into register 2
  /*038*/INSTR_opcode[i] = LOAD; INSTR_operandres[i] = 2; INSTR_operand1[i] = 11; INSTR_operand2[i] = 0; i++;
  //Prints value of b[i]
  /*039*/INSTR_opcode[i] = PRINT_INT; INSTR_operandres[i] = 2; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;
  //Prints a space
  /*040*/INSTR_opcode[i] = PRINT_CHAR; INSTR_operandres[i] = 32; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;


  //Add register 1 and 2 and put the result in reg 3
  /*041*/INSTR_opcode[i] = ADD; INSTR_operandres[i] = 3; INSTR_operand1[i] = 1; INSTR_operand2[i] = 2; i++;
  //Store the value in reg 3 in memory
  /*042*/INSTR_opcode[i] = STORE; INSTR_operandres[i] = 3; INSTR_operand1[i] = 12; INSTR_operand2[i] = 0; i++;
  //Prints value of r[i]
  /*043*/INSTR_opcode[i] = PRINT_INT; INSTR_operandres[i] = 3; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;
  //Prints a space
  /*044*/INSTR_opcode[i] = PRINT_CHAR; INSTR_operandres[i] = 32; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;

  //Increment memeory counter
  /*039*/INSTR_opcode[i] = ADD_I; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 1; i++;
  //Branch if loop ended
  /*040*/INSTR_opcode[i] = BRANCH_LT; INSTR_operandres[i] = 35; INSTR_operand1[i] = 0; INSTR_operand2[i] = 5; i++;
  //Finish the program
  /*041*/INSTR_opcode[i] = HALT; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;


  //Add loop for adding but use branch
}



int main(){
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
  for (int i=0; i<512; i++){
    INSTR_opcode[i] = 0;
    INSTR_operandres[i] = 0;
    INSTR_operand1[i] = 0;
    INSTR_operand2[i] = 0;
  }
  vector_addition_set_reg_store(INSTR_opcode, INSTR_operandres, INSTR_operand1, INSTR_operand2);
  for (int i=0; i<40; i++){
      printf("%d: Opcode: %d Opres: %d Oprand1: %d Oprand2: %d\n", i, INSTR_opcode[i], INSTR_operandres[i], INSTR_operand1[i], INSTR_operand2[i]);
  }


}
