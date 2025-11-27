#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Necessário para usar o tipo 'bool'

// --- Definições ---
#define CAPACIDADE_MAXIMA 10 
#define MAX_NOME 50

// --- Documentação da Estrutura ---
// Enumeração para definir os critérios de ordenação
typedef enum {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
} CriterioOrdenacao;

// Estrutura do Item (AGORA COM PRIORIDADE)
typedef struct {
    char nome[MAX_NOME];
    char tipo[30];
    int quantidade;
    int prioridade; // PRIORIDADE: de 1 a 5
} Item;

// --- Variáveis Globais de Controle ---
Item mochila[CAPACIDADE_MAXIMA]; 
int num_itens = 0;               
bool esta_ordenada_por_nome = false; // Flag para controle da Busca Binária

// --- Protótipos das Funções ---
void exibir_menu();
void adicionar_item();
void remover_item();
void listar_itens();
void menu_ordenacao();
void insertion_sort(CriterioOrdenacao criterio); // Função de ordenação
void buscar_binaria(); // Função de busca binária

// =================================================================
// FUNÇÃO PRINCIPAL
// =================================================================
int main() {
    int escolha;

    do {
        exibir_menu();
        printf("Sua escolha: ");
        if (scanf("%d", &escolha) != 1) {
            while (getchar() != '\n');
            escolha = 0; 
        }

        printf("\n");

        switch (escolha) {
            case 1:
                adicionar_item();
                break;
            case 2:
                remover_item();
                break;
            case 3:
                listar_itens();
                break;
            case 4:
                menu_ordenacao(); // Novo menu para ordenação
                break;
            case 5:
                buscar_binaria(); // Nova busca binária
                break;
            case 6:
                printf("✅ Saindo do sistema MateCheck. Sobreviva! 🫡\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha um número de 1 a 6.\n");
                break;
        }
        printf("\n-------------------------------------------------\n");
    } while (escolha != 6);

    return 0;
}

// =================================================================
// FUNÇÕES DE UTILIDADE
// =================================================================

// Função: exibir_menu (MODIFICADA)
void exibir_menu() {
    printf("\n👑 MOCHILA VIRTUAL - NÍVEL MESTRE 👑\n");
    printf("1. Adicionar item (com Prioridade)\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar a mochila (Nome, Tipo ou Prioridade)\n"); // NOVO
    printf("5. Buscar item por nome (Busca Binária)\n"); // NOVO
    printf("6. Sair\n");
}

// Função: adicionar_item (MODIFICADA)
// Inclui leitura da Prioridade e DESORDENA a flag.
void adicionar_item() {
    if (num_itens >= CAPACIDADE_MAXIMA) {
        printf("🚫 Mochila cheia! Capacidade máxima (%d) atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    Item novo_item;

    printf("--- Adicionar Novo Item ---\n");
    printf("Nome do Item: ");
    scanf("%49s", novo_item.nome); 

    printf("Tipo do Item: ");
    scanf("%29s", novo_item.tipo); 

    printf("Quantidade: ");
    if (scanf("%d", &novo_item.quantidade) != 1 || novo_item.quantidade <= 0) {
        printf("❌ Quantidade inválida. Falha na adição.\n");
        while (getchar() != '\n');
        return;
    }
    
    // NOVIDADE: Leitura da Prioridade
    printf("Prioridade (1 - Baixa, 5 - Alta): ");
    if (scanf("%d", &novo_item.prioridade) != 1 || novo_item.prioridade < 1 || novo_item.prioridade > 5) {
        printf("❌ Prioridade inválida (deve ser entre 1 e 5). Falha na adição.\n");
        while (getchar() != '\n');
        return;
    }

    mochila[num_itens] = novo_item;
    num_itens++; 
    
    // Se um item novo é adicionado, a ordem anterior (se existia) não é garantida
    esta_ordenada_por_nome = false; 

    printf("\n✅ Item '%s' adicionado com sucesso! (%d/%d)\n", novo_item.nome, num_itens, CAPACIDADE_MAXIMA);
}

// Função: remover_item (MANTIDA - mas desordena ao remover)
void remover_item() {
    // ... [código de remoção idêntico ao Aventureiro] ...
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nome_remover[50];
    printf("--- Remover Item ---\n");
    printf("Digite o nome do item a remover: ");
    scanf("%49s", nome_remover);

    int i, encontrado = 0;

    for (i = 0; i < num_itens; i++) {
        if (strcmp(mochila[i].nome, nome_remover) == 0) {
            encontrado = 1;
            break; 
        }
    }

    if (encontrado) {
        printf("✅ Item '%s' encontrado e removido.\n", nome_remover);

        for (int j = i; j < num_itens - 1; j++) {
            mochila[j] = mochila[j + 1];
        }

        num_itens--; 
        // A remoção pode quebrar a ordenação
        esta_ordenada_por_nome = false; 
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nome_remover);
    }
}

// Função: listar_itens (MODIFICADA para incluir Prioridade)
void listar_itens() {
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Não há itens para listar.\n");
        return;
    }

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", num_itens, CAPACIDADE_MAXIMA);
    
    // Novo cabeçalho
    printf("| %-20s | %-15s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("|----------------------|-----------------|------------|------------|\n");

    for (int i = 0; i < num_itens; i++) {
        printf("| %-20s | %-15s | %-10d | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade); // NOVO CAMPO
    }
    printf("|----------------------|-----------------|------------|------------|\n");
    
    // Informa o estado de ordenação para fins de teste
    printf("Status de Ordenação por Nome: %s\n", esta_ordenada_por_nome ? "ORDENADA" : "DESORDENADA");
}

// Função: menu_ordenacao (NOVA)
// Permite ao usuário escolher o critério de ordenação
void menu_ordenacao() {
    int escolha_criterio;
    printf("--- Menu de Ordenação ---\n");
    printf("1. Ordenar por Nome (A-Z)\n");
    printf("2. Ordenar por Tipo (A-Z)\n");
    printf("3. Ordenar por Prioridade (1-5)\n");
    printf("Escolha o criterio: ");

    if (scanf("%d", &escolha_criterio) != 1) {
        printf("❌ Opção inválida.\n");
        while (getchar() != '\n');
        return;
    }

    if (escolha_criterio >= 1 && escolha_criterio <= 3) {
        insertion_sort((CriterioOrdenacao)escolha_criterio);
    } else {
        printf("❌ Critério de ordenação inválido.\n");
    }
}


// Função: insertion_sort (NOVA)
// Implementa o Insertion Sort com contador de comparações.
void insertion_sort(CriterioOrdenacao criterio) {
    if (num_itens <= 1) {
        printf("ℹ️ A mochila tem 0 ou 1 item, já está ordenada.\n");
        esta_ordenada_por_nome = true; // Por ser trivialmente ordenada por nome
        return;
    }

    int i, j;
    Item chave;
    long long contador_comparacoes = 0; // Contador de desempenho

    for (i = 1; i < num_itens; i++) {
        chave = mochila[i];
        j = i - 1;

        // Loop de comparação e deslocamento
        while (j >= 0) {
            int comparacao = 0;

            // Determina a comparação com base no critério
            if (criterio == POR_NOME) {
                comparacao = strcmp(mochila[j].nome, chave.nome);
            } else if (criterio == POR_TIPO) {
                comparacao = strcmp(mochila[j].tipo, chave.tipo);
            } else if (criterio == POR_PRIORIDADE) {
                // Ordenação decrescente por prioridade (maior prioridade primeiro)
                if (mochila[j].prioridade < chave.prioridade) {
                    comparacao = 1; // Coloca a chave à frente (maior prioridade)
                } else {
                    comparacao = -1; // Mantém a ordem
                }
            }
            
            contador_comparacoes++; // Conta cada comparação

            // Condição para deslocamento (se o item em j for "maior" que a chave)
            // Para nome/tipo, comparacao > 0 significa que mochila[j] vem depois de 'chave'.
            // Para prioridade, comparacao > 0 significa que mochila[j] tem menor prioridade.
            if ((criterio != POR_PRIORIDADE && comparacao > 0) || 
                (criterio == POR_PRIORIDADE && comparacao > 0)) {
                
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break; // A posição correta foi encontrada
            }
        }
        mochila[j + 1] = chave; // Insere a chave na posição correta
    }

    printf("✅ Mochila ordenada com sucesso!\n");
    printf("📊 Comparações realizadas durante a ordenação: %lld\n", contador_comparacoes);

    // Atualiza a flag de ordenação APENAS se o critério for POR_NOME
    if (criterio == POR_NOME) {
        esta_ordenada_por_nome = true;
    } else {
        esta_ordenada_por_nome = false;
    }
}

// Função: buscar_binaria (NOVA)
// Implementa a Busca Binária, exige que a lista esteja ordenada por nome.
void buscar_binaria() {
    // 1. Validação de Pré-requisito
    if (!esta_ordenada_por_nome) {
        printf("🚫 ERRO: A Busca Binária exige que a mochila esteja ordenada por NOME.\n");
        printf("Por favor, selecione a opção 4 e ordene por Nome primeiro.\n");
        return;
    }

    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Não há itens para buscar.\n");
        return;
    }

    char nome_busca[MAX_NOME];
    printf("--- Busca Binária por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%49s", nome_busca);

    // 2. Lógica da Busca Binária
    int inicio = 0;
    int fim = num_itens - 1;
    int meio;
    int encontrado = 0;

    // A busca continua enquanto o limite inicial for menor ou igual ao final
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int comparacao = strcmp(mochila[meio].nome, nome_busca);

        if (comparacao == 0) {
            // Encontrado!
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            // Nome buscado é lexicograficamente maior que o item no meio
            // Procura na metade direita
            inicio = meio + 1;
        } else { // comparacao > 0
            // Nome buscado é lexicograficamente menor que o item no meio
            // Procura na metade esquerda
            fim = meio - 1;
        }
    }

    // 3. Exibição do Resultado
    if (encontrado) {
        printf("\n🎯 ITEM ENCONTRADO (Busca Binária)! 🎯\n");
        printf("Nome:       %s\n", mochila[meio].nome);
        printf("Tipo:       %s\n", mochila[meio].tipo);
        printf("Quantidade: %d\n", mochila[meio].quantidade);
        printf("Prioridade: %d\n", mochila[meio].prioridade);
    } else {
        printf("\n❌ Item '%s' não foi encontrado na mochila.\n", nome_busca);
    }
}