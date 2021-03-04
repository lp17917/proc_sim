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

struct INSTUCTIONS {
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
};

void add_instr(int i, int opcode, int operandres, int operand1, int operand2, struct INSTUCTIONS *instr_set);

void print_instuction(struct INSTUCTIONS *instr_set, int i);


void vector_addition_set_reg_store(struct INSTUCTIONS *instr_set){
  int i = 0;
  int a[10] = {10,5,2,2,50,7,1,99,52,0};
  int b[10] = {15,1,100,100,10,13,0,1,132,0};
  /*000*/add_instr(i, LOAD_VALUE,  10,  100,   0, instr_set); i++;
  /*001*/add_instr(i, LOAD_VALUE,  11,  150,   0, instr_set); i++;
  /*002*/add_instr(i, LOAD_VALUE,  12,  200,   0, instr_set); i++;
  for (int r = 0; r < 10; r++){
/*003-030*/add_instr(i, STORE_VALUE,  a[r],  10,  0, instr_set); i++;
/*004-031*/add_instr(i, STORE_VALUE,  b[r],  11,  0, instr_set); i++;
/*005-032*/add_instr(i,       ADD_I,     0,   0,  1, instr_set); i++; //set counter to counter + 1
  }
  /*033*/add_instr(i, LOAD_VALUE,   0,   0,   0, instr_set); i++; //Resets counter
  /*034*/add_instr(i, LOAD_VALUE,   5,  10,   2, instr_set); i++; //Sets loop length

  //Add to allow for the printing of the arrays corretly

  /*035*/add_instr(i,       LOAD,   1,  10,   0, instr_set); i++; //Load a[i] into register 1
  /*036*/add_instr(i,  PRINT_INT,   1,   0,   0, instr_set); i++; //Prints value of a[i]
  /*037*/add_instr(i, PRINT_CHAR,  32,   0,   0, instr_set); i++; //Prints value of a[i]//Prints a space


  /*038*/add_instr(i,       LOAD,   2,  11,   0, instr_set); i++; //Load b[i] into register 2
  /*039*/add_instr(i,  PRINT_INT,   2,   0,   0, instr_set); i++; //Prints value of b[i]
  /*040*/add_instr(i, PRINT_CHAR,  32,   0,   0, instr_set); i++; //Prints a space


  /*041*/add_instr(i,        ADD,   3,   1,   2, instr_set); i++; //Add register 1 and 2 and put the result in reg 3
  /*042*/add_instr(i,      STORE,   3,  12,   2, instr_set); i++; //Store the value in reg 3 in memory
  /*043*/add_instr(i,  PRINT_INT,   3,   0,   0, instr_set); i++; //Prints value of r[i]
  /*044*/add_instr(i, PRINT_CHAR,  32,   0,   0, instr_set); i++; //Prints a space
  /*045*/add_instr(i, PRINT_CHAR,  10,   0,   0, instr_set); i++; //Prints a newline

  /*046*/add_instr(i,      ADD_I,  32,   0,   1, instr_set); i++; //Increment memory counter
  /*047*/add_instr(i,  BRANCH_LT,  35,   0,   5, instr_set); i++; //Branch if loop ended
  /*048*/add_instr(i,       HALT,   0,   0,   0, instr_set); i++;   //Finish the program

  //Printing using loop after reading again
}



void add_instr(int i, int opcode, int operandres, int operand1, int operand2, struct INSTUCTIONS *instr_set){
  instr_set->INSTR_opcode[i] = opcode;
  instr_set->INSTR_operandres[i] = operandres;
  instr_set->INSTR_operand1[i] = operand1;
  instr_set->INSTR_operand2[i] = operand2;
}

void print_instuction(struct INSTUCTIONS *instr_set, int i){
  printf("INSTRUCTION %d: opcode: %d opres: %d ", i, instr_set->INSTR_opcode[i], instr_set->INSTR_operandres[i]);
  printf("oprand1: %d operand2: %d\n", instr_set->INSTR_operand1[i], instr_set->INSTR_operand2[i]);
}


int main(){
  struct INSTUCTIONS instruction_set;
  for (int i=0; i<512; i++){
      add_instr(0, 0, 0, 0, 0, &instruction_set);
  }
  vector_addition_set_reg_store(&instruction_set);
  for (int i=0; i<40; i++){
      print_instuction(&instruction_set, i);
  }


}
