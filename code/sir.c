

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "string.h"
#include "random.h"
#include "defs.h"
#include "sir.h"
#include "main.h"



FILE *fresult;

float param_iniI;
float param_a;
float param_b;
float param_c;
float param_e;

struct c city[CITIESMAX];

void sir_init(){
	
	int i, p;
	
	//p = genrand_int32()%CITIES;
	p=0;
	
	for(i=0;i<CITIES;i++){
		if(!floadcities) city[i].TAM = 10000;
		if(i==p){
			city[i].S[0] = city[i].TAM-city[i].TAM*param_iniI;
			city[i].I[0] = city[i].TAM*param_iniI;
		}else{
			city[i].S[0] = city[i].TAM;
			city[i].I[0] = 0;
		}
		city[i].R[0] = 0;
		city[i].dsi=0; city[i].dir=0; city[i].dis=0; city[i].drs=0;
	}
	
}

void sir_step(){
	
	int i;
	
	for(i=0;i<CITIES;i++){
	   city[i].dsi = (int)(param_a*(float)city[i].S[0]*(float)city[i].I[0]);
	   city[i].dir = (int)(param_b*(float)city[i].I[0]);
	   city[i].dis = (int)(param_c*(float)city[i].I[0]);
	   city[i].drs = (int)(param_e*(float)city[i].R[0]);
	
		city[i].S[1] = city[i].S[0] - city[i].dsi + city[i].dis + city[i].drs;
		city[i].I[1] = city[i].I[0] + city[i].dsi - city[i].dir - city[i].dis;
		city[i].R[1] = city[i].R[0] + city[i].dir - city[i].drs;
		
		city[i].S[0] = city[i].S[1];
		city[i].I[0] = city[i].I[1];
		city[i].R[0] = city[i].R[1];
		
	}
	
}

 


