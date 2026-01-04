#include <stdio.h>
#include "gerenciador.h"
#include <stdlib.h>
#include <string.h>

Lista* criaLista(){
    Lista* li = (Lista*)malloc(sizeof(Lista));
    if(li == NULL){
        printf("Erro ao alocar memoria para a lista!!\n");
        return NULL;
    }
    //inicializando a lista!!
    li->contador = 0;
    li->fim = NULL;
    li->inicio = NULL;
    li->proxID = 1;

    return li;
}
No* alocaNo(Lista* li, char descricao[], int id){
    No* novo = (No*)malloc(sizeof(No));
    if(novo == NULL) return NULL;

    int tam = strlen(descricao);

    novo->Dados.descricao = (char*)malloc(sizeof(char) * (tam + 1));

    if(novo->Dados.descricao == NULL){
        free(novo); // Limpa o nó se a string falhar!
        return NULL;
    }

    strcpy(novo->Dados.descricao, descricao);
    novo->prox = NULL;
    //1.caso: ID veio do arquivo 
    if (id >= 0) {
        novo->Dados.id = id; // Usa o ID que veio do arquivo
    } else { //2. caso: o ID ainda vai vim
        novo->Dados.id = li->proxID; 
        li->proxID++; // Prepara para o próximo ID
    }

    return novo;
}
No* criaNo(Lista* li, char descricao[]) {
    if(li == NULL) return NULL;
    return alocaNo(li, descricao, -1); // Passa -1 caso for esta criando uma lista do zero
}

int addInicio(Lista* li, char descricao[]){
    if(li == NULL){
        printf("Lista ainda nao criada!!\n");
        return 0;
    }
    No* novo = criaNo(li, descricao);
    if(novo == NULL) return 0;
    
    if(li->inicio == NULL){ //caso a lista esteja vazia
        li->inicio = novo;
        li->fim = novo;
    }else{ // caso nao esteja vazia
        novo->prox = li->inicio;
        li->inicio = novo;
    }

    li->contador++; //aumentando o contador de quantidade da lista

    return 1;
}

int addID(Lista* li, int id, char descricao[]){
    if(li == NULL){
        printf("Lista ainda nao criada!!\n");
        return 0;
    }
    if(id < 0 || id > li->proxID){ //delimitando o escopo para evitar posições invalidas
        printf("ID nao existe!!\n");
        return 0;
    }

    //1. caso: id igual ao prox id, ou seja, Adicionar no final!
    if(id == li->proxID) return addfim(li, descricao);

    //criando no
    No* novo = criaNo(li, descricao);
    if(novo == NULL){
        printf("Nao foi possivel criar o no!!\n");
        return 0;
    }
    //percorrendo ate achar o id alvo
    No* aux = li->inicio;
    while(aux != NULL){
        if(aux->Dados.id == id)
            break;
        aux = aux->prox;
    }
    //se for NULL significa que o id não existe
    if(aux == NULL){
        printf("ID nao encontrado!!!\n");
        return 0;
    }   
    //2. caso: inserindo no meio
    novo->prox = aux->prox;
    aux->prox = novo;

    li->contador++;
    
    return 1;
}

int addNoID(Lista* li, int id, char descricao[]){// Função para recriar a lista na memoria RAM
    if(li == NULL){
        printf("Lista ainda nao criada!!\n");
        return 0;
    }
    
    No* novo = alocaNo(li, descricao, id);
    if(novo == NULL){
        printf("Nao foi possivel criar o no!!\n");
        return 0;
    }

    //inserindo no final
    if(li->inicio == NULL)
        li->inicio = novo;
    else 
        li->fim->prox = novo;
    
    li->fim = novo;

    li->contador++;
    return 1;
}

int addfim(Lista* li, char descricao[]){
    if(li == NULL){
        printf("Lista ainda nao criada!!\n");
        return 0;
    }
    if(li->fim == NULL) return addInicio(li, descricao);
    // se não tive um ponteiro para o ultimo significa que está vaizo
    No* novo = criaNo(li, descricao);
    if(novo == NULL){
        printf("Nao foi possivel criar o no!!\n");
        return 0;
    }
    li->fim->prox = novo; // o proximo do ulyimo aponta par ao novo
    li->fim = novo;
    
    li->contador++;
    return 1;
}

int removerID(Lista* li, int id){
    //Verificações da lista
    if(li == NULL){
        printf("Lista nao encontrada!!\n");
        return 0;
    }
    if(li->contador == 0){
        printf("A lista esta vazia");
        return 0;
    }
    //criaçaõ de dois nos auxiliar
    No* aux = NULL;
    No* atual = li->inicio;
    //1.caso: o No inicial coincide com o id
    if(atual->Dados.id == id){
        aux = atual->prox;
        if(li->contador == 1) li->fim = NULL; // caso ele for o único nó
        li->inicio = aux;
    }else{ // 2.caso: Para todos os casos restante com exceção do primeiro
        No* anterior = li->inicio;
        atual = anterior->prox;
        while(atual != NULL){
            if(atual->Dados.id == id) break;
            anterior = atual;
            atual = atual->prox;
        }
        //verificao para ver se achou um que os IDs coincidem 
        if(atual == NULL){
            printf("Id nao encontrado!!\n");
            return 0;
        }
        anterior->prox = atual->prox;
        if(atual == li->fim) li->fim = anterior;
    }
    free(atual);
    li->contador--;
    return 1;
}
void printarTarefas(Lista* li){
    if(li == NULL){
        printf("Lista de tarefas nao criada p!!\n");
        return;
    }
    No* aux = li->inicio;
    int i = 0;
    while(aux != NULL){
        POSICIONAR_CURSOR(CURSOR_TAREFAS_H + i, CURSOR_TAREFAS_L);
        printf("%d.%s\n", aux->Dados.id, aux->Dados.descricao);
        aux = aux->prox;
        i++;
    }
    POSICIONAR_CURSOR(CURSOR_CENTRAL_C, CURSOR_CENTRAL_L);
}
void SalvaLista(Lista *li, const char* nomeArquivo){//Funcao para armazenar a lista de tarefas no arquivo
    if(li == NULL){
        printf("Lista de tarefas nao criada!!!\n");
        return;
    }
    FILE* arquivo = fopen(nomeArquivo, "wb");

    if(!arquivo){
        printf("Erro ao criar arquivo: %s\n", nomeArquivo);
        return;
    }
    No* aux = li->inicio;
    fwrite(li, sizeof(Lista), 1, arquivo); // armazena as informaçoes da minha struct "LISTA"

    while(aux != NULL){
        fwrite(&aux->Dados.id, sizeof(int), 1, arquivo); //armazena o ID
        int size = strlen(aux->Dados.descricao) + 1; // descobre o tamanho da string para armazenar ela
        fwrite(&size, sizeof(int), 1, arquivo); // armazena o tamanho da string
        fwrite(aux->Dados.descricao, sizeof(char), size, arquivo); // guarda a string
        aux = aux->prox;    //avanca para o proximo
        //então, fica assim: Informaçeos da LISTA - ID - SIZE - DESCRICAO
    }

    fclose(arquivo);
}
void LerLista(Lista* li, const char* nomeArquivo){ //Função que ler o arquivo e transfere para memoria RAM
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if(!arquivo){
        printf("Arquivo nao criado!!\n");
        return;
    }

    fread(li, sizeof(Lista), 1, arquivo); //Lê primeiro a struct da lista;
    int C = li->contador; //pega uma variavel para guardar a quantidade de nos

    //renicializando a lista, pois os endereços nas quais elas apontam não servem mais!!
    li->inicio = NULL; 
    li->fim = NULL;
    //zerando o contador pois caso ao contrario tera duas vezes a quantidade real!
    li->contador = 0;

    int id;
    int size;
    char *descricao;

    for(int i = 0; i < C; i++){ // for com base na quantidade de nos
        fread(&id, sizeof(int), 1, arquivo); //lendo o ID
        fread(&size, sizeof(int), 1, arquivo);//lendo o tamanho da string

        descricao = (char*)malloc(sizeof(char) * size); //Criando uma string com base nesse tamanho

        fread(descricao, sizeof(char), size, arquivo);//lendo a string
        addNoID(li, id, descricao); //chama a funcao para inserir os nos no final com base no ID

        free(descricao); //limpando a variavel para nao ter perda de memoria
    } 
    fclose(arquivo);

    return;
}

int destroiLista(Lista* li){
    if(li == NULL){
        printf("A lista nem existe ainda!!\n");
        return 0;
    }
    No* aux = NULL;
    No* atual = li->inicio;
    while(atual != NULL){
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(li);
    return 1;
}