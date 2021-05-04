#ifndef fetch_unit
#define fetch_unit

#include "types.h"


void load_instructs(struct FETCH_UNIT *fetcher, int *INSTR_opcode, int *INSTR_operandres, int *INSTR_operand1, int *INSTR_operand2);

int Fetch(struct instruction *instr, struct FETCH_UNIT *fetcher);

void increment_pc(struct FETCH_UNIT *fetcher);

void branch_pc(struct FETCH_UNIT *fetcher, int location);

int get_waiting(struct FETCH_UNIT *fetcher);

void set_waiting(struct FETCH_UNIT *fetcher, int wait);

#endif
