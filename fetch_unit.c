#include <stdio.h>
#include "fetch_unit.h"



void load_instructs_fetch(struct FETCH_UNIT *fetcher, int *opcode, int *operandres, int *operand1, int *operand2){
  for (int i=0; i<512; i++){
    fetcher->INSTR_opcode[i] = opcode[i];
    fetcher->INSTR_operandres[i] = operandres[i];
    fetcher->INSTR_operand1[i] = operand1[i];
    fetcher->INSTR_operand2[i] = operand2[i];
  }

  fetcher->PC = 0;
  fetcher->waiting = 0;
  fetcher->halted = 0;
}

int Fetch(struct instruction *instr, struct FETCH_UNIT *fetcher){
  instr->opcode = fetcher->INSTR_opcode[fetcher->PC];
  instr->operandres = fetcher->INSTR_operandres[fetcher->PC];
  instr->operand1 = fetcher->INSTR_operand1[fetcher->PC];
  instr->operand2 = fetcher->INSTR_operand2[fetcher->PC];
  return 0;
}

void increment_pc(struct FETCH_UNIT *fetcher){
  fetcher->PC++;
}

int get_waiting(struct FETCH_UNIT *fetcher){
  return fetcher->waiting;
}

void set_waiting(struct FETCH_UNIT *fetcher, int wait){
  fetcher->waiting = wait;
}

void branch_pc(struct FETCH_UNIT *fetcher, int location){
  fetcher->PC = location;
  if (get_waiting(fetcher)) {
    set_waiting(fetcher, 0);
  }
}

int get_halt(struct FETCH_UNIT *fetcher){
  return fetcher->halted;
}

void set_halt(struct FETCH_UNIT *fetcher, int halt){
  fetcher->halted = halt;
}
