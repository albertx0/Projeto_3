#include "biblioteca.h"

int lobby() { // Funcao que demonstra ao usuarios todas as opcoes que ele pode utilizar no aplicativo
    int opcao;

    printf("\n1 - Cadastrar nova tarefa.\n");
    printf("2 - Listar tarefas ja criadas.\n");
    printf("3 - Deletar uma terefa.\n");
    printf("4 - Alterar tarefa.\n");
    printf("5 - Filtrar tarefas por prioridade.\n");
    printf("6 - Filtrar tarefas por estado.\n");
    printf("7 - Filtrar tarefas por categoria.\n");
    printf("8 - Filtar tarefas por categoria e prioridade.\n");
    printf("9 - Exportar tarefas por prioridade.\n");
    printf("10 - Exportar tarefas por categoria.\n");
    printf("11 - Exportar tarefas por categoria e prioridade.\n");
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
        input_string(Lista_Tarefas->tarefas[indice].categoria , 100); // Recebe a entrada da variavel de categoria

        printf("Escreva a descricao da tarefa: ");
        input_string(Lista_Tarefas->tarefas[indice].descricao , 300); // Recebe a entrada da variavel de descricao

        printf("Escreva o estado da tarefa: ");
        input_string(Lista_Tarefas->tarefas[indice].Estado , 20); // Recebe a entrada da variavel de estado;

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
            printf("Categoria: %s\n", lista->tarefas[i].categoria);
            printf("Descricao: %s\n", lista->tarefas[i].descricao);
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

Tarefas_armazem* AlterarTarefa(Tarefas_armazem* Lista_Tarefas){
    listar_tarefas(Lista_Tarefas);

    int indice_alterar; //Indice que o usuario vai digitar para indicar qual tarefa deseja alterar
    printf("Digite o indice da tarefa que deseja alterar: ");
    scanf("%d" , &indice_alterar);

    int Escolha_Alteracao = MenuAlteracao(); //Funcao que retora o indice de qual fator o usuario deseja alterar

    if(Escolha_Alteracao == 1){ //Se Escolha_Alteracao for igual a '1' o usuario optou pela troca da prioridade da tarefa
        int NovaPrioridade;

        printf("Digite a nova prioridade de sua tarefa: ");
        scanf("%d" , &NovaPrioridade);

        Lista_Tarefas->tarefas[indice_alterar - 1].prioridade = NovaPrioridade;
        printf("Alteracao feita com sucesso !\n");
    }else if(Escolha_Alteracao == 2){ //Se Escolha_Alteracao for igual a '2' o usuario optou pela troca da categoria da tarefa
        LoopDeLeitura();

        char NovaCategoria[100];

        printf("Escreva a nova categoria de sua tarefa: ");
        input_string(NovaCategoria , 100);

        strcpy(Lista_Tarefas->tarefas[indice_alterar - 1].categoria , NovaCategoria);
        printf("Alteracao feita com sucesso !\n");
    }else if(Escolha_Alteracao == 3){ //Se Escolha_Alteracao for igual a '3' o usuario optou pela troca da estado da tarefa
        LoopDeLeitura();

        char NovoEstado[20];

        printf("Escreva a nova descricao para sua tarefa: ");
        input_string(NovoEstado , 20);

        strcpy(Lista_Tarefas->tarefas[indice_alterar - 1].Estado , NovoEstado);
        printf("Alteracao feita com sucesso !\n");
    }else if(Escolha_Alteracao == 4){ //Se Escolha_Alteracao for igual a '4' o usuario optou pela troca da descricao da tarefa
        LoopDeLeitura();

        char NovaDescricao[300];

        printf("Escreva a nova descricao para sua tarefa: ");
        input_string(NovaDescricao , 300);

        strcpy(Lista_Tarefas->tarefas[indice_alterar - 1].descricao , NovaDescricao);
        printf("Alteracao feita com sucesso !\n");
    } else if(Escolha_Alteracao == 5){ //Se Escolha_Alteracao for igual a '5' o usuario optou for finalizar a operacao
        printf("Opcao cancelada pelo usuario.\n");
    }

    return Lista_Tarefas;
}

void Filtrar_Tarefas_Prioridade(Tarefas_armazem* Lista_Tarefas){
    int Prioridade_Filtro;
    int Verifica_Prioridade = 0;

    printf("\n====================\n");

    printf("Digite a prioridade das tarefas que deseja que seja listado: ");
    scanf("%d" , &Prioridade_Filtro);

    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){

        if(Lista_Tarefas->tarefas[i].prioridade == Prioridade_Filtro){ // Imprime as tarefas caso a prioridade delas seja igual a prioridade escolhida pelo usuario
            printf("\nPrioridade: %d\n", Lista_Tarefas->tarefas[i].prioridade);
            printf("Categoria: %s\n", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s\n", Lista_Tarefas->tarefas[i].descricao);
            printf("Estado: %s\n" , Lista_Tarefas->tarefas[i].Estado);

            Verifica_Prioridade = 1;
        }

    }

    if(Verifica_Prioridade == 0){ // Caso o Verifica_Prioridade seja igual a '0' significa que em nenhum momento entrou no if de prioridade e retorna ao usuario que nenhuma tarefa com a prioridade desejada foi encontrada
        printf("Nenhuma tarefa cadastrada com essa prioridade.\n");
    }

    printf("====================\n");
}

void Filtrar_Tarefas_Estado(Tarefas_armazem* Lista_Tarefas){
    LoopDeLeitura();

    char Estado_Filtro[20];
    printf("Escreva o estado das tarefas que deseja visualizar: "); //Entrada do estado das tarefas que o usuario deseja listar
    input_string(Estado_Filtro , 20);

    int Verifica_Estado = 0;

    printf("\n====================\n");
    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){

        if(strcmp(Lista_Tarefas->tarefas[i].Estado , Estado_Filtro) == 0){ // Imprime as tarefas caso o estado delas seja igual ao escrito pelo usuario
            printf("\nPrioridade: %d\n", Lista_Tarefas->tarefas[i].prioridade);
            printf("Categoria: %s\n", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s\n", Lista_Tarefas->tarefas[i].descricao);
            printf("Estado: %s\n" , Lista_Tarefas->tarefas[i].Estado);

            Verifica_Estado = 1;
        }
    }
    if(Verifica_Estado == 0)
        printf("Nenhuma tarefa cadastrada com esse estado.\n");

    printf("====================\n");
}

void Filtrar_Tarefas_Categoria(Tarefas_armazem* Lista_Tarefas){
    LoopDeLeitura();

    char Categoria_Filtro[100];
    printf("Escreva a categoria das tarefas que deseja listar: "); // Recebe a categoria das tarefas que o usuario deseja que liste
    input_string(Categoria_Filtro , 100);

    Tarefas_armazem Lista_Tarefas_Temp = *Lista_Tarefas; // Criacao de um array temporario para que a funcao "qsort" nao altere o array principal

    qsort(Lista_Tarefas_Temp.tarefas , Lista_Tarefas_Temp.Tamanho , sizeof(Tarefa) , Compara_Prioridades); // Funcao para ordenar o array de acordo com a prioridade

    for(int i = 0 ; i < Lista_Tarefas_Temp.Tamanho ; i++){
        if(strcmp(Lista_Tarefas_Temp.tarefas[i].categoria , Categoria_Filtro) == 0){ // Imprime as tarefas do array caso a categoria corresponda com a escrita pelo cliente
            printf("\nPrioridade: %d\n", Lista_Tarefas->tarefas[i].prioridade);
            printf("Categoria: %s\n", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s\n", Lista_Tarefas->tarefas[i].descricao);
            printf("Estado: %s\n" , Lista_Tarefas->tarefas[i].Estado);
        }
    }
}

void Filtrar_Tarefas_CategoriaEPrioridade(Tarefas_armazem* Lista_Tarefas){
    int Prioridade_Filtro;
    printf("Digite a prioridade das tarefas que deseja listar: "); // Recebe a prioridade das tarefas que deseja imprimir
    scanf("%d" , &Prioridade_Filtro);

    LoopDeLeitura();

    char Categoria_Filtro[100];
    printf("Escreva a categoria das tarefas que deseja listar: "); // Recebe a categoria das tarefas que deseja imprimir
    input_string(Categoria_Filtro , 100);

    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){
        if(strcmp(Lista_Tarefas->tarefas[i].categoria , Categoria_Filtro) == 0 && Lista_Tarefas->tarefas[i].prioridade == Prioridade_Filtro){ // Caso a categoria e prioridade das tarefas correponda com as informadas pelo usuario, elas sao impressas
            printf("\nPrioridade: %d\n", Lista_Tarefas->tarefas[i].prioridade);
            printf("Categoria: %s\n", Lista_Tarefas->tarefas[i].categoria);
            printf("Descricao: %s\n", Lista_Tarefas->tarefas[i].descricao);
            printf("Estado: %s\n" , Lista_Tarefas->tarefas[i].Estado);
        }
    }
}

void Exportar_TarefasPorPrioridade(Tarefas_armazem* Lista_Tarefas){
    int Prioridade_Filtro;
    printf("Digite a prioridade das tarefas que deseja listar: "); // Recebe a prioridade das tarefas que deseja exportar
    scanf("%d" , &Prioridade_Filtro);


    FILE *arquivo_tarefas = fopen("TarefasExportadasPorPrioridade.txt" , "w");

    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){
        if(Lista_Tarefas->tarefas[i].prioridade == Prioridade_Filtro){ // Imprime no arquivo caso a prioridade seja igual a digitada pelo usuario
            fprintf(arquivo_tarefas , "Prioridade: %d | Categoria: %s | Estado: %s | Descricao: %s\n" , Lista_Tarefas->tarefas[i].prioridade , Lista_Tarefas->tarefas[i].categoria , Lista_Tarefas->tarefas[i].Estado , Lista_Tarefas->tarefas[i].descricao);
        }
    }
}

void Exportar_TarefasPorCategoria(Tarefas_armazem* Lista_Tarefas){
    LoopDeLeitura();

    char Categoria_Filtro[100];
    printf("Escreva a categoria das tarefas que deseja exportar: "); // Recebe a categoria das tarefas que deseja exportar
    input_string(Categoria_Filtro , 100);

    FILE *arquivo_tarefas = fopen("TarefasExportadasPorCategoria.txt" , "w");

    Tarefas_armazem Lista_Tarefas_Temp = *Lista_Tarefas; // Criacao de lista temporaria para a funcao "qsort" nao afetar a original

    qsort(Lista_Tarefas_Temp.tarefas , Lista_Tarefas_Temp.Tamanho , sizeof(Tarefa) , Compara_Prioridades); // Funcao para ordenar as tarefas de acordo com a prioridade

    for(int i = 0 ; i < Lista_Tarefas_Temp.Tamanho ; i++){
        if(strcmp(Lista_Tarefas_Temp.tarefas[i].categoria , Categoria_Filtro) == 0){ // Caso a categoria da tarefa correponda com a informada pelo usuario, a tarefa eh impressa no arquivo
            fprintf(arquivo_tarefas , "Prioridade: %d | Categoria: %s | Estado: %s | Descricao: %s\n" , Lista_Tarefas_Temp.tarefas[i].prioridade , Lista_Tarefas_Temp.tarefas[i].categoria , Lista_Tarefas_Temp.tarefas[i].Estado , Lista_Tarefas_Temp.tarefas[i].descricao);
        }
    }
}

void Exportar_TarefasPorCategoriaEPrioridade(Tarefas_armazem* Lista_Tarefas){

    int Prioridade_Filtro;
    printf("Digite a prioridade das tarefas que deseja listar: "); // Recebe a prioridade das tarefas que deseja imprimir no arquivo
    scanf("%d" , &Prioridade_Filtro);

    LoopDeLeitura();

    char Categoria_Filtro[100];
    printf("Escreva a categoria das tarefas que deseja exportar: "); // Recebe a categoria das tarefas que deseja imprimir no arquivo
    input_string(Categoria_Filtro , 100);

    FILE *arquivo_tarefas = fopen("TarefasExportadasPorCategoriaEPrioridade.txt" , "w");

    for(int i = 0 ; i < Lista_Tarefas->Tamanho ; i++){
        if(strcmp(Lista_Tarefas->tarefas[i].categoria , Categoria_Filtro) == 0 && Lista_Tarefas->tarefas[i].prioridade == Prioridade_Filtro){ // Caso a categoria e prioridade da tarefa correponda com a informada pelo usuario, a tarefa eh impressa no arquivo
            fprintf(arquivo_tarefas , "Prioridade: %d | Categoria: %s | Estado: %s | Descricao: %s\n" , Lista_Tarefas->tarefas[i].prioridade , Lista_Tarefas->tarefas[i].categoria , Lista_Tarefas->tarefas[i].Estado , Lista_Tarefas->tarefas[i].descricao);
        }
    }
}

char* input_string(char* str , int max_caracteres) { // Funcao para simular o input do python
    int c;

    fgets(str, max_caracteres, stdin); // Recebe o array de string


    size_t comprimento = strlen(str);
    if (comprimento > 0 && str[comprimento - 1] == '\n') { // Remover o caractere de nova linha '\n' do final da string
        str[comprimento - 1] = '\0';
    } else {

        while ((c = getchar()) != '\n' && c != EOF); // Limpar o buffer de entrada restante se necessário
    }

    return str;
}

int MenuAlteracao(){ // Funcao para imprimir o menu no terminal do usuario e retornar a opcao escolhida pelo mesmo
    int Escolha_Alteracao;

    while(true){
        printf("1 - Para alterar a prioridade.\n");
        printf("2 - Para alterar a categoria.\n");
        printf("3 - Para alterar o estado.\n");
        printf("4 - Para alterar a descricao.\n");
        printf("5 - Para cancelar alteracao.\n");
        printf("Digite a opcao que deseja: ");
        scanf("%d" , &Escolha_Alteracao);

        if(Escolha_Alteracao > 0 && Escolha_Alteracao < 6){
            break;
        }
    }

    return Escolha_Alteracao;
}

int Compara_Prioridades(const void *a , const void *b){ // Funcao utilizada pela funcao "qsort" para ordenar as tarefas do maior pára o menor
    return ((Tarefa*)b)->prioridade - ((Tarefa*)a)->prioridade;
}

void LoopDeLeitura(){ // Funcao para limpar buffers restantes
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}