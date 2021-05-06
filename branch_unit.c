#include "branch_unit.h"


void init_b(struct BRANCH_U *branchunit){
  branchunit->executinginstruction.opcode = NOOP;
  branchunit->cycles_left = 0;
  branchunit->out_result = -1;
  branchunit->jump = -1;
}

void set_cycles_branch(struct BRANCH_U *branchunit);

void load_instruct_branch(struct BRANCH_U *branchunit, struct instruction *instr){
  branchunit->executinginstruction = *instr;
  branchunit->cycles_left = 1;
}

int is_jumping(struct BRANCH_U *branchunit){
  return branchunit->jump;
}

int get_location(struct BRANCH_U *branchunit){
  return branchunit->out_result;
}

void set_result_branch(struct BRANCH_U *branchunit){
  int s1 = branchunit->executinginstruction.operand1;
  int s2 = branchunit->executinginstruction.operand2;
  int r = branchunit->executinginstruction.operandres;
  switch(branchunit->executinginstruction.opcode){

    case BRANCH_LT:
			if (s1 < s2){ branchunit->jump = 1; branchunit->out_result = r; break;}
      else {branchunit->jump = 0; branchunit->out_result = 0; break;}
		case BRANCH_NOT_ZERO:
			if (s1 != 0) {branchunit->jump = 1; branchunit->out_result = r; break;}
      else {branchunit->jump = 0; branchunit->out_result = 0; break;}
		case ABS_JUMP:
			branchunit->jump = 1; branchunit->out_result = r; break;

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
  if (!(is_finished_branch(branchunit))){
    branchunit->cycles_left -=1;
    if ((is_finished_branch(branchunit))){
      set_result_branch(branchunit);

    }
  }

  else if (branchunit->cycles_left == 0){
    branchunit->cycles_left = -1;
    branchunit->jump = -1;
    branchunit->out_result = -1;
  }
}
