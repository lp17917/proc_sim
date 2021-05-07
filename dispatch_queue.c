#include <stdio.h>
#include "dispatch_queue.h"

void init_d(struct DISPATCH *queued_instruct){
  for (int i = 0; i < 8; i++){
    queued_instruct->queued_instr[i].opcode = NOOP;
    queued_instruct->queued_instr[i].operandres = NOOP;
    queued_instruct->queued_instr[i].operand1 = NOOP;
    queued_instruct->queued_instr[i].operand2 = NOOP;
  }
}

void add_disp_instr(struct DISPATCH *queued_instruct, struct instruction new){
  for (int i = 0; i < 8; i++){
    if (queued_instruct->queued_instr[i].opcode == NOOP){
      queued_instruct->queued_instr[i] = new;
      return;
    }
  }
}

int can_dispatch(struct DISPATCH *queued_instruct, int alu_free, int mem_u_free, int bran_free){
  int validnexte;
  int validnextq;
  int room;
  room = 0;
  validnexte = 1;
  if (queued_instruct->queued_instr[0].opcode < 200 && alu_free){

    return 1;
  }
  else if (queued_instruct->queued_instr[0].opcode < 300 && queued_instruct->queued_instr[0].opcode >= 200 && mem_u_free){

    return 1;
  }
  else if (queued_instruct->queued_instr[0].opcode < 400 && queued_instruct->queued_instr[0].opcode >= 300 && bran_free){

    return 1;
  }
  return 0;
}

void dispatch(struct DISPATCH *queued_instruct, struct instruction *instr){
  instr->opcode = queued_instruct->queued_instr[0].opcode;
  instr->operandres = queued_instruct->queued_instr[0].operandres;
  instr->operand1 = queued_instruct->queued_instr[0].operand1;
  instr->operand2 = queued_instruct->queued_instr[0].operand2;
  for (int i = 0; i < 7; i++){
    queued_instruct->queued_instr[i] = queued_instruct->queued_instr[i+1];
  }
  queued_instruct->queued_instr[7].opcode = NOOP;
}

int is_full(struct DISPATCH *queued_instruct){
  if (queued_instruct->queued_instr[7].opcode == NOOP){return 0;}
  else {return 1;}
}
