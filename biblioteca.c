#include "biblioteca.h"

int lobby() { // Funcao que demonstra ao usuarios todas as opcoes que ele pode utilizar no aplicativo
    int opcao;

    printf("\n1 - Cadastrar nova tarefa.\n");
    printf("2 - Listar tarefas ja criadas.\n");
    printf("3 - Deletar uma terefa.\n");
    printf("6 - Filtrar tarefas por prioridade.\n");
    printf("7 - Filtrar tarefas por estado.\n");
    printf("0 - Fechar programa.\n");
    printf("\nDigite o numero da opcao desejada: ");

    scanf("%d" , &opcao);

    return opcao;
}

Tarefas_armazem *leitura(char *nome) {

    FILE *arquivo = fopen(nome, "rb"); // Abre o arquivo

    Tarefas_armazem *Lista_Tarefas = (Tarefas_armazem *)malloc(100 * sizeof(Tarefas_armazem));

    if(arquivo == NULL){
        Lista_Tarefas->Tamanho = 0;
    }else{
        fread(Lista_Tarefas, sizeof(Tarefas_armazem), 100,arquivo); // Le ate a linha 100 e coloca todas as informacoes no array
        fclose(arquivo); // Fecha o arquivo
    }

    return Lista_Tarefas; // Retorna o array com as informacoes do arquivo
}

void escreve(Tarefas_armazem *Lista_Tarefas, char *nome) {
    FILE *arquivo = fopen(nome, "wb"); // Realiza a abertura do arquivo com o objetivo de escrever todas as possiveis tarefas feitas pelo usuario

    fwrite(Lista_Tarefas, sizeof(Tarefas_armazem), 100, arquivo); // Escreve as tarefas

    fclose(arquivo);
}

Tarefas_armazem* cadastrarTarefa(Tarefas_armazem *Lista_Tarefas) {
    printf("\n====================\n");
    if(Lista_Tarefas->Tamanho == 100){
        printf("Cadastro de novas tarefas indisponivel, limite de tarefas cadastradas atingido.\n");
    }else{
        int indice = Lista_Tarefas->Tamanho; // Declara a variavel "indice" para guardar o valor do tamanho da struct

        Lista_Tarefas->Tamanho = indice + 1; // Somando 1 ao valor atual da lista

        printf("Digite a prioridade da tarefa de 1 a 10: ");
        scanf("%d", &Lista_Tarefas->tarefas[indice].prioridade); // Recebe a entrada da variavel de prioridade


        LoopDeLeitura();

        printf("Escreva a categoria da tarefa: ");
        fgets(Lista_Tarefas->tarefas[indice].categoria, 100, stdin); // Recebe a entrada da variavel de categoria

        printf("Escreva a descricao da tarefa: ");
        fgets(Lista_Tarefas->tarefas[indice].descricao, 300, stdin); // Recebe a entrada da variavel de descricao

        printf("Escreva o estado da tarefa: ");
        fgets(Lista_Tarefas->tarefas[indice].Estado , 20 , stdin); // Recebe a entrada da variavel de estado;

        printf("\nTarefa adionada a lista com sucesso\n");
    }
    printf("=================\n");

    return Lista_Tarefas; // Retorna a lista de tarefas
}

void listar_tarefas(Tarefas_armazem *lista) {



    if (lista->Tamanho == 0) { // Realiza a verificação se a lista esta vazia
        printf("\n====================\n");
        printf("Lista de tarefas vazia....\n");
        printf("====================\n");
    } else {
        printf("\n====================\n");
        printf("Lista Tarefas Atual: \n");

        for (int i = 0; i < lista->Tamanho ; i++) { // Realiza um for que vai iterar ate o tamanho atual da lista de tarefas que vai realizando o print de cada tarefa
            printf("Tarefa - %d\n", i + 1);
            printf("Prioridade: %d\n", lista->tarefas[i].prioridade);
            printf("Categoria: %s", lista->tarefas[i].categoria);
            printf("Descricao: %s", lista->tarefas[i].descricao);
            printf("Estado: %s\n" , lista->tarefas[i].Estado);
        }
        printf("====================\n");
    }
}

Tarefas_armazem *deletarTarefa(Tarefas_armazem* lista) {

    // Realiza a verificacao se a lista esta vazia

    if (lista->Tamanho == 0) {
        printf("\n====================\n");
        printf("Lista de tarefas vazia....\n");
        printf("====================\n");
        return lista;
    } else {
        Tarefas_armazem *lista_temp = (Tarefas_armazem *)malloc(100 * sizeof(Tarefas_armazem)); // Criacao de um array temporario

        listar_tarefas(lista); // Lista todas as tarefas para o usuario escolher qual deseja deletar

        int tamanho = lista->Tamanho; // Declara a variavel tamanho para guardar o tamanho atual da struct

        int indice;

        printf("\nDigite o numero da tarefa que deseja deletar: ");
        scanf("%d", &indice); // Variavel que vai receber o valor que o usuario
        // deseja deletar

        int cont = 0;

        for (int i = 0; i < tamanho; i++) { // For que realiza a iteracao ate o tamanho da lista e caso o "i" seja igual ao "indice" o programa nao adiciona na lista temporaria
            if (i != indice - 1) {
                lista_temp->tarefas[cont].prioridade = lista->tarefas[i].prioridade;
                strcpy(lista_temp->tarefas[cont].categoria,lista->tarefas[i].categoria);
                strcpy(lista_temp->tarefas[cont].descricao,lista->tarefas[i].descricao);
                strcpy(lista_temp->tarefas[cont].Estado,lista->tarefas[i].Estado);
                cont++;
            }
        }

        lista_temp->Tamanho = lista->Tamanho - 1; // Subtraindo 1 ao valor atual da lista
        return lista_temp; // Retorna a nova lista com a tarefa que o usuario desejou excluida
    }
}


void Filtrar_Tarefas_Prioridade(Tarefas_armazem* Lista_Tarefas){
    int Prioridade_Escolha;
    int Verifica_Prioridade = 0;

    printf("\n====================\n");

    printf("Digite a prioridade das tarefas que deseja que seja listado: ");
    scanf("%d" , &Prioridade_Escolha);

    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){

        if(Lista_Tarefas->tarefas[i].prioridade == Prioridade_Escolha){
            printf("\nCategoria: %s", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s", Lista_Tarefas->tarefas[i].descricao);
            printf("Estado: %s" , Lista_Tarefas->tarefas[i].Estado);

            Verifica_Prioridade = 1;
        }

    }

    if(Verifica_Prioridade == 0){
        printf("Nenhuma tarefa cadastrada com essa prioridade.\n");
    }

    printf("====================\n");
}

void Filtrar_Tarefas_Estado(Tarefas_armazem* Lista_Tarefas){
    LoopDeLeitura();

    char Estado_Filtro[20];
    printf("Escreva o estado das tarefas que deseja visualizar: ");
    fgets(Estado_Filtro , 20 , stdin);

    int Verifica_Estado = 0;

    printf("\n====================\n");
    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){

        if(strcmp(Lista_Tarefas->tarefas[i].Estado , Estado_Filtro) == 0){
            printf("\nPrioridade: %d\n" , Lista_Tarefas->tarefas[i].prioridade);
            printf("Categoria: %s", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s", Lista_Tarefas->tarefas[i].descricao);

            Verifica_Estado = 1;
        }
    }
    if(Verifica_Estado == 0)
        printf("Nenhuma tarefa cadastrada com esse estado.\n");

    printf("====================\n");
}

void LoopDeLeitura(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}