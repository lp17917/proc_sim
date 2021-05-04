#ifndef types
#define types

struct instruction
{
  int opcode;
  int operandres;
  int operand1;
  int operand2;
};

struct ALU
{
  struct instruction executinginstruction;
  int cycles_left;
  int out_reg;
  int out_result;

};

struct INSTRUCTIONS
{
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
};


struct MEMORY
{
  int MEM[2048];
  struct instruction executinginstruction;
  int cycles_left;
  int out_reg;
  int out_result;
};

struct FETCH_UNIT
{
  int INSTR_opcode[512];
  int INSTR_operandres[512];
  int INSTR_operand1[512];
  int INSTR_operand2[512];
  int PC;
  int waiting;
};

#endif
