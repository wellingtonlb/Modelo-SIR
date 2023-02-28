#include "network.h"
#include "main.h"
#include "defs.h"

char sznet[20][50];
char sznetnick[20][50];

igraph_t 			graph;
igraph_matrix_t 	A;
igraph_vector_int_t 	v;
igraph_vector_int_t 	c; // vetor de contador de vizinhos

igraph_real_t 		cc;
igraph_real_t 		spl;
igraph_real_t 		den;
igraph_real_t	 	diam;
igraph_real_t   	edge;
float					dg;
float 				group;

float mcc, mspl, mden, mdiam, mdg, mgrouppop, mmgrouppop, mgroupind, mmgroupind;

int tabviz[CITIESMAX][CITIESMAX]; 

int inet;
float P;
int iP;
float Sec;
int iSec;

int ihStart;
int ihEnd;
float fhStart;
float fhEnd;

int iPStart;
int iPEnd;
float fiPhStart;
float fiPEnd;

int iSecStart;
int iSecEnd;
float fiSecStart;
float fiSecEnd;

int iNet;

int networkformation(){
	
#ifdef _DEBUG_
	printf("[NETWORK-networkformation]\n");
	printf("[NETWORK-networkformation]iNet = %d\n", iNet);
#endif

	int i, j, k, z;

	for(i=0;i<CITIES;i++)
		for(j=0;j<CITIES;j++)
			tabviz[i][j] = 0;

	//network formation
	//line-3
	if(iNet == 0){
		CITIES = 3;
		
		igraph_vector_int_init(&v, 2);
		VECTOR(v)[0]=0; VECTOR(v)[1]=1; 

		igraph_create(&graph, &v, CITIES, 0);

		VECTOR(v)[0]=1;
		VECTOR(v)[1]=2;
		igraph_add_edges(&graph, &v, 0);
		
		
	}

	//triangle
	if(iNet == 1){
		CITIES = 3;
		igraph_full(&graph, CITIES, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
	}

	//complete-4
	if(iNet == 2){
		CITIES = 4;
		igraph_full(&graph, CITIES, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
	}

	//circle-4
	if(iNet == 3){
		CITIES=4;
		
		igraph_vector_int_init(&v, 2);

		VECTOR(v)[0]=0;
		VECTOR(v)[1]=1;
		igraph_create(&graph, &v, CITIES, 0);

		VECTOR(v)[0]=1;
		VECTOR(v)[1]=3;
		igraph_add_edges(&graph, &v, 0);

		VECTOR(v)[0]=3;
		VECTOR(v)[1]=2;
		igraph_add_edges(&graph, &v, 0);

		VECTOR(v)[0]=2;
		VECTOR(v)[1]=0;
		igraph_add_edges(&graph, &v, 0);
		
	}

	if(iNet == 4){
		igraph_full(&graph, CITIES, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
	}

	if(iNet==RER)
		igraph_erdos_renyi_game(&graph, IGRAPH_ERDOS_RENYI_GNP, CITIES, P, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);

	if(iNet==RSW)
		igraph_watts_strogatz_game(&graph, 1, CITIES, iSec, P, IGRAPH_NO_LOOPS, IGRAPH_NO_MULTIPLE);

	if(iNet==RSF){
		edge = (igraph_integer_t)(P*CITIES*(CITIES-1)/2);
		igraph_static_power_law_game(&graph, CITIES, edge, Sec, -1, IGRAPH_NO_LOOPS, IGRAPH_NO_MULTIPLE, 0);
	}

	if(iNet==RBA){
		igraph_barabasi_game(&graph, CITIES, Sec, iP, NULL, 0, 1, IGRAPH_UNDIRECTED, IGRAPH_BARABASI_PSUMTREE, NULL);
	}

	if(iNet==RRG){
		igraph_k_regular_game(&graph, CITIES, iSec, IGRAPH_UNDIRECTED, IGRAPH_NO_MULTIPLE);
	}
	
	if(iNet==NET_INPUT){
		
#ifdef _DEBUG_
	printf("[NETWORK-networkformation] CITIES = %d\n", CITIES);
	for (i=0;i<CITIES;i++){
   	for (j=0;j<CITIES;j++){
   		printf("%d ", tempviz[i][j]);
   	}
   	printf("\n");
   }
#endif

		igraph_vector_int_init(&v, 2);
		
		k=0;
		for(i=0;i<CITIES;i++){
			for(j=0;j<i;j++){
				if(tempviz[i][j] == 1){
					VECTOR(v)[0]=i;
					VECTOR(v)[1]=j;
					if(!k){
						igraph_create(&graph, &v, CITIES, 0);
						k++;
					}else{
						igraph_add_edges(&graph, &v, 0);
						k++;
					}
				}
			}
		}
		
	}

	igraph_vector_int_init(&v, CITIES); 
	igraph_vector_int_init(&c, CITIES);
	igraph_neighborhood_size(&graph, &c, igraph_vss_all(), 1, IGRAPH_ALL, 0);/*Neighborhood of graph vertices*/
	
	igraph_matrix_init(&A, (long int)CITIES, (long int)CITIES);
	igraph_get_adjacency(&graph, &A, IGRAPH_GET_ADJACENCY_BOTH, NULL, 0);

	//o código abaixo coloca como vizinho o nó e os vizinhos do nó
	for (i = 0; i < CITIES; i++){
		for (j = 0; j < CITIES; j++){
			tabviz[i][j] = (int)igraph_matrix_get(&A, i, j);
		}
	}
	
#ifdef _DEBUG_
	printf("[NETWORK-networkformation] tabviz\n");

	for(i=0;i<CITIES;i++){
		for(j=0;j<CITIES;j++){
			printf("%d ", tabviz[i][j]);
		}
		printf("\n");
	}
	//getchar();
#endif

   igraph_transitivity_undirected(&graph, &cc,IGRAPH_TRANSITIVITY_ZERO);
   igraph_average_path_length(&graph, &spl, NULL, IGRAPH_UNDIRECTED, 1);/*Shortest (directed or undirected) paths between vertices*/
   igraph_density(&graph, &den, 0);
   igraph_diameter(&graph, &diam, NULL, NULL, NULL, NULL, IGRAPH_UNDIRECTED, 0);

   return 0;

	//printf("\nCC: %f\nSPL: %f\nDEN: %f\nDIAM: %d\n",cc,spl,den,diam);

}

