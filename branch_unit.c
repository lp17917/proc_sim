#include "branch_unit.h"


void set_cycles_branch(struct BRANCH_U *branchunit);

void load_instuct_branch(struct BRANCH_U *branchunit, struct instruction *instr){
  branchunit->executinginstruction = *instr;
  set_cycles_m(branchunit);
}


int get_location(struct BRANCH_U *branchunit);

int is_jumping(struct BRANCH_U *branchunit);


void set_cycles_m(struct MEM_U *memo){
  switch(memo->executinginstruction.opcode){

    memo->cycles_left = 3; break;
    case BRANCH_LT:
			if (RF[s1] < RF[s2]){ branch_pc(fetcher, r); break;}
      else {branch_pc(fetcher, (fetcher->PC) + 1); break;}
		case BRANCH_NOT_ZERO:
			if (RF[s1] != 0) {branch_pc(fetcher, r); break;}
      else {branch_pc(fetcher, (fetcher->PC) + 1); break;}
		case ABS_JUMP:
			branch_pc(fetcher, r); break;
    case REL_JUMP:
      branch_pc(fetcher, (fetcher->PC) + s1); break;

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


int is_finished_branch(struct BRANCH_U *branchunit){
  if ((branchunit->cycles_left) < 1){
    return 1;
  }
  else{
    return 0;
  }
}

void perform_cycle_branch_u(struct BRANCH_U *branchunit){
  if (!(is_finished_branch(branchunit)) && branchunit->cycles_left >= 0){
    branchunit->cycles_left -=1;
    if ((is_finished_branch(branchunit))){
      set_result_branch(branchunit);

    }
  }
  else if (branchunit->cycles_left == 0){
    branchunit->cycles_left = -1;
    branchunit->out_reg = -1;
    branchunit->out_result = -1;
  }
}
