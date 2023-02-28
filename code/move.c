#include "network.h"
#include "defs.h"
#include "main.h"
#include "sir.h"
#include "random.h"

void move_step(){

	int i, j, k, p, lowTAM, lowCity;

	for (i = 0; i < CITIES; i++){
		for (j = 0; j < i; j++){
			if (tabviz[i][j]){
				if(city[i].TAM < city[j].TAM) lowTAM = city[i].TAM;
				else									lowTAM = city[j].TAM;

				for (k = 0; k < lowTAM * theta; k++){
					
					p = genrand_int32()%city[i].TAM;
					
					if(p<city[i].S[0]){
						city[i].S[0]--;
						city[j].S[0]++;
					}else if(p<city[i].S[0]+city[i].I[0]){
						city[i].I[0]--;
						city[j].I[0]++;
					}else if(p<=city[i].S[0]+city[i].I[0]+city[i].R[0]){
						city[i].R[0]--;
						city[j].R[0]++;
					}
					
					p = genrand_int32()%city[j].TAM;
					
					if(p<city[j].S[0]){
						city[j].S[0]--;
						city[i].S[0]++;
					}else if(p<city[j].S[0]+city[j].I[0]){
						city[j].I[0]--;
						city[i].I[0]++;
					}else if(p<=city[j].S[0]+city[j].I[0]+city[j].R[0]){
						city[j].R[0]--;
						city[i].R[0]++;
					}
					
				}
			}
		}
	}
				
}
