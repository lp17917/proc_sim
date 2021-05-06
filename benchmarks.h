#ifndef benchmarks
#define benchmarks

#include "types.h"

void generate(int i, struct INSTRUCTIONS *instruction_set);

void print_instuction(struct INSTRUCTIONS *instr_set, int i);

void clear_instr(struct INSTRUCTIONS *instr_set);

#endif
