import std;

// Árvore binária encadeada
struct NoEnc {
    int v;      // dado armazenado
    NoEnc *esq; // filho esquerdo
    NoEnc *dir; // filho direito
    NoEnc *pai; // pai (opcional)

    int nivel(NoEnc *no, NoEnc *raiz);
    static int svalor(NoEnc *no);
};

struct ArvoreB {
    NoEnc *raiz; // raiz da árvore
    int N;       // número de nós

    void cria();
    int tamanho();
};

void ArvoreB::cria() {
    raiz = nullptr;
    N = 0;
}

int ArvoreB::tamanho() {
    return N;
}

int NoEnc::nivel(NoEnc *no, NoEnc *raiz) {
    if (!raiz)
        return 0;
    if (no == raiz)
        return 1;
    int esq = nivel(no, raiz->esq);
    if (esq != 0)
        return 1 + esq;
    int dir = nivel(no, raiz->dir);
    if (dir != 0)
        return 1 + dir;
    return 0; // nós em árvores distintas
}

int NoEnc::svalor(NoEnc *no) {
    if (!no)
        return 0; // árvore vazia
    int esq = svalor(no->esq);
    int dir = svalor(no->dir);
    return 1 + std::min(esq, dir);
}

// Ex 1
// Inserir em árvore binária completa
void insereBinCompleta(ArvoreB *arv, NoEnc *&raiz, int v, NoEnc *pai = nullptr) {
    if (!raiz) {
        raiz = new NoEnc{v, nullptr, nullptr, pai};
        arv->N++;
        return; // Ponto e vírgula corrigido
    }
    if (!raiz->esq) {
        return insereBinCompleta(arv, raiz->esq, v, raiz);
    }
    if (!raiz->dir) {
        return insereBinCompleta(arv, raiz->dir, v, raiz);
    }
    if (NoEnc::svalor(raiz->esq) <= NoEnc::svalor(raiz->dir)) {
        return insereBinCompleta(arv, raiz->esq, v, raiz);
    }
    return insereBinCompleta(arv, raiz->dir, v, raiz);
}

// Ex 1a
void preOrdem(NoEnc *no) {
    if (no) {
        std::println("{}", no->v);
        preOrdem(no->esq);
        preOrdem(no->dir);
    }
}

// Ex 1b
void emOrdem(NoEnc *no) {
    if (no) {
        emOrdem(no->esq);
        std::println("{}", no->v);
        emOrdem(no->dir);
    }
}

// Ex 1c
void posOrdem(NoEnc *no) {
    if (no) {
        posOrdem(no->esq);
        posOrdem(no->dir);
        std::println("{}", no->v);
    }
}

int main() {
    ArvoreB arvore;
    arvore.cria();

    // Inserindo elementos
    std::cout << "Montando a arvore binaria completa..." << std::endl;
    insereBinCompleta(&arvore, arvore.raiz, 10);
    insereBinCompleta(&arvore, arvore.raiz, 20);
    insereBinCompleta(&arvore, arvore.raiz, 15);
    insereBinCompleta(&arvore, arvore.raiz, 12);
    insereBinCompleta(&arvore, arvore.raiz, 8);
    insereBinCompleta(&arvore, arvore.raiz, 5);
    insereBinCompleta(&arvore, arvore.raiz, 7);
    insereBinCompleta(&arvore, arvore.raiz, 1);
    insereBinCompleta(&arvore, arvore.raiz, 2);

    // Ex 1a: Percurso de Pré-ordem
    std::println("\nPercurso de Pre-ordem");
    preOrdem(arvore.raiz);

    // Ex 1b: Percurso de Em-ordem
    std::println("\nPercurso de Em-ordem");
    emOrdem(arvore.raiz);

    // Ex 1c: Percurso de Pós-ordem
    std::println("\nPercurso de Pos-ordem");
    posOrdem(arvore.raiz);

    return 0;
}