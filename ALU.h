#ifndef ALU
#define ALU

#inclued "types.h"

void load_instuct_alu(struct INSTRUCTIONS *instruction_set);

void is_finished(struct ALU *alu);

void get_out_reg(struct ALU *alu);

void perform_cycle_alu(struct ALU *alu);

#endif
