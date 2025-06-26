#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    char nome_comp[81];
    int numMatric;
    float p1, p2, p3;
}Aluno;

typedef struct lista{
    char nome[81];
    float media;
    struct lista* prox;
}Lista;

Aluno* leia_arquivo(char* nome_arquivo, int* pn) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        exit(1);
    }fscanf(arq, "%d\n", pn);

    Aluno* novoAluno = (Aluno*)malloc((*pn) * sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("ERRO!\n");
        exit(1);
    }
    else {
        for (int i = 0;i < *pn;i++) {
            fscanf(arq, " %[^:]: %d %f %f %f", novoAluno[i].nome_comp, &novoAluno[i].numMatric, &novoAluno[i].p1, &novoAluno[i].p2, &novoAluno[i].p3);
        }
    }fclose(arq);
    return novoAluno;
}

void salva_binario(int n, Aluno* vet, char* nome_arquivo) {
    FILE* arqBin = fopen(nome_arquivo, "wb");
    if (arqBin == NULL) {
        printf("Arquivo nao encontrado!\n");
        exit(1);
    }
    else {
        fwrite(&n, sizeof(int), 1, arqBin);
        fwrite(vet, sizeof(Aluno), n, arqBin);
    }fclose(arqBin);
}

Aluno* leia_aluno(char* nome_arquivo, int n) {
    FILE* arqBin = fopen(nome_arquivo, "rb");
    if (arqBin == NULL) {
        printf("Arquivo nao encontrado!\n");
        exit(1);
    }

    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    if (novo == NULL){
        printf("ERRO\n");
        exit(1);
    }
    else {
        int x;
        Aluno* vetor;
        fread(&x, sizeof(int), 1, arqBin);
        if (n <= x) {
            fread(vetor, sizeof(Aluno), x, arqBin);
            strcpy(novo->nome_comp,vetor[n].nome_comp);
            novo->numMatric = vetor[n].numMatric;
            novo->p1 = vetor[n].p1;
            novo->p2 = vetor[n].p2;
            novo->p3 = vetor[n].p3;
        }
    }return novo;
}

Lista* cria_lista(int n, Aluno* vet) {
    Lista* ini = NULL;
    Lista* fim = NULL;
    float med = 0;
    for (int i = 0;i < n;i++) {
        Lista* l = (Lista*)malloc(sizeof(Lista));
        if (l == NULL) {
            printf("Erro de memória\n");
            exit(1);
        }
        strcpy(l->nome, vet[i].nome_comp);
        med = (vet[i].p1 + vet[i].p2 + vet[i].p3) / 3.0;
        l->media=med;
        l->prox = NULL;//inicializou
        l=l->prox;
        if (ini == NULL) {
            ini = l;
            fim = l;
        }else{
            fim->prox = l;
            fim = l;
        }
    }
    return ini; 


}

int main(void) {
    int n;
    Aluno* alunos = leia_arquivo("alunos.txt", &n);

    printf("Numero de alunos: %d\n", n);
    for (int i = 0; i < n; i++) {
        printf("Aluno %d:\n", i + 1);
        printf(" Nome: %s\n", alunos[i].nome_comp);
        printf(" Matricula: %d\n", alunos[i].numMatric);
        printf(" P1: %.2f\n", alunos[i].p1);
        printf(" P2: %.2f\n", alunos[i].p2);
        printf(" P3: %.2f\n\n", alunos[i].p3);
    }
    salva_binario(n, alunos, "alunos.dat");
    free(alunos);
    return 0;
}