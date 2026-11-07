import std;

// Árvore Binária de Busca
struct NoEnc {
    char chave; // dado armazenado
    NoEnc *esq; // filho esquerdo
    NoEnc *dir; // filho direito
    NoEnc *pai; // pai (opcional)
};

struct ABB {
    NoEnc *raiz; // raiz da árvore
    int N;       // número de nós

    NoEnc *buscaABB(NoEnc *no, char c);
    NoEnc *minimo(NoEnc *const no);
    NoEnc *sucessor(NoEnc *const no);
    std::tuple<bool, NoEnc *> removeABB(char c, NoEnc *raiz);
    bool eh_filho_direito(NoEnc *f);
    bool eh_filho_esquerdo(NoEnc *f);
    bool tem_dois_filhos(NoEnc *no);
    std::tuple<NoEnc *, NoEnc *> extrai(NoEnc *const no);
};

// Operações básicas

// Busca
NoEnc *ABB::buscaABB(NoEnc *no, char c) {
    if (!no)
        return no; // chave não encontrada
    if (no->chave == c)
        return no; // chave encontrada
    if (c < no->chave)
        return buscaABB(no->esq, c); // recursão esquerda
    else
        return buscaABB(no->dir, c); // recursão direita
}

// É filho direito/esquerdo
bool ABB::eh_filho_direito(NoEnc *f) {
    return f == f->pai->dir;
}

bool ABB::eh_filho_esquerdo(NoEnc *f) {
    return f == f->pai->esq;
}

// Tem dois filhos
bool ABB::tem_dois_filhos(NoEnc *no) {
    return no->esq && no->dir;
}

// Extrair
std::tuple<NoEnc *, NoEnc *> ABB::extrai(NoEnc *const no) {
    auto *filho = no->esq ? no->esq : no->dir;
    auto *pai = no->pai;

    if (filho)
        filho->pai = pai;

    if (pai) {
        if (ABB::eh_filho_esquerdo(no))
            pai->esq = filho;
        else
            pai->dir = filho;
    }

    no->pai = no->esq = no->dir = nullptr;
    return std::tuple{pai, filho};
}

// Menor elemento
NoEnc *ABB::minimo(NoEnc *const no) {
    auto *atual = no;
    while (atual->esq)
        atual = atual->esq;
    return atual;
}

// Sucessor
NoEnc *ABB::sucessor(NoEnc *const no) {
    if (no->dir)
        return ABB::minimo(no->dir);

    auto *atual = no;
    auto *suc = atual->pai;

    while (suc && ABB::eh_filho_direito(atual)) {
        atual = suc;
        suc = atual->pai;
    }

    return suc;
}

// Remoção
std::tuple<bool, NoEnc *> ABB::removeABB(char c, NoEnc *raiz) {
    if (!raiz)
        return {false, raiz}; // raiz inalterada

    auto *no = ABB::buscaABB(raiz, c);
    if (!no)
        return {false, raiz};

    if (ABB::tem_dois_filhos(no)) {
        auto *removido = sucessor(no); // 'removido' sempre existe: minimo(no->dir)
        ABB::extrai(removido);         // 'removido' não tem filho esquerdo!
        no->chave = removido->chave;
        delete removido;
        return {true, raiz}; // raiz inalterada
    } else {
        auto [pai, filho] = ABB::extrai(no); // 'no' tem no máximo um filho
        delete no;
        if (!pai)
            return {true, filho}; // 'no' era raiz, 'filho' é nova raiz
        return {true, raiz};      // raiz inalterada
    }
}

// Função auxiliar simples para montar a árvore no teste
void inserir(NoEnc *&raiz, char c, NoEnc *pai = nullptr) {
    if (!raiz) {
        raiz = new NoEnc{c, nullptr, nullptr, pai};
        return;
    }

    if (c < raiz->chave) {
        inserir(raiz->esq, c, raiz);
    } else if (c > raiz->chave) {
        inserir(raiz->dir, c, raiz);
    }
}

int main() {
    return 0;
}