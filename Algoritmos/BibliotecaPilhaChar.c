#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxPilha 10
#define sinal 0
#define ghost 36

typedef struct{
int topo;
unsigned char Vetor[MaxPilha];
}PilhaCh;


PilhaCh criarPilha( ){
    PilhaCh P;
    P.topo = sinal;
    P.Vetor[0] = MaxPilha - 1;
    return P;
}

bool PilhaVazia(PilhaCh P){
    bool estado;
    if(P.topo == sinal){
        estado = true;
    }else{
        estado = false;
    }
    return estado;
}

unsigned char acessarPilha(PilhaCh P){

    unsigned char item;
    item = P.Vetor[P.topo];
    return item;
}

PilhaCh pushPilha(PilhaCh P,unsigned char item){

    if(P.topo < MaxPilha - 1){
        P.topo++;
        P.Vetor[P.topo] = item;
    }

    return P;
}

PilhaCh popPilha(PilhaCh P){
    if(P.topo > sinal){
        P.topo--;
    }
    return P;
}

PilhaCh esvaziarPilha(PilhaCh P){
    if(P.topo > sinal){
        P.topo = sinal;
    }
    return P;
}

int obterProfundidade(PilhaCh P){
    int item;
    item = P.topo;

    return item;
}

 void mostrarPilha(PilhaCh P){
     if(P.topo > sinal){

        for(int i = P.topo; i > sinal; i--){
                printf("%i", P.Vetor[i]);
        }

     }

 }


int main(){
    PilhaCh P = criarPilha();
}
