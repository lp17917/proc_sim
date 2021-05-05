#include <stdio.h>
#include "ALU.h"

void set_cycles(struct A_LOGIC *alu);

void load_instuct_alu(struct A_LOGIC *alu, struct instruction *instr){
  alu->executinginstruction = *instr;
  set_cycles(alu);
}

void set_cycles(struct A_LOGIC *alu){
  switch(alu->executinginstruction.opcode){

    case ADD:
      alu->cycles_left = 1; break;
    case ADD_I:
      alu->cycles_left = 1; break;
    case MUL:
      alu->cycles_left = 2; break;
    case CMP:
      alu->cycles_left = 1; break;
    case AND:
      alu->cycles_left = 1; break;
    case OR:
      alu->cycles_left = 1; break;
    case L_SHIFT:
      alu->cycles_left = 1; break;
    case R_SHIFT:
      alu->cycles_left = 1; break;
    case NOT:
      alu->cycles_left = 1; break;

  }

}


void set_result(struct A_LOGIC *alu){
  alu->out_reg = alu->executinginstruction.operandres;
  int s1 = alu->executinginstruction.operand1;
  int s2 = alu->executinginstruction.operand2;
  switch(alu->executinginstruction.opcode){

		case ADD:
			alu->out_result = s1 + s2; break;
    case ADD_I:
      alu->out_result = s1 + s2; break;
		case MUL:
			alu->out_result = s1 * s2; break;
    case CMP:
      if (s1 == s2){ alu->out_result = 0; break;}
      else if (s1 < s2){ alu->out_result = -1; break;}
      else {alu->out_result = 1; break;}
    case AND:
      alu->out_result = s1 & s2; break;
    case OR:
      alu->out_result = s1 | s2; break;
    case L_SHIFT:
      alu->out_result = s1 << s2; break;
    case R_SHIFT:
      alu->out_result = s1 >> s2; break;
    case NOT:
      alu->out_result = ~s1; break;

  }

}

int is_finished(struct A_LOGIC *alu){

  if (!(alu->cycles_left)){
    return 1;
  }
  else{
    return 0;
  }
}

int get_out_reg(struct A_LOGIC *alu){
  return alu->out_reg;
}

int get_out_result(struct A_LOGIC *alu){
  return alu->out_result;
}


void perform_cycle_alu(struct A_LOGIC *alu){
  if (!(is_finished(alu))){
    alu->cycles_left -=1;
    if ((is_finished(alu))){
      set_result(alu);

    }
  }
  else{
    return;
  }
}
