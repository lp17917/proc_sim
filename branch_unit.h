#ifndef branch_unit
#define branch_unit

#include "types.h"

void init_b(struct BRANCH_U *branchunit);

void load_instruct_branch(struct BRANCH_U *branchunit, struct instruction *instr);

int is_finished_branch(struct BRANCH_U *branchunit);

int get_location(struct BRANCH_U *branchunit);

int is_jumping(struct BRANCH_U *branchunit);

void perform_cycle_branch_u(struct BRANCH_U *branchunit);

#endif
