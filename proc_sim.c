#include <stdio.h>
#include "benchmarks.h"
#include "fetch_unit.h"
#include "types.h"
#include <unistd.h>


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
    case REL_JUMP:
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

int Execute(int opcode, int r, int s1, int s2, int *RF, int *MEM, struct FETCH_UNIT *fetcher, int *finished)
{
	int error = 0;
	switch(opcode)
	{


    //Arithmatic operations
		case ADD:
			RF[r] = RF[s1] + RF[s2]; break;
    case ADD_I:
      RF[r] = RF[s1] + s2; break;
		case MUL:
			RF[r] = RF[s1] * RF[s2]; break;
    case CMP:
      if (RF[s1] == RF[s2]){ RF[r] = 0; break;}
      else if (RF[s1] < RF[s2]){ RF[r] = -1; break;}
      else {RF[r] = 1; break;}

    //Bitwise operations
    case AND:
      RF[r] = RF[s1] & RF[s2]; break;
    case OR:
      RF[r] = RF[s1] | RF[s2]; break;
    case L_SHIFT:
      RF[r] = RF[s1] << RF[s2]; break;
    case R_SHIFT:
      RF[r] = RF[s1] >> RF[s2]; break;
    case NOT:
      RF[r] = ~RF[s1]; break;

    //Load/store operations
		case LOAD:
			RF[r] = MEM[ RF[s1] + RF[s2] ]; break;
    case LOAD_VALUE:
      RF[r] = s1;  break;
		case STORE:
			MEM[ RF[s1] + RF[s2] ] = RF[r]; break;
    case STORE_VALUE:
      MEM[ RF[s1] + RF[s2] ] = r; break;

    //Branchs and jumps
		case BRANCH_LT:
			if (RF[s1] < RF[s2]){ branch_pc(fetcher, r); break;}
      else {branch_pc(fetcher, (fetcher->PC) + 1); break;}
		case BRANCH_NOT_ZERO:
			if (RF[s1] != 0) {branch_pc(fetcher, r); break;}
      else {branch_pc(fetcher, (fetcher->PC) + 1); break;}
		case ABS_JUMP:
			branch_pc(fetcher, r); break;
    case REL_JUMP:
      branch_pc(fetcher, (fetcher->PC) + s1); break;

    //Print statements
    case PRINT_INT:
      printf("%d", RF[r]); break;
    case PRINT_CHAR_REG:
      printf("%c",(unsigned char)RF[r] & 0xFF); break;
    case PRINT_CHAR:
      printf("%c",(unsigned char)r & 0xFF); break;

    case NOOP:
      break;
		case HALT:
			*finished = 1; break;
		default:
			printf("Error: Opcode not recognised: %d", opcode); error = 1; break;
	}
	return error;
}

void run_instr_set(struct INSTRUCTIONS *instr_set){
  struct FETCH_UNIT fetch_u;
  struct instruction fetch_current;
  struct instruction decode_next;
  struct instruction decode_current;
  struct instruction execute_next;
  null_instr(&fetch_current);
  null_instr(&decode_next);
  null_instr(&decode_current);
  null_instr(&execute_next);
  load_instructs(&fetch_u, instr_set->INSTR_opcode, instr_set->INSTR_operandres, instr_set->INSTR_operand1, instr_set->INSTR_operand2);
  printf("set reloaded\n");
  int finished = 0;
  int cycles = 0;
  int instructions = 0;
  int RF[32] = {0};
  int MEM[1024] = {0};

  while (!finished) {
    //printf("%d    %d     %d\n",PC, RF[0],RF[1]);
    int opcode;
    int operandres;
    int operand1;
    int operand2;

    if (!get_waiting(&fetch_u) && !get_halt(&fetch_u)){
      instructions++;
		  Fetch(&fetch_current, &fetch_u);
    }
    else{
      null_instr(&fetch_current);
    }

    //printf("fetched instruction: %d\n" ,fetch_current.opcode);
    checkifhalt(&fetch_current, &fetch_u);
    checkifbranch(&fetch_current, &fetch_u);

    if (!get_waiting(&fetch_u) && !get_halt(&fetch_u)){
        increment_pc(&fetch_u);
    }

    decode_current = decode_next;
		Decode();
    //print_instr(&fetch_current);

		Execute(execute_next.opcode, execute_next.operandres, execute_next.operand1, execute_next.operand2, RF, MEM, &fetch_u, &finished);



    decode_next = fetch_current;
    execute_next = decode_current;


    cycles += 1;

	}
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

}
