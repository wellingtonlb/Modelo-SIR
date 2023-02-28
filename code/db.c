#include "db.h"
#include "main.h"
#include<stdio.h>

char filefolder[256];
char filename[512];

FILE *fresult;

int DADOS = 7; //update if more things are written to the file

void db_init(){
	
	int i, j;
	
	for(i=0;;i++){
		sprintf(filename, "%sSIR-CITY-edd_SIM_%04d.csv", filefolder, i);
	   fresult = fopen (filename, "r");
	   if (fresult!=NULL){
	   	fclose (fresult);
	   }else break;
	}
	
	fresult = fopen(filename, "w");
	
	for(i=0;i<CITIES;i++){
		fprintf(fresult, "CITY %d;", i);
		for(j=0;j<DADOS-1;j++){
			fprintf(fresult, ";");
		}
	}
	
	fprintf(fresult, "\n");
	
	for(i=0;i<CITIES;i++){
		fprintf(fresult, "S;I;R;S->I;I->R;I->S;R->S;");
	}
	
	fprintf(fresult, "\n");
	
	return;
}

void db_step(){

	int c;

	for(c=0;c<CITIES;c++){
	   fprintf(fresult, "%d;%d;%d;%d;%d;%d;%d;", 
							  city[c].S[0],city[c].I[0],city[c].R[0],city[c].dsi,city[c].dir,city[c].dis,city[c].drs);
	}
	
	fprintf(fresult, "\n");
	
}

void db_end(){
	
   fprintf(fresult, "Parameters;\n");
   fprintf(fresult, "ITER;%d\n", ITER);
   fprintf(fresult, "a;%f\n", param_a);
   fprintf(fresult, "b;%f\n", param_b);
   fprintf(fresult, "c;%f\n", param_c);
   fprintf(fresult, "e;%f\n", param_e);
   fclose(fresult);
   
}

