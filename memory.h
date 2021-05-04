#ifndef MEMORY
#define MEMORY

#inclued "types.h"

void load_instuct_memory(struct INSTRUCTIONS *instruction_set);

void is_finished(struct memory *memory);

void perform_cycle_memory(struct ALU *alu);

#endif
