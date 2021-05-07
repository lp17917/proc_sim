#ifndef dispatch
#define dispatch

#include "types.h"

void init_d(struct instruction *queued_instruct);

void add_disp_instr(struct instruction *queued_instruct);

void can_dispatch(struct instruction *queued_instruct);

int is_full(struct instruction *queued_instruct);

#endif
