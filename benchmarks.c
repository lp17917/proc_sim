#include <stdio.h>
#define LOAD_VALUE 1;
#define STORE_VALUE 2;


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
    /*005*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 1; i++; //set counter to counter + 1
  }
  /*033*/INSTR_opcode[i] = LOAD_VALUE; INSTR_operandres[i] = 0; INSTR_operand1[i] = 0; INSTR_operand2[i] = 0; i++;
  printf("%d\n", i);

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
