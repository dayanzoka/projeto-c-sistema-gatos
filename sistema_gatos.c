#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. structs
typedef struct {
    int id;
    char nomeTutor[100];
    char nomeGato[100];
    int tipoServico; // vacina,banho e tosa
} Atendimento;


// protótipos das funções 

void limparBufferEntrada();
void mostrarMenu();

// passagem por referência no 'int *total'
// alocação dinâmica (retorna o novo ponteiro do vetor)
Atendimento* cadastrarAtendimento(Atendimento *db, int *total);

// funções - passagem por valor no 'int total'
void listarAtendimentos(Atendimento *db, int total);

void buscarAtendimentoPorID(Atendimento *db, int total);

// ordenação - selection sort
void ordenarAtendimentosPorID(Atendimento *db, int total);

// recursividade - fatorial
long long fatorial(int n);
void testarFuncaoRecursiva();


// função principal 
int main() {
    // ponteiros e alocação dinâmica - 'database' é o ponteiro para o vetor dinâmico
    Atendimento *database = NULL; 
    int totalAtendimentos = 0;
    int opcao;

    printf("bem-vindo ao sistema petgato :D\n");

    do {
        // menu 
        mostrarMenu();
        scanf("%d", &opcao);
        limparBufferEntrada(); 

        switch (opcao) {
            case 1:
                // passagem por referência - &totalatendimentos
                database = cadastrarAtendimento(database, &totalAtendimentos);
                break;
            case 2:
                // passagem por valor - totalatendimentos)
                listarAtendimentos(database, totalAtendimentos);
                break;
            case 3:
                buscarAtendimentoPorID(database, totalAtendimentos);
                break;
            case 4:
                ordenarAtendimentosPorID(database, totalAtendimentos);
                break;
            case 5:
                testarFuncaoRecursiva();
                break;
            case 0:
                printf("saindo do sistema...\n");
                break;
            default:
                printf("opcao invalida D: tente novamente\n");
        }

        if(opcao != 0) {
            printf("\npressione enter para continuar");
            getchar();
        }

    } while (opcao != 0);

    // alocação dinâmica - free
    free(database);
    database = NULL;

    return 0;
}


// função para não bugar o scanf + fgets
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// menu que aparece para o usuário =D
void mostrarMenu() {
    printf("\n\n--- menu principal ---\n");
    printf("1. cadastrar novo atendimento\n");
    printf("2. listar todos atendimentos\n");
    printf("3. buscar atendimento (por id)\n");
    printf("4. ordenar atendimentos por id (extra)\n");
    printf("5. testar funcao recursiva (extra)\n");
    printf("0. sair\n");
    printf("escolha uma opcao: ");
}

// função de passagem por referência e alocação dinâmica (realloc)
Atendimento* cadastrarAtendimento(Atendimento *db, int *total) {
    
    // passagem por referência
    (*total)++;

    // alocação dinâmica 
    db = (Atendimento *) realloc(db, (*total) * sizeof(Atendimento));

    if (db == NULL) {
        printf("erro fatal: falha ao alocar memoria!\n");
        exit(1);
    }

    // pega o índice do novo atendimento (o último)
    int novoIndex = (*total) - 1;

    // manipulação de array de struct
    printf("\n--- cadastro de atendimento ---\n");
    printf("digite o id (numero): ");
    scanf("%d", &db[novoIndex].id);
    limparBufferEntrada(); 

    printf("digite o nome do tutor: ");
    fgets(db[novoIndex].nomeTutor, 100, stdin);
    db[novoIndex].nomeTutor[strcspn(db[novoIndex].nomeTutor, "\n")] = 0;

    printf("digite o nome do gato: ");
    fgets(db[novoIndex].nomeGato, 100, stdin);
    db[novoIndex].nomeGato[strcspn(db[novoIndex].nomeGato, "\n")] = 0;

    printf("digite o servico: 1 - vacina, 2 - banho, 3 - tosa): ");
    scanf("%d", &db[novoIndex].tipoServico);
    limparBufferEntrada();

    printf("\natendimento (id: %d) cadastrado com sucesso!", db[novoIndex].id);
    
    // retorna o ponteiro 
    return db;
}

// manipulação de array de struct
void listarAtendimentos(Atendimento *db, int total) {
    printf("\n--- lista de atendimentos cadastrados (%d) ---\n", total);
    if (total == 0) {
        printf("nenhum atendimento cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("--------------------------------------\n");
        printf("id atendimento: %d\n", db[i].id);
        printf("tutor: %s\n", db[i].nomeTutor);
        printf("gato:  %s\n", db[i].nomeGato);
        printf("servico: %d\n", db[i].tipoServico);
    }
    printf("--------------------------------------\n");
}

// busca sequencial
void buscarAtendimentoPorID(Atendimento *db, int total) {
    if (total == 0) {
        printf("\nnenhum atendimento cadastrado para buscar.\n");
        return;
    }

    int idBusca;
    printf("\n--- buscar atendimento ---\n");
    printf("digite o id do atendimento: ");
    scanf("%d", &idBusca);
    limparBufferEntrada();

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        // uso do ponteiro - db[i]
        if (db[i].id == idBusca) {
            printf("\n--- atendimento encontrado ---\n");
            printf("id atendimento: %d\n", db[i].id);
            printf("tutor: %s\n", db[i].nomeTutor);
            printf("gato:  %s\n", db[i].nomeGato);
            printf("servico: %d\n", db[i].tipoServico);
            encontrado = 1;
            break; 
        }
    }

    if (!encontrado) {
        printf("\natendimento com id %d não encontrado.\n", idBusca);
    }
}

// ordenação - selection sort
void ordenarAtendimentosPorID(Atendimento *db, int total) {
    if (total < 2) {
        printf("\nnão há atendimentos suficientes para ordenar.\n");
        return;
    }

    int i, j, indiceMenor;
    Atendimento temp; // variável temporária para a troca

    for (i = 0; i < total - 1; i++) {
        indiceMenor = i;
        // acha o menor elemento no resto do vetor
        for (j = i + 1; j < total; j++) {
            if (db[j].id < db[indiceMenor].id) {
                indiceMenor = j;
            }
        }
        
        // troca o menor (indicemenor) com o elemento atual (i)
        if (indiceMenor != i) {
            temp = db[i];
            db[i] = db[indiceMenor];
            db[indiceMenor] = temp;
        }
    }

    printf("\natendimentos ordenados por id com sucesso!");
    printf("\n(use a opcao 2 para ver o resultado.)\n");
}

// recursividade - fatorial
long long fatorial(int n) {
    // caso base 
    if (n == 0 || n == 1) {
        return 1;
    }
    // passo recursivo - chama ele mesmo
    return (long long)n * fatorial(n - 1);
}

// função para o menu testar a recursão
void testarFuncaoRecursiva() {
    int num;
    printf("\n teste de função recursiva :P \n");
    printf("digite um numero: ");
    
    scanf("%d", &num);
    limparBufferEntrada();

    if (num < 0) {
        printf("fatorial não definido para números negativos.\n");
    } else {
        long long resultado = fatorial(num);
        printf("o fatorial de %d é: %lld\n", num, resultado);
    }
}