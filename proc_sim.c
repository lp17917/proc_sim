#include <stdio.h>
#include "benchmarks.h"
#include "fetch_unit.h"
#include "types.h"
#include <unistd.h>
#include "ALU.h"
#include "memory.h"
#include "branch_unit.h"


int check_forwarded(int *backloc, int *backval, int loc){
  int j = -1;
  for (int i = 0; i <32; i++){
    if (backloc[i] == loc){
      j = backval[i];
    }
  }

  return j;
}


void load_instr(struct A_LOGIC *alu, struct MEM_U *memo, struct BRANCH_U *branchunit, struct instruction *instr, int *RF, int *backloc, int *backval){
  struct instruction loader;
  int fvalr = -1;
  int fval1 = -1;
  int fval2 = -1;
  fval1 = check_forwarded(backloc, backval, instr->operand1);
  fval2 = check_forwarded(backloc, backval, instr->operand2);
  fvalr = check_forwarded(backloc, backval, instr->operandres);
  if (instr->opcode < 200){
    switch(instr->opcode)
    {
      case ADD_I:
       loader.operand2 = instr->operand2; break;
      default:
        if (fval2 == -1){ loader.operand2 = RF[instr->operand2]; }
        else{ loader.operand2 = fval2; }
      break;
    }
    loader.opcode = instr->opcode;
    loader.operandres = instr->operandres;

    if (fval1 == -1){ loader.operand1 = RF[instr->operand1]; }
    else{ loader.operand1 = fval1; }

    load_instruct_alu(alu, &loader);
  }


  else if(instr->opcode >= 200 && instr->opcode < 300){
    switch(instr->opcode)
    {

      case LOAD_VALUE:
        loader.operandres = instr->operandres; loader.operand1 = instr->operand1; break;

      case STORE:
        if (fvalr == -1){ loader.operandres = RF[instr->operandres]; }
        else{ loader.operandres = fvalr; }

        if (fval1 == -1){ loader.operand1 = RF[instr->operand1]; }
        else{ loader.operand1 = fval1; }
        break;


      default:
        loader.operandres = instr->operandres;
        if (fval1 == -1){ loader.operand1 = RF[instr->operand1]; }
        else{ loader.operand1 = fval1; }
        break;

    }

    loader.opcode = instr->opcode;

    if (fval2 == -1){ loader.operand2 = RF[instr->operand2];}
    else{loader.operand2 = fval2;}

    load_instruct_memory(memo, &loader);
  }

  else if(instr->opcode >= 300 && instr->opcode < 400){
    loader.opcode = instr->opcode;
    loader.operandres = instr->operandres;

    if (fval1 == -1){ loader.operand1 = RF[instr->operand1]; }
    else{ loader.operand1 = fval1; }

    if (fval2 == -1){ loader.operand2 = RF[instr->operand2];}
    else{loader.operand2 = fval2;}
    load_instruct_branch(branchunit, &loader);
  }

}

int Decode(){
  return 0;
}



void print_instr(struct instruction *instr){
  printf("executing instruction: %d r: %d S1:%d S2:%d\n",instr->opcode,instr->operandres,instr->operand1,instr->operand2);
}


void checkifbranch(struct instruction *instr, struct FETCH_UNIT *fetcher){
  switch(instr->opcode)

  {
    case BRANCH_LT:
      set_waiting(fetcher, 1); break;
    case BRANCH_NOT_ZERO:
      set_waiting(fetcher, 1); break;
    case ABS_JUMP:
      set_waiting(fetcher, 1); break;
    default:
      break;

  }

}

void checkifhalt(struct instruction *instr, struct FETCH_UNIT *fetcher){
  switch(instr->opcode)

  {
    case HALT:
      set_halt(fetcher, 1); break;
    default:
      break;

  }

}

void null_instr(struct instruction *instr){
  instr->opcode = NOOP;
  instr->operandres = 0;
  instr->operand1 = 0;
  instr->operand2 = 0;
}

int Execute(struct instruction *instr, int *RF, int *finished, struct A_LOGIC *alu, struct MEM_U *memo, struct BRANCH_U *branchunit, int *backloc, int *backval)
{
	int error = 0;
  if (instr->opcode < 400){
    load_instr(alu, memo, branchunit, instr, RF, backloc, backval);
  }

	else{
    int fvalr = -1;
    fvalr = check_forwarded(backloc, backval, instr->operandres);
    switch(instr->opcode){
    case PRINT_INT:
      if (fvalr == -1){ printf("%d", RF[instr->operandres]); }
      else{ printf("%d", fvalr); }

      break;
    case PRINT_CHAR_REG:
      if (fvalr == -1){ printf("%c",(unsigned char)RF[instr->operandres] & 0xFF); }
      else{ printf("%c",(unsigned char)fvalr & 0xFF); }

      break;
    case PRINT_CHAR:
      printf("%c",(unsigned char)instr->operandres & 0xFF); break;

    case NOOP:
      break;
    case HALT:
      *finished = 1; break;
    default:
      printf("Error: Opcode not recognised: %d", instr->opcode); error = 1; break;

    }
  }
    //Print statements

	return error;
}

int writeback(int *backloc, int *backval, int *RF){
  for (int i = 0; i < 32; i++){
    if (backloc[i] != -1)
      //printf("writing: %d to location: %d\n", backval[i] , backloc[i]);
      RF[backloc[i]] = backval[i];
      backloc[i] = -1;
      backval[i] = 0;
  }
}

void add_writebuffer(int *backloc, int *backval, int res, int loc){
  int i = 0;
  while (backloc[i] != -1){
    i++;
  }
  backloc[i] = loc;
  backval[i] = res;
}


void run_instr_set(struct INSTRUCTIONS *instr_set){
  struct FETCH_UNIT fetch_u;
  struct A_LOGIC alu;
  struct MEM_U memo;
  struct BRANCH_U branchunit;
  struct instruction fetch_current;
  struct instruction decode_next;
  struct instruction decode_current;
  struct instruction execute_next;
  init_a(&alu);
  init_b(&branchunit);
  init_m(&memo);
  null_instr(&fetch_current);
  null_instr(&decode_next);
  null_instr(&decode_current);
  null_instr(&execute_next);
  load_instructs_fetch(&fetch_u, instr_set->INSTR_opcode, instr_set->INSTR_operandres, instr_set->INSTR_operand1, instr_set->INSTR_operand2);
  printf("set reloaded\n");
  int finished = 0;
  int cycles = 0;
  int instructions = 0;
  int RF[32] = {0};
  int WBloc[32];
  for (int i = 0; i < 32; i++){
    WBloc[i] = -1;
  }
  int WBval[32] = {0};
  while (!finished) {
    writeback(WBloc, WBval, RF);
    //printf("cycling branch\n");
    perform_cycle_branch_u(&branchunit);
    //printf("cycling alu\n");
    perform_cycle_alu(&alu);
    //printf("cycling memo\n");
    perform_cycle_memory(&memo);
    //printf("checking if branch writback\n");
    if (is_finished_branch(&branchunit)){
      if (is_jumping(&branchunit) == 0){
        branch_pc(&fetch_u, fetch_u.PC + 1);
      }
      else if (is_jumping(&branchunit)  == 1){
        branch_pc(&fetch_u, get_location(&branchunit));
      }

    }
    //printf("checking if alu writback\n");
    if (is_finished(&alu)){
      if (get_out_reg(&alu) >= 0){
        add_writebuffer(WBloc, WBval,  get_out_result(&alu), get_out_reg(&alu));
      }

    }
    //printf("checking if memory writback\n");
    if (is_finished_mem(&memo)){
      if (get_out_reg_m(&memo) >= 0){
        add_writebuffer(WBloc, WBval, get_out_result_m(&memo), get_out_reg_m(&memo));
      }

    }
    //printf("unit stats:\n");
    //printf("unit stats  alu finished: %d\n", is_finished(&alu));
    //printf("unit stats  memory finished: %d\n", is_finished_mem(&memo));
    //printf("unit stats  brancher finished: %d\n", is_finished_branch(&branchunit));
    if (is_finished(&alu) && is_finished_mem(&memo) && is_finished_branch(&branchunit)){
      Execute(&execute_next, RF, &finished, &alu, &memo, &branchunit, WBloc, WBval);
      if (!get_waiting(&fetch_u) && !get_halt(&fetch_u)){
        instructions++;
  		  Fetch(&fetch_current, &fetch_u);
      }
      else{
        null_instr(&fetch_current);
      }

      checkifhalt(&fetch_current, &fetch_u);
      checkifbranch(&fetch_current, &fetch_u);

      if (!get_waiting(&fetch_u) && !get_halt(&fetch_u)){
          increment_pc(&fetch_u);
      }

      decode_current = decode_next;
  		Decode();
      decode_next = fetch_current;
      execute_next = decode_current;
    }



    //printf("fetched instruction: %d\n" ,fetch_current.opcode);

    //print_instr(&fetch_current);

    cycles += 1;

	}
  /*
  for (int i = 0; i < 32; i++){
    printf("RF element: %d value %d\n" , i, RF[i]);
  }
  */
  printf("\ncycles:%d instructions:%d instructions per cycle: %3f\n", cycles, instructions, (float)instructions/(float)cycles);

}

int main() {


  struct INSTRUCTIONS instruction_set;

  generate(1, &instruction_set);
  printf("--------- Running vector addition ---------\n\n");
  run_instr_set(&instruction_set);
  printf("\n--------- Vector addition finished ---------\n\n");
  clear_instr(&instruction_set);

  generate(2, &instruction_set);
  printf("--------- Running bubble sort ---------\n\n");
  run_instr_set(&instruction_set);
  printf("\n--------- Finished bubble sort ---------\n\n");
  clear_instr(&instruction_set);

  generate(3, &instruction_set);
  printf("--------- Running factorial ---------\n\n");
  run_instr_set(&instruction_set);
  printf("\n--------- Finished factorial ---------\n\n");
  clear_instr(&instruction_set);
/*
  generate(4, &instruction_set);
  printf("--------- Running factorial ---------\n\n");
  run_instr_set(&instruction_set);
  printf("\n--------- Finished factorial ---------\n\n");
  clear_instr(&instruction_set);
  */
}
