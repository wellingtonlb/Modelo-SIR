#ifndef NETWORK_H

#define NETWORK_H

#include "defs.h"
#include <igraph.h>


#define NET_LINE_THREE	0
#define NET_TRIANGLE		1

enum{
	RER = 10,
	RSW,
	RSF,
	RBA,
	RRG
};

#define NET_INPUT		100

int networkformation();
void names();

extern char sznet[20][50];
extern char sznetnick[20][50];

/* global variables */
extern igraph_t 			graph;
extern igraph_matrix_t		A;
extern igraph_vector_int_t 	v;
extern igraph_vector_int_t 	c; // vetor de contador de vizinhos

extern igraph_real_t 		cc;
extern igraph_real_t 		spl;
extern igraph_real_t 		den;
extern igraph_real_t	 	diam;
extern igraph_real_t   	edge;
extern float					dg;
extern float 				group;

extern float mcc, mspl, mden, mdiam, mdg, mgrouppop, mmgrouppop, mgroupind, mmgroupind;
// coeficiente de clusterização, menor caminho, densidade, diametro, grau

extern int tabviz[CITIESMAX][CITIESMAX];

extern int inet;
extern float P;
extern int iP;
extern float Sec;
extern int iSec;

extern int ihStart;
extern int ihEnd;
extern float fhStart;
extern float fhEnd;

extern int iPStart;
extern int iPEnd;
extern float fiPhStart;
extern float fiPEnd;

extern int iSecStart;
extern int iSecEnd;
extern float fiSecStart;
extern float fiSecEnd;

extern int iNet;

#endif
