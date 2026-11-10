import std;

struct No {
    int valor;
    No *esq;
    No *dir;
};

struct Arvore {
    No *raiz;

    void cria();
    void insereBin(No *&no, int valor);
};

void Arvore::cria() {
    raiz = nullptr;
}

void Arvore::insereBin(No *&no, int valor) {
    if (!no) {
        no = new No(valor, nullptr, nullptr);
        return;
    }
    if (valor <= no->valor)
        return insereBin(no->esq, valor);
    return insereBin(no->dir, valor);
}

// Ex 3a
int somaFolhas(No *no) {
    if (!no)
        return 0;
    int soma = 0;
    soma += somaFolhas(no->esq);
    soma += somaFolhas(no->dir);
    if (!(no->esq || no->dir))
        return no->valor;
    return soma;
}

// Ex 3b
void posOrdem(No *no) {
    if (no) {
        posOrdem(no->esq);
        posOrdem(no->dir);
        std::println("{}", no->valor);
    }
}

// Ex 3c
void emOrdem(No *no) {
    if (no) {
        emOrdem(no->esq);
        std::println("{}", no->valor);
        emOrdem(no->dir);
    }
}

// Ex 3d
void preOrdem(No *no) {
    if (no) {
        std::println("{}", no->valor);
        preOrdem(no->esq);
        preOrdem(no->dir);
    }
}

// Ex 3e
int maior(int he, int hd) {
    return he > hd ? he : hd;
}

int altura(No *no) {
    if (!no)
        return 0;
    int he = 0;
    int hd = 0;
    he += altura(no->esq);
    hd += altura(no->dir);
    return 1 + maior(he, hd);
}

// Ex 3f
int fator(No *no) {
    if (!no)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

// Ex 3g
void emNiveisAux(No *no, int altura_total, int altura_relativa) {
    if (!no)
        return;
    if (altura_total == altura_relativa) {
        std::println("{}", no->valor);
        return;
    }
    emNiveisAux(no->esq, altura_total, altura_relativa - 1);
    emNiveisAux(no->dir, altura_total, altura_relativa - 1);
}

void emNiveis(No *no) {
    if (!no)
        return;
    int altura_total = altura(no);
    int altura_relativa = altura_total;
    int nivel = 1;
    while (altura_total) {
        std::println("Nivel {}:", nivel);
        emNiveisAux(no, altura_total, altura_relativa);
        altura_total--;
        nivel++;
    }
}

int multiplicaNos(No *no) {
    if (!no)
        return 0;
    int p = no->valor;
    if (no->esq)
        p *= multiplicaNos(no->esq);
    if (no->dir)
        p *= multiplicaNos(no->dir);
    return p;
}

int main() {
    Arvore arv;
    arv.cria();

    arv.insereBin(arv.raiz, 5);
    arv.insereBin(arv.raiz, 7);
    arv.insereBin(arv.raiz, 1);
    arv.insereBin(arv.raiz, 3);
    arv.insereBin(arv.raiz, 6);
    arv.insereBin(arv.raiz, 9);
    arv.insereBin(arv.raiz, 4);
    arv.insereBin(arv.raiz, 15);
    arv.insereBin(arv.raiz, 8);
    arv.insereBin(arv.raiz, 12);
    arv.insereBin(arv.raiz, 2);

    // Impressão do percurso em-ordem
    emOrdem(arv.raiz);

    // Ex 3a
    std::println("\nSoma das folhas: {}", somaFolhas(arv.raiz));

    // Ex 3e
    std::println("\nAltura da arvore: {}", altura(arv.raiz));

    // Ex 3f
    std::println("\nFator de balanceamento da raiz: {}", fator(arv.raiz));

    // Ex 3g
    std::println("\nArvore em niveis:");
    emNiveis(arv.raiz);

    // Ex 3h
    std::println("\nProduto dos nós: {}", multiplicaNos(arv.raiz));

    return 0;
}