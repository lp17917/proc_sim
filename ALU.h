#ifndef ALU
#define ALU

#include "types.h"

void init_a(struct A_LOGIC *alu);

void load_instruct_alu(struct A_LOGIC *alu, struct instruction *instr);

int is_finished(struct A_LOGIC *alu);

int get_out_reg(struct A_LOGIC *alu);

int get_out_result(struct A_LOGIC *alu);

void perform_cycle_alu(struct A_LOGIC *alu);

#endif
