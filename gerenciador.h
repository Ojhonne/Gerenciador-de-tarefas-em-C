#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <stdio.h>  // Necessário para FILE* e printf
#include <stdlib.h> // Necessário para malloc/free
#include <string.h> // Necessário para manipulacao de strings

#define MAX 512//tamanho da string descrição
#define LISTA "listaDeTarefas.bin"//Definindo o nome do arquivo que será criado
#define POSICIONAR_CURSOR(lin, col) printf("\033[%d;%dH", lin, col) // definindo os cursores na hora de printar
#define CURSOR_CENTRAL_L 1
#define CURSOR_CENTRAL_C 15
#define CURSOR_TAREFAS_L 75
#define CURSOR_TAREFAS_H 2

//Para limpeza do terminal
#ifdef _WIN32 
    #include <windows.h>
    #define CLEAR "cls"
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define SLEEP(ms) usleep((ms) * 1000)
#endif 

typedef struct informacoes{
    char *descricao;
    int id;
}informacoes;

typedef struct No{
    informacoes Dados; 
    struct No* prox;
}No;

typedef struct Lista{
    No* inicio;
    No* fim;
    int contador;
    int proxID;
}Lista;

//funções da lista
Lista* criaLista();
No* alocaNo(Lista* li, char descricao[], int id_manual);
No* criaNo(Lista* li, char descricao[]);
int addInicio(Lista* li, char tarefa[]);
int addID(Lista* li, int id, char descricao[]);
int addNoID(Lista* li, int id, char descricao[]);
int addfim(Lista* li, char descricao[]);
int removerID(Lista* li, int id);
void SalvaLista(Lista *li, const char* nomeArquivo);
void LerLista(Lista* li, const char* nomeArquivo);
void printarTarefas(Lista* li);
int destroiLista(Lista* li);

#endif