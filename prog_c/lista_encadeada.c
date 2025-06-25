#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct elemento {
    int valor;
    struct elemento* prox;
} Elemento;


Elemento* cria_lista(){
    Elemento* head = (Elemento*)malloc(sizeof(Elemento));
    if (head==NULL){
        printf("ERRO\n");
        exit(1);
    }else{
        return head;
    }
}

Elemento * lst_retira(Elemento * lst, int a){
    Elemento* primeiro = lst;
    if(lst->valor==a){//se ele for o primeiro elemento
        return lst->prox;
    }else{
        while(lst->prox->valor!=a){//se ele estiver no meio e final sos
        lst=lst->prox;
    }lst->prox=lst->prox->prox;
    }return primeiro;
} 


void lst_insere_final(int valor,Elemento*head){
    Elemento* novoElem=(Elemento*)malloc(sizeof(Elemento));
    if(novoElem==NULL){
        printf("ERRO\n");
        exit(1);
    }else{
        novoElem->valor=valor;
        novoElem->prox=NULL;
        while(head->prox!=NULL){
            head=head->prox;
        }
        head->prox=novoElem;
    }
}


Elemento* lst_insere_comeco(int valor,Elemento*head){
    Elemento* novoElem=(Elemento*)malloc(sizeof(Elemento));
    if(novoElem==NULL){
        printf("ERRO\n");
        exit(1);
    }else{
        novoElem->valor=valor;
        novoElem->prox=head;
        return novoElem;
    }
}

void imprime_lst(Elemento*atual){
    while(atual!=NULL){
        printf("%d\n",atual->valor);
        atual=atual->prox;
    }
}
Elemento* lst_busca(Elemento*head,int valor){
    while(head!=NULL){
        if(head->valor==valor){
            return head;
        }
        head=head->prox;
    } return NULL;
} 

int main (void){
    Elemento* head = cria_lista();
    head->valor = 23;
    head->prox = NULL;
    head = lst_insere_comeco(45,head);
    lst_insere_final(47,head);
    lst_insere_final(150,head);
    imprime_lst(head);
    printf("==================\n");
    head = lst_retira(head, 23);
    imprime_lst(head);
    head = lst_retira(head, 150);
    printf("==================\n");
    imprime_lst(head); 
    return 0;
}