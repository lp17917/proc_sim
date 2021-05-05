#include "memory.h"


void set_cycles_m(struct MEM_U *memo);

void load_instruct_memory(struct MEM_U *memo, struct instruction *instr){
  memo->executinginstruction = *instr;
  set_cycles_m(memo);
}


void set_cycles_m(struct MEM_U *memo){
  switch(memo->executinginstruction.opcode){

    case LOAD:
      memo->cycles_left = 3; break;
    case LOAD_VALUE:
      memo->cycles_left = 1; break;
    case STORE:
      memo->cycles_left = 2; break;
    case STORE_VALUE:
      memo->cycles_left = 2; break;

  }
}

int get_out_reg_m(struct MEM_U *memo){
  return memo->out_reg;
}

int get_out_result_m(struct MEM_U *memo){
  return memo->out_result;
}

void set_result_m(struct MEM_U *memo){
  int s1 = memo->executinginstruction.operand1;
  int s2 = memo->executinginstruction.operand2;
  switch(memo->executinginstruction.opcode){

		case LOAD:
      memo->out_reg = memo->executinginstruction.operandres;
			memo->out_result = memo->MEM[s1 + s2]; break;
    case LOAD_VALUE:
      memo->out_result = s1;
      memo->out_reg = memo->executinginstruction.operandres; break;
		case STORE:
			memo->MEM[s1 + s2] = memo->executinginstruction.operandres;
      memo->out_result = -1;
      memo->out_reg = -1; break;
    case STORE_VALUE:
      memo->MEM[s1 + s2] = memo->executinginstruction.operandres;
      memo->out_result = -1;
      memo->out_reg = -1; break;

  }

}


int is_finished_mem(struct MEM_U *memo){
  if ((memo->cycles_left) < 1){
    return 1;
  }
  else{
    return 0;
  }
}

void perform_cycle_memory(struct MEM_U *memo){
  if (!(is_finished_mem(memo)) && memo->cycles_left >= 0){
    memo->cycles_left -=1;
    if ((is_finished_mem(memo))){
      set_result_m(memo);

    }
  }
  else if (memo->cycles_left == 0){
    memo->cycles_left = -1;
    memo->out_reg = -1;
    memo->out_result = -1;
  }
}
