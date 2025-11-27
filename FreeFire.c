#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
// --- Documentação da Estrutura ---
// Define a estrutura para um item na mochila
#define CAPACIDADE_MAXIMA 10 // Capacidade máxima da mochila

typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

// --- Variáveis Globais de Controle ---
Item mochila[CAPACIDADE_MAXIMA]; // A array estática que representa a mochila
int num_itens = 0;               // Contador de itens atualmente na mochila

// --- Protótipos das Funções ---
void exibir_menu();
void adicionar_item();
void remover_item();
void listar_itens();

// =================================================================
// FUNÇÃO PRINCIPAL
// =================================================================
int main() {
    int escolha;

    // Loop do-while para o menu interativo
    do {
        exibir_menu();
        printf("Sua escolha: ");
        // Leitura da escolha do usuário
        if (scanf("%d", &escolha) != 1) {
            // Limpa o buffer de entrada em caso de erro (ex: usuário digitou texto)
            while (getchar() != '\n');
            escolha = 0; // Garante que a escolha será tratada como inválida
        }

        printf("\n");

        // Estrutura switch para lidar com a escolha do usuário
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
                printf("✅ Saindo do sistema MateCheck. Sobreviva! 🫡\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha um número de 1 a 4.\n");
                break;
        }
        printf("\n-------------------------------------------------\n");
    } while (escolha != 4);

    return 0;
}

// =================================================================
// FUNÇÕES DE UTILIDADE
// =================================================================

// Função: exibir_menu
// Descrição: Exibe as opções disponíveis para o usuário.
void exibir_menu() {
    printf("\n🎒 MOCHILA VIRTUAL - NÍVEL NOVATO 🎒\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar todos os itens\n");
    printf("4. Sair\n");
}

// Função: adicionar_item
// Descrição: Permite ao usuário inserir um novo item na mochila.
// Instruções: Verifica se há espaço antes de adicionar.
void adicionar_item() {
    // 1. Verificação de Capacidade
    if (num_itens >= CAPACIDADE_MAXIMA) {
        printf("🚫 Mochila cheia! Capacidade máxima (%d) atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    // 2. Coleta de Dados
    Item novo_item;

    printf("--- Adicionar Novo Item ---\n");
    printf("Nome do Item (sem espacos): ");
    scanf("%49s", novo_item.nome); // Limita a leitura para evitar estouro de buffer

    printf("Tipo do Item (Ex: Cura, Munição, Vestuário): ");
    scanf("%29s", novo_item.tipo); // Limita a leitura

    printf("Quantidade: ");
    while (scanf("%d", &novo_item.quantidade) != 1 || novo_item.quantidade <= 0) {
        printf("❌ Quantidade inválida. Digite um número inteiro positivo: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    // 3. Inserção na Array
    mochila[num_itens] = novo_item;
    num_itens++; // Incrementa o contador de itens

    printf("\n✅ Item '%s' adicionado com sucesso! (%d/%d)\n", novo_item.nome, num_itens, CAPACIDADE_MAXIMA);
}

// Função: remover_item
// Descrição: Remove um item da mochila pelo nome fornecido.
// Instruções: Usa um loop para encontrar o item. Se encontrado, move os itens subsequentes para preencher o espaço.
void remover_item() {
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nome_remover[50];
    printf("--- Remover Item ---\n");
    printf("Digite o nome do item a remover: ");
    scanf("%49s", nome_remover);

    int i, encontrado = 0;

    // 1. Busca Sequencial
    for (i = 0; i < num_itens; i++) {
        // Usa strcmp para comparação de strings (0 significa que são iguais)
        if (strcmp(mochila[i].nome, nome_remover) == 0) {
            encontrado = 1;
            break; // Encontrou o item na posição 'i'
        }
    }

    // 2. Remoção
    if (encontrado) {
        printf("✅ Item '%s' encontrado e removido.\n", nome_remover);

        // Desloca todos os itens após a posição 'i' para trás (i+1 -> i)
        for (int j = i; j < num_itens - 1; j++) {
            // Cópia do item j+1 para a posição j
            mochila[j] = mochila[j + 1];
        }

        num_itens--; // Decrementa o contador de itens
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nome_remover);
    }
}

// Função: listar_itens
// Descrição: Imprime todos os itens atualmente armazenados na mochila.
void listar_itens() {
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Não há itens para listar.\n");
        return;
    }

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", num_itens, CAPACIDADE_MAXIMA);
    
    // Configuração do cabeçalho da tabela
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("|----------------------|-----------------|------------|\n");

    // Impressão dos dados
    for (int i = 0; i < num_itens; i++) {
        printf("| %-20s | %-15s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("|----------------------|-----------------|------------|\n");
}