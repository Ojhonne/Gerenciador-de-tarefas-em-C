#include <stdio.h>
#include <string.h>
#include "gerenciador.h"
#include <locale.h>

#define ENTRADA 20
char keyboard[BUFSIZ]; //uma string para a criacao de um buffer

void printaMenu();
Lista* MenuTarefas(Lista* li);
int getInput(char *buff, int size){//Funcao que 

    if (size <= 0) return 0;

    if (fgets(buff, size, stdin) != NULL) {
        size_t len = strlen(buff);

        if(len > 0 && buff[len - 1] == '\n'){
            buff[len - 1] = '\0';
        } else if(len == (size_t) size - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        return 1;
    }
    return 0;
}

int abrirTarefas(const char* nomeArquivo, Lista* li){ // Funcao que gerencia a minha lista

    if(li == NULL) return 0;

    LerLista(li, nomeArquivo);

    li = MenuTarefas(li);//chamo o menu da lista

    if(li != NULL) SalvaLista(li, nomeArquivo); // salvo ela no arquivo binario

    printf("Saindo...");
    SLEEP(2500);
    return 1;
}

void printaMenu(){
    system(CLEAR);
    printf("1. Abrir Lista de tarefas\n");
    printf("2. Excluir arquivo bin\n");
    printf("3. Sair do gerenciador de tarefas\n");
}

int main(void){
    setlocale(LC_ALL, "");
    setbuf(stdin, keyboard);//define um novo buffer 

    Lista* li = criaLista(); //cria uma lista
    char entrada[ENTRADA];
    int opcao, escolha;

    while(opcao != 3){
        printaMenu();
        if (getInput(entrada, ENTRADA)){
            if ((sscanf(entrada, "%d", &opcao) == 1)){ 
                switch (opcao){
                case 1:
                    if(!abrirTarefas(LISTA, li)) printf("Erro na funçao abrirTarefas \n");
                    SLEEP(2000);
                    break;
                case 2:
                    printf("Voce tem certeza que deseja excluir o arquivo : %s??\nDigite 1 para SIM e 0 para NAO:\n", LISTA);
                    char temp[5];
                    if(getInput(temp, sizeof(temp))){
                        sscanf(temp, "%d", &escolha);
                        if(escolha){
                            FILE* abrir = fopen(LISTA, "rb");
                            if(abrir){
                                fclose(abrir);
                                remove(LISTA);
                                printf("Arquivo removido com sucesso!!\n");
                            }
                        } else {
                            printf("Erro ao remover arquivo!");
                        }

                    }

                    SLEEP(2000);
                    break;
                case 3:
                    printf("Encerrando o programa...\n");
                    SLEEP(2000);
                    system(CLEAR);
                    destroiLista(li);
                    exit(1);
                    break;
                default:
                    printf("Opcao invalida. Tente novamente: ");
                    SLEEP(2000);
                    break;
                }
            }else{
                printf("Opcao invalida. Tente novamente: ");                    
                SLEEP(2000);
            }
        }
    }
    return 0;
}

void printaMenuTarefas(){
        printf("\n================MENU LISTA================\n");
        printf("1. Adicionar elemento \n");
        printf("2. Remover elemento \n");
        printf("3. Inserir no final \n");
        printf("4. Inserir depois de um ID especifico \n");
        printf("5. Imprimir lista \n");
        printf("6. Esvazia lista \n");
        printf("7. Sair \n");
        printf("0. Salvar e sair\n");
        printf("==========================================\n");
        printf("Escolha uma opcao: ");
}

Lista* MenuTarefas(Lista* li){
    int opcao, id, escolha;
    char descricao[MAX], entrada[ENTRADA], tempID[10];

    while(opcao != 0){
        system(CLEAR);
        POSICIONAR_CURSOR(CURSOR_CENTRAL_L, CURSOR_CENTRAL_C + 15);
        printaMenuTarefas();
        if(getInput(entrada, ENTRADA)){
            if((sscanf(entrada, "%d", &opcao) == 1)){
                switch (opcao) {
                    case 1:
                        printf("Digite a tarefa para adicionar: ");
                        if(getInput(descricao, MAX)){
                            if(addInicio(li, descricao) == 1){
                            printf("tarefa adicionado.\n");
                            printarTarefas(li);
                            }
                            else{ 
                                printf("Error ao adicionar tarefa");
                            }
                            SLEEP(2000);
                        } else {
                            printf("Erro no input!\n");
                        }
                        break;

                    case 2:
                        printf("Digite o id para remover a tarefa: ");
                        if(getInput(tempID, sizeof(tempID))){
                            sscanf(tempID, "%d", &id);
                            if ((removerID(li, id))) printf("Elemento %d removido com sucesso!\n", id);
                            else printf("Elemento %d nao encontrado.\n", id);
                        }

                        printarTarefas(li);
                        SLEEP(2000);
                        break;
                    case 3:
                        printf("Digite a tarefa para inserir no final: ");
                        if (getInput(descricao, MAX)){
                            POSICIONAR_CURSOR(CURSOR_CENTRAL_L - 2,CURSOR_CENTRAL_C +  15);

                            if (addfim(li, descricao)) printf("Elemento adicionado ao final.\n");
                            else printf("Falha ao adicionar tarefa");

                            printarTarefas(li);
                            SLEEP(2000);
                        } else {
                            printf("Erro no input!\n");
                        }
                        break;

                    case 4:
                        printf("Digite o id e a tarefa: ");
                        if(getInput(tempID, sizeof(tempID))){
                            sscanf(tempID, "%d", &id);
                            if(getInput(descricao, MAX)){
                                if ((addID(li, id, descricao))) printf("Elemento inserido na posicao %d.\n" , id);
                                else printf("Falha ao inserir elemento.\n");

                                printarTarefas(li);
                                SLEEP(2000);
                            } 
                        }
                        else {
                            printf("Erro no input!\n");
                        }
                        break;

                    case 5:
                        if (li == NULL) {
                            printf("Crie a lista primeiro!\n");
                        } else {
                            POSICIONAR_CURSOR(CURSOR_TAREFAS_H - 1, CURSOR_TAREFAS_L);
                            printf("Conteudo da lista:\n");
                            printarTarefas(li);
                            SLEEP(5000);
                        }
                        break;
                    case 6:
                        if (li == NULL) {
                            printf("Nenhuma lista para liberar.\n");
                        } else {
                            if(destroiLista(li)){
                                li = criaLista();
                                printf("Lista esvaziada com sucesso!\n");
                            }
                        }
                        SLEEP(5000);
                        break;
                    case 7:
                        printf("Deseja sair sem salvar?\ndigite 1 para SIM e 0 para NÃO: ");
                        char temp[5];
                        if(getInput(temp, sizeof(temp))){
                            sscanf(temp, "%d", &escolha);
                            if(escolha){
                                return NULL;
                            }
                        }

                        break;
                    case 0:
                        printf("Lista de tarefas salva... \n");
                        printarTarefas(li);
                        SLEEP(750);
                        return li;
                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                        getchar();
                    }
            } else
                printf("Opcao invalida! Tente novamente.\n");
        }
    } 
    return NULL;
}

