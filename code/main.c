#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defs.h"
#include "random.h"
#include "sir.h"
#include "db.h"
#include "network.h"
#include "move.h"

void initialization();
void parseArgs( int qtde, char **args ); 
void loadinfo(char *buffer, char *folder);
void loadcities();

int CITIES;
float theta;

int floadcities = 0;

int tempviz[CITIESMAX][CITIESMAX];

int main(int argc, char *argv[]) {
	
	int it;
	
	initialization();	
	
	loadinfo("../data.ini", filefolder);
	
	iNet = 3;
   param_iniI = 0.05;
   param_a = 0.001;
	param_b = (float)1/(float)14;
	param_c = 0.005;
	param_e = (float)1/(float)(365*78);
	
	theta = 0.05;

	parseArgs(argc, argv);
	
	if(floadcities) loadcities();
		
	networkformation();
		
	db_init();
	sir_init();
	db_step();
	
	for(it=0;it<ITER;it++){
		move_step();
		sir_step();
		//move_step();
		db_step();
	}
	
	db_end();
	
	
	
	return 0;
}

void initialization(){
	
	struct timespec ts;
	
	clock_gettime(0, &ts);

	srand((time_t)ts.tv_nsec);
	init_genrand(rand());
	
}

void loadinfo(char *buffer, char *folder){

   FILE *fp;

   fp=fopen(buffer,"r");
   if(fp==NULL) printf("\nError opening the file");
   fscanf(fp,"\nresultfolder=%s\n",folder);

}

void parseArgs(int qtde, char **args )
{
	int c;
	
	for( c = 0; c < qtde; c++ ){
		if( !(strcmp( *(args+c), "--a" ) ) ){
			param_a = atof(*(args + ++c));
		} 
		else if( !(strcmp( *(args+c), "--b" ) ) ){
			param_b = atof(*(args + ++c));
		} 
		else if( !(strcmp( *(args+c), "--c" ) ) ){
			param_c = atof(*(args + ++c));
		}
		else if( !(strcmp( *(args+c), "--e" ) ) ){
			param_e = atof(*(args + ++c));
		}
		else if( !(strcmp( *(args+c), "--INII" ) ) ){
			param_iniI = atof(*(args + ++c));
		}
		else if( !(strcmp( *(args+c), "--loadcities" ) ) ){
			floadcities = 1;
			iNet = NET_INPUT;
		}


	}
}

void loadnet(char *buffer){

	int i, j;
	
   FILE *fp;
   


}

void loadcities(char *buffer){
	
	int i, j;
	
   FILE *fp;
   
   for (i=0;i<CITIESMAX;i++){
   	for (j=0;j<CITIESMAX;j++){
   		tempviz[i][j] = 0;
   	}
   }
  	
   fp=fopen("../../conexoes.txt","r");
   if(fp==NULL) printf("\nError opening the file");
   
   while (fscanf(fp,"\n%d-%d\n",&i,&j) != EOF){
    	//printf("%d-%d\n",i,j);
   	tempviz[i-1][j-1] = 1;
   	tempviz[j-1][i-1] = 1;
   }
   
   /*for (i=0;i<CITIESMAX;i++){
   	for (j=0;j<CITIESMAX;j++){
   		printf("%d ", tempviz[i][j]);
   	}
   	printf("\n");
   }
   getchar();*/

   fp=fopen("../../populacao.txt","r");
   if(fp==NULL) printf("\nError opening the file");
   
   while (fscanf(fp,"\n%d: %d\n",&i,&j) != EOF){
    	//printf("%d: %d\n",i,j);
    	city[i-1].TAM = j;
   }
   
   CITIES = i;

}
