#ifndef dispatch_queue
#define dispatch_queue

#include "types.h"

void init_d(struct DISPATCH *queued_instruct);

void add_disp_instr(struct DISPATCH *queued_instruct, struct instruction new);

int can_dispatch(struct DISPATCH *queued_instruct, int alu_free, int mem_u_free, int bran_free);

void dispatch(struct DISPATCH *queued_instruct, struct instruction *instr);

int is_full(struct DISPATCH *queued_instruct);

#endif
