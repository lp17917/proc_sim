#ifndef MEMORY
#define MEMORY

#include "types.h"

void load_instruct_memory(struct MEM_U *memo, struct instruction *instr);

int is_finished_mem(struct MEM_U *memo);

int get_out_reg_m(struct MEM_U *memo);

int get_out_result_m(struct MEM_U *memo);

void perform_cycle_memory(struct MEM_U *memo);

#endif
