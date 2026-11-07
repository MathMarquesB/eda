import std;

// Árvore binária encadeada
struct NoEnc5 {
    char chave;  // dado armazenado
    NoEnc5 *esq; // filho esquerdo
    NoEnc5 *dir; // filho direito
    NoEnc5 *pai; // pai (opcional)
};

struct ArvoreEnc5 {
    NoEnc5 *raiz; // raiz da árvore
};

// Percursos
// Pré-ordem
void preordem(auto *no) {
    if (no) {
        // operação ou "visita"
        println("{}", no->chave);
        preordem(no->esq);
        preordem(no->dir);
    }
}

// Pós-ordem
void posordem(auto *no) {
    if (no) {
        posordem(no->esq);
        posordem(no->dir);
        // operação ou "visita"
        println("{}", no->chave);
    }
}

// Em-ordem (ordem simétrica)
void emordem(auto *no) {
    if (no) {
        emordem(no->esq);
        // operação ou "visita"
        println("{}", no->chave);
        emordem(no->dir);
    }
}

// Operações básicas
// Altura
int altura(auto *const no) {
    if (!no)
        return 0;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    if (he > hd)
        return he + 1;
    else
        return hd + 1;
}

// Nível
int nivel(auto *no, auto *raiz) {
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

// S-valor
int svalor(auto *no) {
    if (!no)
        return 0; // árvore vazia
    int esq = svalor(no->esq);
    int dir = svalor(no->dir);
    return 1 + std::min(esq, dir);
}

// É filho direito
// pre(f && f->pai) // C++26
bool eh_filho_direito(auto *f) {
    return f == f->pai->dir;
}

bool eh_filho_esquerdo(auto *f) {
    return f == f->pai->esq;
}

// Verifica se é folha ou semifolha
// pre(no) // C++26
bool tem_zero_filhos(auto *const no) {
    return !no->esq && !no->dir;
}

// pre(no) // C++26
bool tem_um_ou_zero_filhos(auto *const no) {
    return !no->esq || !no->dir;
}

// Extrair um nó que tem no máximo um filho
// pre(tem_um_ou_zero_filhos(no)) // C++26
// post(tem_zero_filhos(no)) // C++26
auto extrai(auto *const no) {
    auto *filho = no->esq ? no->esq : no->dir;
    auto *pai = no->pai;
    if (filho)
        filho->pai = pai;
    if (pai) {
        if (eh_filho_esquerdo(no))
            pai->esq = filho;
        else
            pai->dir = filho;
    }
    no->pai = no->esq = no->dir = 0;
    return std::tuple{pai, filho};
}

int main() {
    return 0;
}