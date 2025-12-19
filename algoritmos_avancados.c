#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------ STRUCT PISTA -------------------------
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

//------------------ STRUCT SALA -------------------------------
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
    Pista* pistas;
} Sala;

//------------------ CRIAR PISTA -------------------------------
Pista* criarPista(char* texto) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

//------------------ INSERIR NA BST ----------------------------
Pista* inserirPista(Pista* raiz, char* texto) {
    if (raiz == NULL)
        return criarPista(texto);

    if (strcmp(texto, raiz->texto) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->direita = inserirPista(raiz->direita, texto);

    return raiz;
}

//------------------ EXIBIR EM ORDEM ---------------------------
void emOrdem(Pista* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        emOrdem(raiz->direita);
    }
}

//------------------ LISTAR PISTAS -----------------------------
void listarPista(Pista* pistas) {
    if (pistas == NULL) {
        printf("Nenhuma pista encontrada nesta sala.\n");
        return;
    }
    printf("Pistas coletadas:\n");
    emOrdem(pistas);
}

//------------------ CRIAR SALA --------------------------------
Sala* criarSala(char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    nova->pistas = NULL;
    return nova;
}

//------------------ EXPLORAR SALAS ----------------------------
void explorarSalas(Sala* salaAtual) {
    char escolha;

    printf("\nVocê está no(a): %s\n", salaAtual->nome);

    // 🔍 adiciona pista automaticamente ao visitar
    if (salaAtual->pistas == NULL) {
        if (strcmp(salaAtual->nome, "Biblioteca") == 0)
            salaAtual->pistas = inserirPista(salaAtual->pistas, "Um livro foi encontrado aberto.");
        else if (strcmp(salaAtual->nome, "Cozinha") == 0)
            salaAtual->pistas = inserirPista(salaAtual->pistas, "Um copo de suco foi deixado na mesa.");
        else if (strcmp(salaAtual->nome, "Sótão") == 0)
            salaAtual->pistas = inserirPista(salaAtual->pistas, "Um velho diário foi encontrado.");
    }

    if (salaAtual->esquerda)
        printf("(e) -> %s\n", salaAtual->esquerda->nome);
    if (salaAtual->direita)
        printf("(d) -> %s\n", salaAtual->direita->nome);

    printf("(p) -> Ver pistas\n");
    printf("(s) -> Sair\n");
    printf("Escolha: ");
    scanf(" %c", &escolha); // espaço antes do %c

    if (escolha == 'e' && salaAtual->esquerda)
        explorarSalas(salaAtual->esquerda);
    else if (escolha == 'd' && salaAtual->direita)
        explorarSalas(salaAtual->direita);
    else if (escolha == 'p') {
        listarPista(salaAtual->pistas);
        explorarSalas(salaAtual);
    }
    else if (escolha == 's') {
        printf("Você saiu da casa.\n");
        return;
    }
    else {
        printf("Opção inválida!\n");
        explorarSalas(salaAtual);
    }
}

//------------------ MAIN --------------------------------------
int main() {
    Sala* hall = criarSala("Hall de entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->direita = sotao;

    explorarSalas(hall);

    return 0;
}

    
    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().



