#ifndef fetch_unit
#define fetch_unit


struct FETCH_UNIT
{
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
  int PC;
  int waiting;
};

struct instruction
{
  int opcode;
  int operandres;
  int operand1;
  int operand2;
};

void load_instructs(struct FETCH_UNIT *fetcher, int *INSTR_opcode, int *INSTR_operandres, int *INSTR_operand1, int *INSTR_operand2);

int Fetch(struct instruction *instr, struct FETCH_UNIT *fetcher);

void increment_pc(struct FETCH_UNIT *fetcher);

void branch_pc(struct FETCH_UNIT *fetcher, int location);

int get_waiting(struct FETCH_UNIT *fetcher);

void set_waiting(struct FETCH_UNIT *fetcher, int wait);

#endif
