#ifndef types
#define types

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

#define PRINT_INT 400
#define PRINT_CHAR_REG 401
#define PRINT_CHAR 402

#define HALT 500
#define NOOP 501

struct instruction
{
  int opcode;
  int operandres;
  int operand1;
  int operand2;
};

struct A_LOGIC
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

struct BRANCH_U
{
  struct instruction executinginstruction;
  int cycles_left;
  int out_result;
  int jump;
};

struct MEM_U
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
  int halted;
};

#endif
