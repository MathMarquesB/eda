import std;

struct NoBin {
    char chave;
    NoBin *esq;
    NoBin *dir;
};

struct ArvBB {
    NoBin *raiz;
    int N;

    void cria();
    void aumenta();
    void insere(char chave, NoBin *&no);
};

void ArvBB::cria() {
    raiz = nullptr;
    N = 0;
}

void ArvBB::aumenta() {
    N++;
}

// Ex 2
// Foi preciso modificar o tipo ponteiro (*) para referência do ponteiro (*&)
// Isso só é permitido no C++
// Permite alterar o ponteiro original de forma mais simples
void ArvBB::insere(char chave, NoBin *&no) {
    if (!no) {
        no = new NoBin{chave, nullptr, nullptr};
        aumenta();
        return;
    }
    if (chave <= no->chave)
        return insere(chave, no->esq);
    return insere(chave, no->dir);
}

// Ex 3
// Retorna A se a árvore estiver vazia (a função precisa retornar char)
char maior(NoBin *no) {
    if (!no)
        return 'A';
    if (no->dir)
        return maior(no->dir);
    return no->chave;
}

// Ex 4
// Retorna Z se a árvore estiver vazia (a função precisa retornar char)
char menor(NoBin *no) {
    if (!no)
        return 'Z';
    if (no->esq)
        return menor(no->esq);
    return no->chave;
}

// Ex 5
bool ehBinariaBusca(NoBin *no) {
    if (!no) // Árvore vazia
        return true;
    if (!(no->esq || no->dir)) // Folha
        return true;
    if (no->esq && no->esq->chave > no->chave) // Chave esquerda maior que o pai
        return false;
    if (no->dir && no->dir->chave < no->chave) // Chave direita menor que o pai
        return false;
    bool check = true;
    // Qualquer valor vezes falso é falso
    if (no->esq)
        check *= ehBinariaBusca(no->esq);
    if (no->dir)
        check *= ehBinariaBusca(no->dir);
    return check;
}

// Ex 6
char busca(char chave, NoBin *no) {
    if (!no)
        return '\0';
    if (chave < no->chave)
        return busca(chave, no->esq);
    if (chave > no->chave)
        return busca(chave, no->dir);
    return no->chave;
}

// Ex 7
char auxAnterior(char chave, NoBin *no, char candidato) {
    if (chave < no->chave) // Elemento menor que atual
        return auxAnterior(chave, no->esq, candidato);
    if (chave > no->chave) // Elemento maior que atual
        return auxAnterior(chave, no->dir, no->chave);
    // Elemento encontrado
    if (no->esq)
        return maior(no->esq);
    return candidato;
}

char anterior(char chave, NoBin *no) {
    if (!no) // Árvore vazia
        return '\0';
    if (!busca(chave, no)) // Elemento não encontrado
        return '\0';
    return auxAnterior(chave, no, '\0');
}

// Ex 8
char auxPosterior(char chave, NoBin *no, char candidato) {
    if (chave < no->chave) // Elemento menor que atual
        return auxPosterior(chave, no->esq, no->chave);
    if (chave > no->chave) // Elemento maior que atual
        return auxPosterior(chave, no->dir, candidato);
    // Elemento encontrado
    if (no->dir)
        return menor(no->dir);
    return candidato;
}

char posterior(char chave, NoBin *no) {
    if (!no) // Árvore vazia
        return '\0';
    if (!busca(chave, no)) // Elemento não encontrado
        return '\0';
    return auxPosterior(chave, no, '\0');
}

// Impressão
void emOrdem(NoBin *no) {
    if (no) {
        emOrdem(no->esq);
        std::println("{}", no->chave);
        emOrdem(no->dir);
    }
}

// Bônus
NoBin *noMenor(NoBin *no) {
    if (no->esq)
        return noMenor(no->esq);
    return no;
}

void remove(char chave, NoBin *&no) {
    if (!no)
        return;
    if (chave < no->chave) {
        remove(chave, no->esq);
    } else if (chave > no->chave) {
        remove(chave, no->dir);
    } else {
        if (!no->esq) {
            NoBin *tmp = no;
            no = no->dir;
            delete tmp;
        } else if (!no->dir) {
            NoBin *tmp = no;
            no = no->esq;
            delete tmp;
        } else {
            NoBin *tmp = noMenor(no->dir);
            no->chave = tmp->chave;
            remove(tmp->chave, no->dir);
        }
    }
}

int main() {
    ArvBB arv;
    arv.cria();

    // Cria árvore perfeita
    // insere(&arv, arv.raiz, 'D');
    // insere(&arv, arv.raiz, 'B');
    // insere(&arv, arv.raiz, 'A');
    // insere(&arv, arv.raiz, 'C');
    // insere(&arv, arv.raiz, 'F');
    // insere(&arv, arv.raiz, 'E');
    // insere(&arv, arv.raiz, 'G');

    arv.insere('D', arv.raiz);
    arv.insere('B', arv.raiz);
    arv.insere('A', arv.raiz);
    arv.insere('C', arv.raiz);
    arv.insere('F', arv.raiz);
    arv.insere('E', arv.raiz);
    arv.insere('G', arv.raiz);
    arv.insere('X', arv.raiz);
    arv.insere('Y', arv.raiz);
    arv.insere('Z', arv.raiz);

    // Cria ávore para buscar antecessor e sucessor
    // Testes recomendados:
    // 1. Buscar antecessor de J
    // 2. Buscar antecessor de J sem inserir I
    // 3. Buscar antecessor de H
    // 4. Buscar sucessor de N
    // arv.insere('L', arv.raiz);
    // arv.insere('H', arv.raiz);
    // arv.insere('K', arv.raiz);
    // arv.insere('J', arv.raiz);
    // arv.insere('I', arv.raiz);
    // arv.insere('N', arv.raiz);
    // arv.insere('T', arv.raiz);
    // arv.insere('P', arv.raiz);
    // arv.insere('O', arv.raiz);

    std::println("Percurso da arvore em-ordem:");
    emOrdem(arv.raiz);

    // Ex 3
    std::println("\nMaior elemento da árvore: {}", maior(arv.raiz));

    // Ex 4
    std::println("\nMenor elemento da árvore: {}", menor(arv.raiz));

    // Ex 5
    if (ehBinariaBusca(arv.raiz))
        std::println("\nA arvore é binária de busca.");
    else
        std::println("\nA arvore não é binária de busca.");

    // Ex 6
    char elem_buscado = 'K';
    std::println("\nBuscando elemento {}...", elem_buscado);
    char elem_encontrado = busca(elem_buscado, arv.raiz);
    if (elem_encontrado)
        std::println("Elemento encontrado: {}", elem_encontrado);
    else
        std::println("Elemento não encontrado.");

    // Ex 7
    elem_buscado = 'H';
    std::println("\nBuscando elemento {}...", elem_buscado);
    elem_encontrado = anterior(elem_buscado, arv.raiz);
    if (elem_encontrado)
        std::println("Elemento anterior: {}", elem_encontrado);
    else
        std::println("Elemento anterior não encontrado.");

    // Ex 8
    elem_buscado = 'N';
    std::println("\nBuscando elemento {}...", elem_buscado);
    elem_encontrado = posterior(elem_buscado, arv.raiz);
    if (elem_encontrado)
        std::println("Elemento posterior: {}", elem_encontrado);
    else
        std::println("Elemento posterior não encontrado.");

    return 0;
}