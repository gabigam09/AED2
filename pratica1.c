#include <stdio.h>   // Biblioteca para entrada e saída de dados (printf)
#include <stdlib.h>  // Biblioteca para alocação de memória (malloc) e números aleatórios
#include <string.h>  // Biblioteca para manipulação de strings (se necessário)
#include <time.h>    // Biblioteca para medir o tempo (clock) e semente do rand

/* ---------------------------------------------------------
   1. ALGORITMOS DE ORDENAÇÃO
   --------------------------------------------------------- */

// --- INSERTION SORT (Ordenação por Inserção) ---
// Comentário: Funciona como organizar cartas. Pega um elemento e o move para trás
// até encontrar seu lugar correto. É eficiente para vetores pequenos ou quase ordenados.
void insertion(int *A, int n) {
    for (int i = 1; i < n; i++) {
        int chave = A[i]; // O elemento atual que será "encaixado"
        int j = i - 1;    // Começa comparando com o elemento à esquerda

        // Enquanto o elemento da esquerda for maior que a chave, "empurra" ele para a direita
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j]; // Deslocamento
            j--;             // Move para o próximo elemento à esquerda
        }
        A[j + 1] = chave; // Coloca a chave na posição correta encontrada
    }
}

// --- MERGE SORT (Ordenação por Intercalação) ---
// Comentário: Algoritmo "Dividir para Conquistar". Divide o vetor ao meio recursivamente
// e depois junta as partes de forma ordenada.

// Função auxiliar para intercalar (juntar) duas metades ordenadas
void merge_final(int *A, int esq, int meio, int dir) {
    int n1 = meio - esq + 1; // Tamanho da metade esquerda
    int n2 = dir - meio;      // Tamanho da metade direita

    // Aloca memória temporária para as duas metades
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copia os dados do vetor original para os temporários L e R
    for (int i = 0; i < n1; i++) L[i] = A[esq + i];
    for (int j = 0; j < n2; j++) R[j] = A[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    // Compara os elementos de L e R e devolve o menor para o vetor A
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    }

    // Copia elementos restantes de L ou R, se sobrarem
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
    
    free(L); free(R); // Libera a memória temporária usada na junção
}

// Função recursiva que subdivide o vetor
void merge_recursivo(int *A, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2; // Ponto central
        merge_recursivo(A, esq, meio);     // Divide lado esquerdo
        merge_recursivo(A, meio + 1, dir); // Divide lado direito
        merge_final(A, esq, meio, dir);    // Junta tudo ordenado
    }
}

// Interface solicitada pelo exercício
void mergesort2(int *A, int n) {
    merge_recursivo(A, 0, n - 1);
}

// --- QUICK SORT (Ordenação Rápida) ---
// Comentário: Escolhe um "pivô" e organiza o vetor: menores que o pivô à esquerda,
// maiores à direita.

// Função para trocar dois números de lugar
void trocar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Organiza o vetor em torno do pivô (último elemento neste caso)
int particionar(int *A, int baixo, int alto) {
    int pivo = A[alto]; // Pivô definido como o último elemento
    int i = (baixo - 1); // Índice do menor elemento

    for (int j = baixo; j <= alto - 1; j++) {
        if (A[j] < pivo) { // Se o elemento for menor que o pivô
            i++;           // Incrementa o índice do menor
            trocar(&A[i], &A[j]); // Troca os elementos de posição
        }
    }
    trocar(&A[i + 1], &A[alto]); // Coloca o pivô na posição central correta
    return (i + 1); // Retorna a posição do pivô
}

// Função recursiva do Quick Sort
void quick_recursivo(int *A, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(A, baixo, alto); // Ponto de partição
        quick_recursivo(A, baixo, pi - 1);    // Ordena lado esquerdo
        quick_recursivo(A, pi + 1, alto);     // Ordena lado direito
    }
}

// Interface solicitada pelo exercício
void quicksort(int *A, int n) {
    quick_recursivo(A, 0, n - 1);
}

/* ---------------------------------------------------------
   2. GERADORES DE VETORES E MEDIÇÃO DE TEMPO
   --------------------------------------------------------- */

// Preenche o vetor com números aleatórios entre 0 e 99.999
void fill_random(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 100000;
}

// Preenche o vetor em ordem crescente (0, 1, 2, 3...)
void fill_ascending(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

// Preenche o vetor em ordem decrescente (n, n-1, n-2...)
void fill_descending(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = n - i;
}

// Função que calcula o tempo de execução usando a biblioteca time.h
double get_time(void (*sort_func)(int*, int), int *A, int n) {
    clock_t start = clock(); // Captura o tempo inicial do processador
    sort_func(A, n);         // Executa o algoritmo de ordenação passado como parâmetro
    clock_t end = clock();   // Captura o tempo final
    return (double)(end - start) / CLOCKS_PER_SEC; // Retorna a diferença em segundos
}

/* ---------------------------------------------------------
   3. BLOCO PRINCIPAL (EXECUÇÃO E TESTES)
   --------------------------------------------------------- */

int main() {
    srand(time(NULL)); // Inicializa a semente para gerar números aleatórios reais

    // Define os tamanhos dos vetores para testar e plotar o gráfico (Instância vs Tempo)
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000};
    int num_tamanhos = 5; // Quantidade de testes de tamanho diferente

    // Imprime cabeçalho formatado para CSV (facilita importar no Excel/Sheets)
    printf("N;Algoritmo;Caso;Tempo(s)\n");

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i]; // Pega o tamanho atual da rodada
        int *A = (int *)malloc(n * sizeof(int)); // Aloca o vetor dinamicamente

        // Listas auxiliares para automatizar o teste dos 3 algoritmos
        void (*algoritmos[])(int*, int) = {insertion, mergesort2, quicksort};
        char *nomes_alg[] = {"Insertion", "MergeSort", "QuickSort"};

        // Loop para testar cada um dos 3 algoritmos
        for (int j = 0; j < 3; j++) {
            
            // --- TESTE ALEATÓRIO ---
            fill_random(A, n); 
            printf("%d;%s;Aleatorio;%f\n", n, nomes_alg[j], get_time(algoritmos[j], A, n));

            // --- TESTE CRESCENTE ---
            fill_ascending(A, n);
            printf("%d;%s;Crescente;%f\n", n, nomes_alg[j], get_time(algoritmos[j], A, n));

            // --- TESTE DECRESCENTE ---
            fill_descending(A, n);
            printf("%d;%s;Decrescente;%f\n", n, nomes_alg[j], get_time(algoritmos[j], A, n));
        }
        free(A); // Libera a memória do vetor antes da próxima rodada de tamanho n
    }

    return 0; // Fim do programa
}
