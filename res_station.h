#ifndef res_station
#define res_station

#include "types.h"

void init_r(struct RES_STAT *res_s, int id);

int is_busy(struct RES_STAT *res_s);

void set_busy(struct RES_STAT *res_s, int b);

int is_ready(struct RES_STAT *res_s);

void add_instr_res(struct RES_STAT *res_s, struct instruction *instruct, int ova1, int oval2, int ovalr, int oprg1, int oprg2, int oprgr, int opres1, int opres2, int opresr);

int check_operand(struct RES_STAT *res_s, int res_id, int reg_val,  int res_value);

#endif
