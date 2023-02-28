#ifndef _SIR_H_
#define _SIR_H_

#include "defs.h"

extern float param_iniI;
extern float param_a;
extern float param_b;
extern float param_c;
extern float param_e;

struct c{
	int S[2], I[2], R[2];
   int dsi, dir, dis, drs;
   int TAM;
};

extern struct c city[CITIESMAX];

void sir_init();
void sir_step();

#endif
