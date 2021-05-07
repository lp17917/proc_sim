#include <stdio.h>
#include "types.h"
#include "dispatch_queue.h"
#include "res_station.h"


int main() {
  struct instruction instr;
  struct DISPATCH queued_instruct;
  struct RES_STAT res_s;
  init_d(&queued_instruct);
  init_r(&res_s, 0);
  instr.opcode = ADD;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;

  add_disp_instr(&queued_instruct, instr);

  instr.opcode = BRANCH_LT;
  instr.operandres = 1;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = LOAD;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = MUL;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = BRANCH_NOT_ZERO;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = ADD_I;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = ADD;
  instr.operandres = 2;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  instr.opcode = STORE;
  instr.operandres = 5;
  instr.operand1 = 15;
  instr.operand2 = 10;
  add_disp_instr(&queued_instruct, instr);
  printf("is full: %d\n", is_full(&queued_instruct));
  if (!is_busy(&res_s)){
    dispatch(&queued_instruct, &instr);
  }

}
