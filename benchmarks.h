#ifndef benchmarker
#define benchmarker


struct INSTRUCTIONS
{
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
};

void generate(int i, struct INSTRUCTIONS *instruction_set);

void print_instuction(struct INSTRUCTIONS *instr_set, int i);

void clear_instr(struct INSTRUCTIONS *instr_set);

#endif
