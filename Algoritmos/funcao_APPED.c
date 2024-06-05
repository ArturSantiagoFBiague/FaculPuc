/* Atividade Python
Arquivo:   artur_santiago_AtPYTHON.c
Autor:     artur santiago,
Date:      26/04/24 11:42
Descrição: fazer comportamento da Funçao append()
*/


#define Max 20
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int tamanho;
    int Vetor[Max];
} Lista;


Lista criarLista(){
    Lista A;
    A.tamanho = 0;
    return A;
    printf("lista Criado com sucesso");
}

Lista mostrarLista(Lista L){
    int tam = L.tamanho;
    if(tam == 0){

        printf("Lista Vazia");

    }else{

    printf("\n");
    for(int i=0;i<tam;i++){

        printf("%i ", L.Vetor[i]);
    }

    printf("\n");

    }
    return L;
}

Lista append(Lista L, int y) {

    unsigned int tam;
    tam = L.tamanho;
    L.Vetor[tam] = y;
    tam+=1;
    L.tamanho = tam;
    return L;

}

int main() {

    Lista H;

    H = criarLista();
    H = append(H, 2);
    H = append(H, 3);
    H = append(H, 3);
    H = append(H, 3);
    H = append(H, 3);

    mostrarLista(H);

    return 0;
}
