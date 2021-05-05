/*Benchmarks for benchmark the processor simulator*/
#include <stdio.h>
#include "benchmarks.h"

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
#define R16 16
#define R17 17

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

void add_instr(int i, int opcode, int operandres, int operand1, int operand2, struct INSTRUCTIONS *instr_set);

void print_instruction(struct INSTRUCTIONS *instr_set, int i);

void vector_addition_set_reg_store(struct INSTRUCTIONS *instr_set){
  int i = 0;
  int a[10] = {10,5,2,182,50,7,1,99,52,213};
  int b[10] = {15,1,100,171,10,13,0,1,132,999};
  /*000*/add_instr(i, LOAD_VALUE,  R10,  100,   0, instr_set); i++;
  /*001*/add_instr(i, LOAD_VALUE,  R11,  150,   0, instr_set); i++;
  /*002*/add_instr(i, LOAD_VALUE,  R12,  200,   0, instr_set); i++;
  for (int r = 0; r < 10; r++){
/*003-030*/add_instr(i, STORE_VALUE,  a[r], R10,  0, instr_set); i++;
/*004-031*/add_instr(i, STORE_VALUE,  b[r], R11,  0, instr_set); i++;
/*005-032*/add_instr(i,       ADD_I,    R0,  R0,  1, instr_set); i++; //set counter to counter + 1
  }
  /*033*/add_instr(i, LOAD_VALUE,  R0,   0,   0, instr_set); i++; //Resets counter
  /*034*/add_instr(i, LOAD_VALUE,  R5,  10,   0, instr_set); i++; //Sets loop length

  //Add to allow for the printing of the arrays corretly

  /*035*/add_instr(i,       LOAD,  R1, R10,  R0, instr_set); i++; //Load a[i] into register 1
  /*036*/add_instr(i,  PRINT_INT,  R1,   0,   0, instr_set); i++; //Prints value of a[i]
  /*037*/add_instr(i, PRINT_CHAR,  43,   0,   0, instr_set); i++; //Prints a space


  /*038*/add_instr(i,       LOAD,  R2, R11,  R0, instr_set); i++; //Load b[i] into register 2
  /*039*/add_instr(i,  PRINT_INT,  R2,   0,   0, instr_set); i++; //Prints value of b[i]
  /*040*/add_instr(i, PRINT_CHAR,  61,   0,   0, instr_set); i++; //Prints an equals


  /*041*/add_instr(i,        ADD,  R3,  R1,  R2, instr_set); i++; //Add register 1 and 2 and put the result in reg 3
  /*042*/add_instr(i,      STORE,  R3, R12,  R0, instr_set); i++; //Store the value in reg 3 in memory
  /*043*/add_instr(i,  PRINT_INT,  R3,   0,   0, instr_set); i++; //Prints value of r[i]
  /*045*/add_instr(i, PRINT_CHAR,  10,   0,   0, instr_set); i++; //Prints a newline

  /*046*/add_instr(i,      ADD_I,  R0,  R0,   1, instr_set); i++; //Increment memory counter
  /*047*/add_instr(i,  BRANCH_LT,  35,  R0,  R5, instr_set); i++; //Branch if loop ended
  /*048*/add_instr(i,       HALT,   0,   0,   0, instr_set); i++;   //Finish the program

  //Printing using loop after reading again
}


void bubble_sort(struct INSTRUCTIONS *instr_set){
  int i = 0;
  int a[20] = {10,5,2,182,50,7,1,99,52,213, 15,1,100,171,10,13,0,1,132,999};
  /*000*/add_instr(i, LOAD_VALUE,  R10,  100,   0, instr_set); i++; //Sets the memory address for the list
  for (int r = 0; r < 20; r++){
/*001-039*/add_instr(i, STORE_VALUE,  a[r], R10,  0, instr_set); i++;
/*002-040*/add_instr(i,       ADD_I,    R0,  R0,  1, instr_set); i++; //set counter to counter + 1
  }
  /*041*/add_instr(i, LOAD_VALUE,    R0,  18,  0, instr_set); i++; //set outer loop counter to 18
  /*042*/add_instr(i, LOAD_VALUE,    R1,   0,  0, instr_set); i++; //set inner loop counter to 0
  /*043*/add_instr(i,       LOAD,    R5, R10, R1, instr_set); i++; //get first list element
  /*044*/add_instr(i,      ADD_I,    R2,  R1,  1, instr_set); i++; //get next mem address
  /*045*/add_instr(i,       LOAD,    R6, R10, R2, instr_set); i++; //get second list element
  /*046*/add_instr(i,  BRANCH_LT,   250,  R6, R5, instr_set); i++; //Branch if r6 < r5 to make swap
  /*047*/add_instr(i,      ADD_I,    R1,  R1,  1, instr_set); i++; //get next mem address
  /*048*/add_instr(i, BRANCH_NOT_ZERO, 200,  R0,  0, instr_set); i++; //Branch if R0 is not 0
  /*049*/add_instr(i, LOAD_VALUE,    R1,   0,  0, instr_set); i++;

  for (int r = 0; r < 20; r++){
/*050-126*/add_instr(i,        LOAD,    R0, R10, R1, instr_set); i++;
/*051-127*/add_instr(i,       ADD_I,    R1,  R1,  1, instr_set); i++; //set counter to counter + 1
/*052-128*/add_instr(i,   PRINT_INT,    R0,   0,  0, instr_set); i++;
/*053-129*/add_instr(i,  PRINT_CHAR,    32,   0,  0, instr_set); i++;
  }
  /*130*/add_instr(i,  PRINT_CHAR,    10,   0,  0, instr_set); i++;
  /*131*/add_instr(i,       HALT,     0,   0,  0, instr_set); i++; //End program


  i = 200;
  /*060*/add_instr(i,  BRANCH_LT,   150,  R0, R1, instr_set); i++; //Branch if r6 < r5 to make swap
  /*061*/add_instr(i,   ABS_JUMP,    43,   0,  0, instr_set); i++; //Branch if r6 < r5 to make swap

  i = 250;
  /*100*/add_instr(i,      STORE,    R6, R10,  R1, instr_set); i++; //Store R6 where R5 was taken from
  /*101*/add_instr(i,      STORE,    R5, R10,  R2, instr_set); i++; //Store R5 where R6 was taken from
  /*102*/add_instr(i,   ABS_JUMP,    48,   0,   0, instr_set); i++; //Jump back to loop
i = 150;
  /*150*/add_instr(i,      ADD_I,    R0,  R0,  -1, instr_set); i++; //Jump back to loop
  /*151*/add_instr(i,   ABS_JUMP,    42,   0,   0, instr_set); i++; //Jump back to loop


}

void factorial(struct INSTRUCTIONS *instr_set){
  int i = 0;
  /*000*/add_instr(i, LOAD_VALUE,  R0,  12,   0, instr_set); i++;
  /*001*/add_instr(i, LOAD_VALUE,  R1,  11,   0, instr_set); i++;
  /*002*/add_instr(i, LOAD_VALUE,  R2,  12,   0, instr_set); i++;
  /*003*/add_instr(i,        MUL,  R0,  R0,  R1, instr_set); i++;
  /*004*/add_instr(i,      ADD_I,  R1,  R1,  -1, instr_set); i++;
  /*005*/add_instr(i, BRANCH_NOT_ZERO,   3,  R1,  0, instr_set); i++;
  /*006*/add_instr(i,  PRINT_INT,  R2,   0,  0, instr_set); i++;
  /*007*/add_instr(i, PRINT_CHAR,  33,   0,  0, instr_set); i++;
  /*008*/add_instr(i, PRINT_CHAR,  61,   0,  0, instr_set); i++;
  /*009*/add_instr(i, PRINT_CHAR,  32,   0,  0, instr_set); i++;
  /*010*/add_instr(i,  PRINT_INT,  R0,   0,  0, instr_set); i++;
  /*011*/add_instr(i, PRINT_CHAR,  10,   0,  0, instr_set); i++;
  /*012*/add_instr(i,       HALT,   0,   0,  0, instr_set); i++; //End program

}


void add_instr(int i, int opcode, int operandres, int operand1, int operand2, struct INSTRUCTIONS *instr_set){
  instr_set->INSTR_opcode[i] = opcode;
  instr_set->INSTR_operandres[i] = operandres;
  instr_set->INSTR_operand1[i] = operand1;
  instr_set->INSTR_operand2[i] = operand2;
}

void print_instruction(struct INSTRUCTIONS *instr_set, int i){
  printf("INSTRUCTION %d: opcode: %d opres: %d ", i, instr_set->INSTR_opcode[i], instr_set->INSTR_operandres[i]);
  printf("oprand1: %d operand2: %d\n", instr_set->INSTR_operand1[i], instr_set->INSTR_operand2[i]);
}


void clear_instr(struct INSTRUCTIONS *instruction_set){
  for (int i=0; i<512; i++){
      add_instr(0, NOOP, 0, 0, 0, instruction_set);
  }
}


void generate(int i, struct INSTRUCTIONS *instruction_set){

  for (int i=0; i<512; i++){
      add_instr(0, NOOP, 0, 0, 0, instruction_set);
  }
  switch (i)
  {
  case 1:
    vector_addition_set_reg_store(instruction_set); break;
  case 2:
    bubble_sort(instruction_set); break;
  case 3:
    factorial(instruction_set); break;
  }
}
