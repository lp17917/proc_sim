#include <stdio.h>


#define ADD 0
#define ADD_I 1
#define MUL 2
#define CMP 3

#define AND 100
#define OR 101
#define L_SHIFT 102
#define R_SHIFT 103
#define NOT 104

#define LOAD 200
#define LOAD_VALUE 201
#define STORE 202
#define STORE_VALUE 203

#define BRANCH_LT 300
#define BRANCH_NOT_ZERO 301
#define ABS_JUMP 302
#define REL_JUMP 303

#define PRINT_INT 400
#define PRINT_CHAR_REG 401
#define PRINT_CHAR 402

#define HALT 500


int Fetch(int *opcode, int *operandres, int *operand1, int *operand2, int *INSTR_opcode, int *INSTR_operandres, int *INSTR_operand1, int *INSTR_operand2, int PC)
{
  *opcode = INSTR_opcode[PC];
  *operandres = INSTR_operandres[PC];
  *operand1 = INSTR_operand1[PC];
  *operand2 = INSTR_operand2[PC];
  return 0;
}

int Decode(){
  return 0;
}

int Execute(int opcode, int r, int s1, int s2, int *RF, int *MEM, int *PC, int target_addr, int *finished)
{
	int error = 0;
	switch(opcode)
	{
    //instructions to ADD
    //multiply w/ overflow

    //Arithmatic operations
		case ADD:
			RF[r] = RF[s1] + RF[s2]; *PC++; break;
    case ADD_I:
      RF[r] = RF[s1] + s2; *PC++; break;
		case MUL:
			RF[r] = RF[s1] * RF[s2]; *PC++; break;
    case CMP:
      if (RF[s1] == RF[s2]){ RF[r] = 0; *PC++; break;}
      else if (RF[s1] < RF[s2]){ RF[r] = -1; *PC++; break;}
      else {RF[r] = 1; *PC++; break;}

    //Bitwise operations
    case AND:
      RF[r] = RF[s1] & RF[s2]; *PC++; break;
    case OR:
      RF[r] = RF[s1] | RF[s2]; *PC++; break;
    case L_SHIFT:
      RF[r] = RF[s1] << RF[s2]; *PC++; break;
    case R_SHIFT:
      RF[r] = RF[s1] >> RF[s2]; *PC++; break;
    case NOT:
      RF[r] = ~RF[s1]; *PC++; break;

    //Load/store operations
		case LOAD:
			RF[r] = MEM[ RF[s1] + RF[s2] ]; *PC++; break;
    case LOAD_VALUE:
      RF[r] = s1; *PC++; break;
		case STORE:
			MEM[ RF[s1] + RF[s2] ] = RF[r]; *PC++; break;
    case STORE_VALUE:
      MEM[ RF[s1] + RF[s2] ] = r; *PC++; break;

    //Branchs and jumps
		case BRANCH_LT:
			if (RF[s1] < RF[s2]){ *PC = r; break;}
      else {*PC++; break;}
		case BRANCH_NOT_ZERO:
			if (s1 != 0) {*PC = r; break;}
      else {*PC++; break;}
		case ABS_JUMP:
			*PC = r; break;
    case REL_JUMP:
        *PC += s1; break;

    //Print statements
    case PRINT_INT:
      printf("%d ", RF[r]); *PC++; break;
    case PRINT_CHAR_REG:
      printf("%c",(unsigned char)RF[r] & 0xFF); *PC++; break;
    case PRINT_CHAR:
      printf("%c",(unsigned char)r & 0xFF); *PC++; break;

		case HALT:
			*finished = 1; break;
		default:
			printf("Error: Opcode not recognised: %d", opcode); error = 1; break;
	}
	return error;
}

int main() {

	int finished = 0;
	int cycles = 0;
	int instructions = 0;
	int PC = 0;

	int RF[32];
	int MEM[1024];
	int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];


	while (!finished) {
    int opcode;
    int operandres;
    int operand1;
    int operand2;
		Fetch(&opcode, &operandres, &operand1, &operand2, INSTR_opcode, INSTR_operandres, INSTR_operand1, INSTR_operand2 , PC);
    cycles += 1;
		Decode();
    cycles += 1;
		Execute(opcode, operandres, operand1, operand2, RF, MEM, &PC, 0, &finished);
    cycles += 1;
		instructions++;

	}
}
