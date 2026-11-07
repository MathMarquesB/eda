import std;

struct NoBin {
    char chave;
    NoBin *esq;
    NoBin *dir;
};

struct ArvBin {
    NoBin raiz;
    int N;

    void cria();
}

void ArvBin::cria() {
    raiz = nullptr;
    N = 0;
}

void insere(ArvBin *arv, NoBin *&raiz, char c) {
    if (!raiz) {
        raiz = new NoBin{c, nullptr, nullptr};
        arv->N++;
        return;
    }
    if (c <= arv->chave)
        return insere(arv, arv->esq, c);
    return insere(arv, arv->dir, c);
}

int main() {
    ArvBin arv;
    arv.cria();

    insere(&arv, arv.raiz, 'A');
    insere(&arv, arv.raiz, 'B');
    insere(&arv, arv.raiz, 'C');
    insere(&arv, arv.raiz, 'D');
    insere(&arv, arv.raiz, 'E');

    return 0;
}