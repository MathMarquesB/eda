import std;

struct NoEnc {
    char chave;
    float valor;
    NoEnc *esq;
    NoEnc *dir;
    NoEnc *pai;
};

struct ArvAVL {
    NoEnc *raiz;
    int N;

    void cria();
    void aumenta();
    void insere(char chave, float valor, NoEnc *&no, NoEnc *pai);
};

void ArvAVL::cria() {
    raiz = nullptr;
    N = 0;
}

void ArvAVL::aumenta() {
    N++;
}

void ArvAVL::insere(char chave, float valor, NoEnc *&no, NoEnc *pai) {
    if (!no) {
        no = new NoEnc{chave, valor, nullptr, nullptr, pai};
        aumenta();
        return;
    }
    if (chave <= no->chave)
        return insere(chave, valor, no->esq, no);
    return insere(chave, valor, no->dir, no);
}

// Ex 9
int altura(NoEnc *no) {
    if (!no)
        return 0;
    int he = 0;
    int hd = 0;
    he += altura(no->esq);
    hd += altura(no->dir);
    return he > hd ? he + 1 : hd + 1;
}

int fator(NoEnc *no) {
    if (!no)
        return 0;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    return he - hd;
}

bool ehBalanceado(NoEnc *no) {
    int fb = fator(no);
    return fb > -2 && fb < 2;
}

// Ex 10
void qualRotacao(NoEnc *no) {
    if (!no)
        return;
    if (ehBalanceado(no))
        return;
    if (fator(no) <= -2) {
        if (fator(no->dir) <= 0)
            std::println("Simples a esquerda");
        else
            std::println("Dupla a esquerda");
    } else {
        if (fator(no->esq) >= 0)
            std::println("Simples a direita");
        else
            std::println("Dupla a direita");
    }
}

// Apenas para testes
// void verificaNo(NoEnc *no) {
//     if (!no)
//         return;
//     if (!ehBalanceado(no)) {
//         std::println("\nO no {} está desbalanceado e precisa da rotação:", no->chave);
//         qualRotacao(no);
//     }
//     verificaNo(no->esq);
//     verificaNo(no->dir);
// }

int main() {
    ArvAVL arv;
    arv.cria();

    // Cria árvore desbalanceada
    arv.insere('D', 10, arv.raiz, nullptr);
    arv.insere('B', 2, arv.raiz, nullptr);
    arv.insere('Y', 5, arv.raiz, nullptr);
    arv.insere('A', 3, arv.raiz, nullptr);
    arv.insere('G', 9, arv.raiz, nullptr);
    arv.insere('C', 8, arv.raiz, nullptr);
    arv.insere('F', 6, arv.raiz, nullptr);
    arv.insere('Z', 4, arv.raiz, nullptr);
    arv.insere('E', 1, arv.raiz, nullptr);
    arv.insere('X', 7, arv.raiz, nullptr);

    // Ex 9
    std::println("Altura da arvore: {}", altura(arv.raiz));

    std::println("Fator de balanceamento da raiz: {}", fator(arv.raiz));

    return 0;
}