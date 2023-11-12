//Gabriel Albertini Pinheiro - R.A: 24.123.004-4

#include "biblioteca.h"


int main() {

    Tarefas_armazem *lista_tarefas;

    int opcao;

    lista_tarefas = leitura("lista"); // Le o arquivo e coloca no lista todos as tarefas presentes no arquivo

    while (true) {
        opcao = lobby();

        if (opcao == 1) {
            lista_tarefas = cadastrarTarefa(
                    lista_tarefas); // Chama a funcao para cadastrar uma tarefa
        } else if (opcao == 2) {
            listar_tarefas(lista_tarefas); // Chama a funcao para mostrar na tela do usuario todas as tarefas
        } else if (opcao == 3) {
            lista_tarefas = deletarTarefa(lista_tarefas); // Chama a funcao para listar todas as tarefas ja criadas pelo usuario
        }else if(opcao == 6){
            Filtrar_Tarefas_Prioridade(lista_tarefas);
        }else if(opcao == 7){
            Filtrar_Tarefas_Estado(lista_tarefas);
        }else if(opcao == 8){
            Filtrar_Tarefas_Categoria(lista_tarefas);
        }else if(opcao == 9) {
            Filtrar_Tarefas_CategoriaEPrioridade(lista_tarefas);
        }else if(opcao == 10){
            Exportar_TarefasPorPrioridade(lista_tarefas);
        }else if(opcao == 11){
            Exportar_TarefasPorCategoria(lista_tarefas);
        }else if(opcao == 12){
            Exportar_TarefasPorCategoriaEPrioridade(lista_tarefas);
        }else if(opcao == 0) {
                escreve(lista_tarefas,"lista"); // Fecha o programa e salva a lista no arquivo
                break;
        }else{
            printf("Opcao Invalida, por favor digite uma opcao novamente.\n");
        }
    }

    escreve(lista_tarefas , "lista");

    return 0;
}