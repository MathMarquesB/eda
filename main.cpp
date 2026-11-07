import std;

struct NoBin {
    char chave;
    NoBin *esq;
    NoBin *dir;
};

struct ArvBin {
    NoBin *raiz;
    int N;

    void cria();
    bool estritaBin(NoBin *no);
};

void ArvBin::cria() {
    raiz = nullptr;
    N = 0;
}

// Ex 1a
bool dois_ou_zero_filhos(NoBin *no) {
    return (!(no->esq || no->dir) || (no->esq && no->dir));
}

bool auxEstritaBin(NoBin *no, bool check) {
    if (no && no->esq)
        check *= auxEstritaBin(no->esq, check);
    if (no && no->dir)
        check *= auxEstritaBin(no->dir, check);
    return check * dois_ou_zero_filhos(no);
}

bool ArvBin::estritaBin(NoBin *no) {
    if (!no)
        return true;
    return auxEstritaBin(no, true);
}

// Ex 1b
int altura(NoBin *no) {
    if (!no)
        return 0;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    if (he > hd)
        return he + 1;
    else
        return hd + 1;
}

void auxEmNiveis(NoBin *no, int altura_atual, int altura_relativa) {
    if (altura_relativa == altura_atual)
        std::println("{}", no->chave);
    if (altura_relativa > altura_atual) {
        if (no->esq)
            auxEmNiveis(no->esq, altura_atual, altura_relativa - 1);
        if (no->dir)
            auxEmNiveis(no->dir, altura_atual, altura_relativa - 1);
    }
}

void emNiveis(NoBin *no) {
    if (!no)
        return;
    int altura_total = altura(no);
    int altura_atual = altura_total;
    int nivel = 1;
    while (altura_atual) {
        std::println("Nivel {}:", nivel);
        auxEmNiveis(no, altura_atual, altura_total);
        altura_atual--;
        nivel++;
    }
}

void insere(ArvBin *arv, NoBin *&raiz, char c) {
    if (!raiz) {
        raiz = new NoBin{c, nullptr, nullptr};
        arv->N++;
        return;
    }
    if (c <= raiz->chave)
        return insere(arv, raiz->esq, c);
    return insere(arv, raiz->dir, c);
}

void emOrdem(NoBin *no) {
    if (no) {
        emOrdem(no->esq);
        std::println("{}", no->chave);
        emOrdem(no->dir);
    }
}

int main() {
    ArvBin arv;
    arv.cria();

    // Cria árvore perfeita
    // insere(&arv, arv.raiz, 'D');
    // insere(&arv, arv.raiz, 'B');
    // insere(&arv, arv.raiz, 'A');
    // insere(&arv, arv.raiz, 'C');
    // insere(&arv, arv.raiz, 'F');
    // insere(&arv, arv.raiz, 'E');
    // insere(&arv, arv.raiz, 'G');

    insere(&arv, arv.raiz, 'D');
    insere(&arv, arv.raiz, 'B');
    insere(&arv, arv.raiz, 'A');
    insere(&arv, arv.raiz, 'C');
    insere(&arv, arv.raiz, 'F');
    insere(&arv, arv.raiz, 'E');
    insere(&arv, arv.raiz, 'G');
    insere(&arv, arv.raiz, 'X');
    insere(&arv, arv.raiz, 'Y');
    insere(&arv, arv.raiz, 'Z');

    std::println("Percurso da arvore em-ordem:");
    emOrdem(arv.raiz);

    // Ex 1a
    if (arv.estritaBin(arv.raiz))
        std::println("\nA arvore é estritamente binaria.");
    else
        std::println("\nA arvore não é estritamente binaria.");

    // Ex 1b
    std::println("\nPercurso na arvore em-niveis:");
    emNiveis(arv.raiz);

    return 0;
}