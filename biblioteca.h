#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char Estado[20];
} Tarefa;

typedef struct {
    Tarefa tarefas[100];
    int Tamanho;
} Tarefas_armazem;

int lobby();
Tarefas_armazem *leitura(char *nome);
void escreve(Tarefas_armazem *v, char *nome);
Tarefas_armazem *cadastrarTarefa(Tarefas_armazem *lista);
Tarefas_armazem *deletarTarefa(Tarefas_armazem *lista);
void listar_tarefas(Tarefas_armazem *lista);
void Filtrar_Tarefas_Prioridade(Tarefas_armazem* Lista_Tarefas);
void Filtrar_Tarefas_Estado(Tarefas_armazem* Lista_Tarefas);
void Filtrar_Tarefas_Categoria(Tarefas_armazem* Lista_Tarefas);
void Filtrar_Tarefas_CategoriaEPrioridade(Tarefas_armazem* Lista_Tarefas);
void Exportar_TarefasPorPrioridade(Tarefas_armazem* Lista_Tarefas);
void Exportar_TarefasPorCategoria(Tarefas_armazem* Lista_Tarefas);
void Exportar_TarefasPorCategoriaEPrioridade(Tarefas_armazem* Lista_Tarefas);

char* input_string(char* str , int max_caracteres);
int Compara_Prioridades(const void *a , const void *b);
void LoopDeLeitura();