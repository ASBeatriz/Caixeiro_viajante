/* -------------- TAD lista encadeada -------------- */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura do nó da lista de adjacência
typedef struct adjacencia {
    int cidade;            // Índice da cidade adjacente
    int distancia;         // Distância para a cidade adjacente
    struct adjacencia *prox; // Próximo nó na lista
} Adjacencia;

// Estrutura para a lista de adjacências
typedef struct {
    Adjacencia *inicio;    // Ponteiro para o início da lista de adjacências
} Lista;

// Função para criar um nó de adjacência
Adjacencia* cria_adjacencia(int cidade, int distancia) {
    Adjacencia *nova = (Adjacencia*)malloc(sizeof(Adjacencia));
    nova->cidade = cidade;
    nova->distancia = distancia;
    nova->prox = NULL;
    return nova;
}

// Função para inserir uma adjacência na lista de uma cidade
void insere_adjacencia(Lista *lista, int cidade, int distancia) {
    Adjacencia *nova = cria_adjacencia(cidade, distancia);
    nova->prox = lista->inicio;
    lista->inicio = nova;
}

// Função para liberar a memória de uma lista de adjacências
void libera_lista(Lista *lista) {
    Adjacencia *atual = lista->inicio;
    while (atual != NULL) {
        Adjacencia *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

/* ----------------- Gerar as Permutações ---------------- */

// Função que calcula a distância de um caminho dado
int calcula_distancia(Lista *listaCidades[], int *permutacao, int n) {
    int distancia_total = 0;

    // Percorre todas as cidades da permutação
    for (int i = 0; i < n - 1; i++) {
        int cidade_atual = permutacao[i];
        int proxima_cidade = permutacao[i + 1];
        
        // Busca a distância entre cidade_atual e proxima_cidade na lista de adjacências
        Adjacencia *adj = listaCidades[cidade_atual]->inicio;
        int distancia_encontrada = 0;
        while (adj != NULL) {
            if (adj->cidade == proxima_cidade) {
                distancia_total += adj->distancia;
                distancia_encontrada = 1;
                break;
            }
            adj = adj->prox;
        }
        
        if (!distancia_encontrada) return INT_MAX; // Se não encontrar caminho, distância é infinita
    }

    // Volta para a cidade inicial
    int ultima_cidade = permutacao[n - 1];
    int primeira_cidade = permutacao[0];
    Adjacencia *adj = listaCidades[ultima_cidade]->inicio;
    int distancia_encontrada = 0;
    while (adj != NULL) {
        if (adj->cidade == primeira_cidade) {
            distancia_total += adj->distancia;
            distancia_encontrada = 1;
            break;
        }
        adj = adj->prox;
    }
    
    if (!distancia_encontrada) return INT_MAX; // Se não encontrar caminho, distância é infinita
    return distancia_total;
}

// Função que troca dois elementos de um array
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função que gera todas as permutações usando backtracking
void permutacao(Lista *listaCidades[], int *cidades, int l, int r, int n, int *melhor_caminho, int *menor_distancia) {
    if (l == r) {
        // Calcula a distância total para a permutação atual
        int distancia_atual = calcula_distancia(listaCidades, cidades, n);
        if (distancia_atual < *menor_distancia) {
            *menor_distancia = distancia_atual;
            for (int i = 0; i < n; i++) {
                melhor_caminho[i] = cidades[i];
            }
        }
    } else {
        for (int i = l; i <= r; i++) {
            troca(&cidades[l], &cidades[i]);
            permutacao(listaCidades, cidades, l + 1, r, n, melhor_caminho, menor_distancia);
            troca(&cidades[l], &cidades[i]); // Backtrack
        }
    }
}

/* ------------------ Main -------------------*/

int main() {
    int n = 4; // Número de cidades
    Lista *listaCidades[n];

    // Inicializa as listas
    for (int i = 0; i < n; i++) {
        listaCidades[i] = (Lista*)malloc(sizeof(Lista));
        listaCidades[i]->inicio = NULL;
    }

    // Insere as adjacências para cada cidade
    insere_adjacencia(listaCidades[0], 1, 10); // Cidade 0 -> Cidade 1, distância 10
    insere_adjacencia(listaCidades[0], 2, 15); // Cidade 0 -> Cidade 2, distância 15
    insere_adjacencia(listaCidades[0], 3, 20); // Cidade 0 -> Cidade 3, distância 20

    insere_adjacencia(listaCidades[1], 0, 10); // Cidade 1 -> Cidade 0, distância 10
    insere_adjacencia(listaCidades[1], 2, 35); // Cidade 1 -> Cidade 2, distância 35
    insere_adjacencia(listaCidades[1], 3, 25); // Cidade 1 -> Cidade 3, distância 25

    insere_adjacencia(listaCidades[2], 0, 15); // Cidade 2 -> Cidade 0, distância 15
    insere_adjacencia(listaCidades[2], 1, 35); // Cidade 2 -> Cidade 1, distância 35
    insere_adjacencia(listaCidades[2], 3, 30); // Cidade 2 -> Cidade 3, distância 30

    insere_adjacencia(listaCidades[3], 0, 20); // Cidade 3 -> Cidade 0, distância 20
    insere_adjacencia(listaCidades[3], 1, 25); // Cidade 3 -> Cidade 1, distância 25
    insere_adjacencia(listaCidades[3], 2, 30); // Cidade 3 -> Cidade 2, distância 30

    // Array de cidades
    int cidades[] = {0, 1, 2, 3};
    int melhor_caminho[n];
    int menor_distancia = INT_MAX;

    // Gera permutações e encontra o menor caminho
    permutacao(listaCidades, cidades, 0, n - 1, n, melhor_caminho, &menor_distancia);

    // Exibe o menor caminho e a menor distância
    printf("Menor distância: %d\n", menor_distancia);
    printf("Melhor caminho: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", melhor_caminho[i]);
    }
    printf("\n");

    // Libera a memória alocada
    for (int i = 0; i < n; i++) {
        libera_lista(listaCidades[i]);
        free(listaCidades[i]);
    }

    return 0;
}
