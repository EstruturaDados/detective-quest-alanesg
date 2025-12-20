#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------- TAMANHO DO HASH--------------- 

#define TAM_HASH 10

//------------------ STRUCT PISTA -------------------------
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

//--------------------STRUCT LISTA DE PISTAS ---------------
typedef struct listaPista {
    char texto[100];
    struct listaPista* prox;
} listaPista;

//---------------------STRUCT SUSPEITO (hash) --------------------------
typedef struct Suspeito {
 char nome [50];
 int contador;
 listaPista* pistas;
 struct Suspeito* prox; //colisão
} Suspeito;

//------------------ STRUCT SALA -------------------------------
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
    Pista* pistas;
} Sala;

//----------------------HASH---------------------------------
Suspeito* tabelaHash[TAM_HASH];

//----------------------- FUNÇÃO HASH------------------------
int funcaoHash(char* nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++)
    soma += nome[i];
    return soma % TAM_HASH;
}
//----------------------- INICIANDO HASH------------------------
void iniciarHash() {
    for(int i = 0; i < TAM_HASH; i++)
    tabelaHash[i]= NULL;
}

//------------------ BUSCAR SUSPEITO-----------------------------
Suspeito* buscarSuspeito(char* nome) {
    int idx = funcaoHash(nome);
    Suspeito* atual = tabelaHash[idx];

    while(atual) {
        if (strcmp(atual->nome, nome) == 0)
        return atual;
        atual = atual -> prox;
    }
    return NULL;
}
//---------------------- ADICIONAR PISTA NA LISTA --------------
void adicionarPistaLista(listaPista** lista, char* texto) {
    listaPista* nova = malloc(sizeof(listaPista));
    strcpy(nova->texto, texto);
    nova->prox = *lista;
    *lista = nova;
}

//---------------------- INSERIR HASH ----------------------------
void inserirHash(char* nomeSuspeito, char* pista) {
    int idx = funcaoHash(nomeSuspeito);
    Suspeito* s =buscarSuspeito(nomeSuspeito);
    if(!s) {
        s = malloc(sizeof(Suspeito));
        strcpy(s->nome, nomeSuspeito);
        s-> contador = 0;
        s-> pistas = NULL;
        s->prox = tabelaHash[idx];
        tabelaHash[idx] = s;
    }
    adicionarPistaLista(&s->pistas, pista);
    s->contador++;
}

//--------------------- LISTANDO ASSOCIAÇÕES----------------------
void listarAssociacoes() {
    for(int i = 0; i< TAM_HASH; i++) {
        Suspeito* s = tabelaHash[i];
        
        while(s) {
            printf("\nSuspeito: %s (%d pistas)\n", s->nome, s->contador);
            listaPista* p = s-> pistas;
            while(p) {
                printf(" - %s\n", p->texto);
                p = p->prox;           
            }
               s = s->prox;
        }
    }
}

//-------------------- SUSPEITO PROVÁVEL-----------------------
void suspeitoMaisProvavel() {
    Suspeito* melhor = NULL;
    for(int i = 0; i < TAM_HASH; i++) {
        Suspeito* s = tabelaHash[i];
        while(s) {
            if(!melhor || s->contador > melhor->contador)
            melhor = s;
            s = s->prox;
        }
    } 
    if(melhor) 
        printf("\nSuspeito mais provável: %s (%d pista)\n",
             melhor->nome, melhor->contador);
    
}
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

//------------------ CRIAR SALA --------------------------------
Sala* criarSala(char* nome) {
    Sala* s = malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    s->esquerda = s->direita = NULL;
    s->pistas = NULL;
    return s;
}

//------------------ EXPLORAR SALAS ----------------------------
void explorarSalas(Sala* sala) {
    char op;

    printf("\nVocê está no(a): %s\n .", sala->nome);

    // 🔍 adiciona pista automaticamente ao visitar
    if (!sala->pistas) {
        if (strcmp(sala->nome, "Biblioteca") == 0) {
            sala->pistas = inserirPista(sala->pistas, "Um livro foi encontrado.");
            inserirHash("Carlos", "Um livro foi encontrado.");
    }
        else if (strcmp(sala->nome, "Cozinha") == 0) {
            sala->pistas = inserirPista(sala->pistas, "Um copo com impressões digitais.");
            inserirHash("Marta", "Um copo com impressões digitais.");
    }
        else if (strcmp(sala->nome, "Sótão") == 0){
            sala->pistas = inserirPista(sala->pistas, "Diário escondido no baú.");
            inserirHash("Carlos", "Diário escondido no baú.");
    }
}

    if (sala->esquerda)
        printf("(e) -> %s\n", sala->esquerda->nome);
    if (sala->direita)
        printf("(d) -> %s\n", sala->direita->nome);

     printf("(p) Ver pistas\n(s) Sair\nEscolha: ");
    scanf(" %c", &op);
 

    if (op == 'e' && sala->esquerda) {
        explorarSalas(sala->esquerda);
    }
    else if (op == 'd' && sala->direita){
        explorarSalas(sala->direita);
    }
    else if (op == 'p') {
        emOrdem(sala->pistas);
        explorarSalas(sala);
    } 
     else if (op == 's') {
        printf("Você saiu da casa.\n");
        return;
    }
}
   


//------------------ MAIN --------------------------------------
int main() {
    iniciarHash();

    printf("--------MAPA DA MANSÃO--------\n");
    Sala* hall = criarSala("Hall de entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->direita = sotao;

    explorarSalas(hall);
    listarAssociacoes();
    suspeitoMaisProvavel();
    
    return 0;
}


