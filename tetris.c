#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

typedef struct {
    char nome;  // 'I', 'O', 'T', 'L'
    int id;
} Peca;

typedef struct {
    Peca fila[TAM];
    int inicio;
    int fim;
    int qtd;
} Fila;

// -------------------- GERAR PEÇA --------------------
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = rand() % 1000; // identificador simples
    return p;
}

// -------------------- INICIALIZAR FILA --------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    for(int i = 0; i < TAM; i++) {
        f->fila[i] = gerarPeca();
        f->fim = (f->fim + 1) % TAM;
        f->qtd++;
    }
}

// -------------------- ENQUEUE --------------------
void inserir(Fila *f) {
    if(f->qtd == TAM) {
        printf("Fila cheia! (mas como é fixa, sobrescrevemos o final)\n");
    }

    f->fila[f->fim] = gerarPeca();
    f->fim = (f->fim + 1) % TAM;

    if(f->qtd < TAM)
        f->qtd++;
    else
        f->inicio = (f->inicio + 1) % TAM; // sobrescrita circular
}

// -------------------- DEQUEUE --------------------
void removerPeca(Fila *f) {
    if(f->qtd == 0) {
        printf("Fila vazia, não há peça para jogar.\n");
        return;
    }

    printf("Peça jogada: %c (id %d)\n",
           f->fila[f->inicio].nome,
           f->fila[f->inicio].id);

    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
}

// -------------------- MOSTRAR FILA --------------------
void mostrarFila(Fila *f) {
    if(f->qtd == 0) {
        printf("Fila vazia.\n");
        return;
    }

    printf("\n=== Estado atual da fila ===\n");
    int idx = f->inicio;
    for(int i = 0; i < f->qtd; i++) {
        printf("[%d] Peça: %c | id: %d\n", i, f->fila[idx].nome, f->fila[idx].id);
        idx = (idx + 1) % TAM;
    }
    printf("=============================\n");
}

// -------------------- MAIN --------------------
int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Jogar peça (dequeue)\n");
        printf("2. Inserir nova peça (enqueue)\n");
        printf("3. Mostrar fila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                removerPeca(&fila);
                mostrarFila(&fila);
                break;
            case 2:
                inserir(&fila);
                mostrarFila(&fila);
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while(op != 0);

    return 0;
}
