#include <stdio.h>
#include "dispatch_queue.h"

init_d(struct instruction *queued_instruct){
  for (int i = 0; i < 8; i++){
    queued_instruct[i]->opcode = NOOP;
    queued_instruct[i]->operandres = NOOP;
    queued_instruct[i]->operand1 = NOOP;
    queued_instruct[i]->operand2 = NOOP;
  }
}

void add_disp_instr(struct instruction *queued_instruct, struct instruction *new){
  for (int i = 0; i < 8; i++){
    if (queued_instruct[i]->opcode != NOOP){
      queued_instruct[i] = new;
      return;
    }
  }
}

int can_dispatch(struct instruction *queued_instruct, int alu_free, int mem_u_free, int bran_free){
  int validnexte;
  int validnextq;
  int room;
  room = 0;
  validnexte = 1;
  if (queued_instruct[0]->opcode < 200 && alu_free){

    return 1;
  }
  else if (queued_instruct[0]->opcode < 300 && queued_instruct[i]->opcode >= 200 && mem_u_free){

    return 1;
  }
  else if (queued_instruct[0]->opcode < 400 && queued_instruct[i]->opcode >= 300 && bran_free){

    return 1;
  }
  return 0;
}

int is_full(struct instruction *queued_instruct){
  if (queued_instruct[7]->opcode == NOOP){return 0;}
  else {return 1;}
}
