#include <stdio.h>
#include <string.h>

//função auxiliar para trocar dois caracteres de lugar
void troca(char str[], int pos1, int pos2){
    char aux = str[pos1];
    str[pos1] = str[pos2];
    str[pos2] = aux;
}

// função recursiva para testar todas as permutações da string
void permutacao(char str[], int esq, int dir){
    //caso trivial
    if(dir == esq) {
        printf("%s\n", str);
    }
    else{
        for(int p = esq; p <= dir; p++){
            troca(str, p, esq);
            permutacao(str, esq+1, dir);
            troca(str, p, esq); //troca novamente para não afetar as próx alterações
        }
    }
}

int main(){
    char string[] = "ABC";
    int n = 3;
    permutacao(string, 0, n-1);
}