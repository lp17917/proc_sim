int main() {

	int finished = 0;
	int cycles = 0;
	int instructions = 0
	int PC = 0;

	int RF[32];
	int MEM[1024];
	int INSTR[512];

	while (!finished) {
		Fetch();
		Decode();
		Execute();
		instructions++;
		cycles += 3;
	}
}


int fetch(){
  return 0;
}

int Execute(int opcode, int r, int s1, int s2, int *RF, int* MEM, int *PC, int target_addr, int *finished)
{
	int error = 0;
	switch(opcode)
	{
		case ADD:
			RF[r] = RF[s1] + RF[s2]; *PC++; break;
		case MUL:
			RF[r] = RF[s1] * RF[s2]; *PC++; break;
		case LOAD:
			RF[r] = MEM[ RF[s1] + RF[s2] ]; *PC++; break;
		case STORE:
			MEM[ RF[s1] + RF[s2] ] = RF[r]; *PC++; break;
		case BRANCH_LT:
			if (RF[s1] < RF[s2]) *PC = target_addr; break;
		case BRANCH_NOT_ZERO:
			if (s1 != 0) *PC = target_addr; break;
		case UNCONDITIONAL_JUMP:
			*PC = target_addr; break;
		case HALT:
			*finished = 1; break;
		default:
			printf("Error: Opcode not recognised: %d", opcode); error = 1; break;
	}
	return error;
}
