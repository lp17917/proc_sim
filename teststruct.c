#define ADD 100
#include <stdio.h>
struct INSTUCTIONS {
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
};


void add_instr(int i, int opcode, int operandres, int operand1, int operand2, struct INSTUCTIONS *instr_set);
void print_instuction(struct INSTUCTIONS *instr_set, int i);


int main(){
  struct INSTUCTIONS instruction_set;
  add_instr(0, ADD, 1, 1, 1, &instruction_set);
  print_instuction(&instruction_set, 0);
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
