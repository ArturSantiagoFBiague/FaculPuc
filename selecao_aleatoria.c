#include <stdio.h>     
#include <stdlib.h>  
#include <time.h>

int main(){
	int n, m, p, u, g, rd, aux;
	int lista[5]= {1,2,3,4,5};
	
	srand((int) time(NULL)); //semente
 
	p = 1; 	m = 5; u = m; n=m; 
	
	for( n=m; n>=0; n--){
		//Numero Aleatorio Gerado
		rd= rand();
		g = p+rd%(u-p+1);
		//Troca de Posição
		aux = lista[g];
		lista[g] = lista[n];
		lista[n] = aux;	
	}
	
	for( n=0; n<m; n++){
		printf(" %d", lista[n]);
	}
	
	return 0;  
}