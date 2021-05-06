A: proc_sim.c benchmarks.c
	gcc -o proc_sim proc_sim.c benchmarks.c ALU.c fetch_unit.c memory.c branch_unit.c
