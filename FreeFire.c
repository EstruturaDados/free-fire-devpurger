#include <stdio.h>
#include <string.h> // Essencial para strcmp

// --- Definições ---
#define CAPACIDADE_MAXIMA 10 

// --- Estrutura do Item ---
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

// --- Variáveis Globais de Controle ---
Item mochila[CAPACIDADE_MAXIMA]; 
int num_itens = 0;               

// --- Protótipos das Funções ---
void exibir_menu();
void adicionar_item();
void remover_item();
void listar_itens();
void buscar_item_por_nome(); // Nova função de busca

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
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n');
            escolha = 0; 
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
                // Nova opção: Buscar item
                buscar_item_por_nome();
                break;
            case 5:
                printf("✅ Saindo do sistema MateCheck. Sobreviva! 🫡\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha um número de 1 a 5.\n");
                break;
        }
        printf("\n-------------------------------------------------\n");
    } while (escolha != 5);

    return 0;
}

// =================================================================
// FUNÇÕES DE UTILIDADE
// =================================================================

// Função: exibir_menu (MODIFICADA)
// Descrição: Inclui a nova opção de Busca.
void exibir_menu() {
    printf("\n🎒 MOCHILA VIRTUAL - NÍVEL AVENTUREIRO 🎒\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n"); // NOVA OPÇÃO
    printf("5. Sair\n");
}

// Função: adicionar_item (MANTIDA)
void adicionar_item() {
    if (num_itens >= CAPACIDADE_MAXIMA) {
        printf("🚫 Mochila cheia! Capacidade máxima (%d) atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    Item novo_item;

    printf("--- Adicionar Novo Item ---\n");
    printf("Nome do Item (sem espacos): ");
    scanf("%49s", novo_item.nome); 

    printf("Tipo do Item (Ex: Cura, Munição, Vestuário): ");
    scanf("%29s", novo_item.tipo); 

    printf("Quantidade: ");
    while (scanf("%d", &novo_item.quantidade) != 1 || novo_item.quantidade <= 0) {
        printf("❌ Quantidade inválida. Digite um número inteiro positivo: ");
        while (getchar() != '\n'); 
    }

    mochila[num_itens] = novo_item;
    num_itens++; 

    printf("\n✅ Item '%s' adicionado com sucesso! (%d/%d)\n", novo_item.nome, num_itens, CAPACIDADE_MAXIMA);
}

// Função: remover_item (MANTIDA)
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
        // strcmp: 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nome_remover) == 0) {
            encontrado = 1;
            break; // Encontrou o item na posição 'i'
        }
    }

    // 2. Remoção (Deslocamento)
    if (encontrado) {
        printf("✅ Item '%s' encontrado e removido.\n", nome_remover);

        // Desloca todos os itens subsequentes
        for (int j = i; j < num_itens - 1; j++) {
            mochila[j] = mochila[j + 1];
        }

        num_itens--; 
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nome_remover);
    }
}

// Função: listar_itens (MANTIDA)
void listar_itens() {
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Não há itens para listar.\n");
        return;
    }

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", num_itens, CAPACIDADE_MAXIMA);
    
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("|----------------------|-----------------|------------|\n");

    for (int i = 0; i < num_itens; i++) {
        printf("| %-20s | %-15s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("|----------------------|-----------------|------------|\n");
}

// Função: buscar_item_por_nome (NOVA)
// Descrição: Implementa a busca sequencial para encontrar e exibir um item.
void buscar_item_por_nome() {
    if (num_itens == 0) {
        printf("ℹ️ A mochila está vazia. Não há itens para buscar.\n");
        return;
    }

    char nome_busca[50];
    printf("--- Buscar Item por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%49s", nome_busca);

    int encontrado = 0; // Flag para controlar se o item foi encontrado
    int i;

    // A lógica de busca sequencial é simples: percorre a lista inteira
    for (i = 0; i < num_itens; i++) {
        // Compara a string de busca com o nome do item atual
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            encontrado = 1; // Item encontrado!
            break; // Interrompe o loop imediatamente
        }
    }

    // Exibe o resultado com base na flag 'encontrado'
    if (encontrado) {
        printf("\n✨ ITEM ENCONTRADO! ✨\n");
        printf("Nome:       %s\n", mochila[i].nome);
        printf("Tipo:       %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    } else {
        printf("\n❌ Item '%s' não foi encontrado na mochila.\n", nome_busca);
    }
}