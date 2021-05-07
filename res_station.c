#include <stdio.h>
#include "res_station.h"

void init_r(struct RES_STAT *res_s, int id){
  res_s->res_id = id;
  res_s->busy = 0;
  res_s->executinginstruction.opcode = NOOP;
  res_s->opval1 = -1;
  res_s->opval2 = -1;
  res_s->opreg1 = -1;
  res_s->opreg2 = -1;
  res_s->opreg1res = -1;
  res_s->opreg2res = -1;
  res_s->opvalr = -1;
  res_s->opregr = -1;
  res_s->opregrres = -1;
}

int is_busy(struct RES_STAT *res_s){
  return res_s->busy;
}

void set_busy(struct RES_STAT *res_s, int b){
  res_s->busy = b;
}


int is_ready(struct RES_STAT *res_s){
  if (res_s->opreg1 == -1 && res_s->opreg2 == -1 && res_s->opregr == -1){ return 1;}
  return 0;
}

void add_instr_res(struct RES_STAT *res_s, struct instruction *instruct, int ova1, int oval2, int ovalr, int oprg1, int oprg2, int oprgr, int opres1, int opres2, int opresr){
  res_s->executinginstruction = *instruct;
  res_s->opval1 = ova1;
  res_s->opval2 = oval2;
  res_s->opreg1 = oprg1;
  res_s->opreg2 = oprg2;
  res_s->opreg1res = opres1;
  res_s->opreg2res = opres2;
  res_s->opvalr = ovalr;
  res_s->opregr = oprgr;
  res_s->opregrres = opresr;
  res_s->busy = 1;
}

int check_operand(struct RES_STAT *res_s, int res_id, int reg_val, int res_value){
  if (res_id == res_s->opreg1res && reg_val == res_s->opreg1 && res_s->opreg1 != -1){
    res_s->opreg1res = -1;
    res_s->opreg1 = -1;
    res_s->opval1 = res_value;
  }
  else if (res_id == res_s->opreg2res && reg_val == res_s->opreg2 && res_s->opreg2 != -1){
    res_s->opreg2res = -1;
    res_s->opreg2 = -1;
    res_s->opval2 = res_value;
  }
  else if (res_id == res_s->opregrres && reg_val == res_s->opregr && res_s->opregr != -1){
    res_s->opregrres = -1;
    res_s->opregr = -1;
    res_s->opvalr = res_value;
  }
}
