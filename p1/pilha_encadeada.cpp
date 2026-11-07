// Pilha encadeada
// O limite é a memória do computador

import std;

// Estrutura auxiliar para a pilha
// Cada nó guarda um dado e o ponteiro para o próximo
// A pilha guarda apenas o ponteiro para o primeiro nó (último a ser adicionado)
struct NoPilha1 {
    char dado;
    NoPilha1* prox;
};

struct PilhaEnc1 {
    NoPilha1* inicio;
    int N;
    void cria();
    void libera();
    char topo();
    void empilha(char dado);
    char desempilha();
    int tamanho();
};

void PilhaEnc1::cria() {
    N = 0; // zero elementos na pilha
    inicio = 0; // endereço zero de memória
}

void PilhaEnc1::libera() {
    while (inicio) {
        desempilha();
    }
}

char PilhaEnc1::topo() {
    return inicio->dado;
}

void PilhaEnc1::empilha(char dado) {
    // Alocação dinâmica no Heap com 'new'
    NoPilha1* no = new NoPilha1{.dado = dado, .prox = inicio};
    inicio = no;
    N++;
}

char PilhaEnc1::desempilha() {
    NoPilha1* no = inicio->prox;
    char r = inicio->dado;
    delete inicio;
    inicio = no;
    N--;
    return r;
}

int PilhaEnc1::tamanho() {
    return N;
}

int main() {
    PilhaEnc1 p;
    p.cria();

    p.empilha('A');
    std::println("Início da pilha: {} | Tamanho da pilha: {}", p.topo(), p.tamanho());
    p.empilha('B');
    std::println("Início da pilha: {} | Tamanho da pilha: {}", p.topo(), p.tamanho());
    char t = p.desempilha();
    std::println("Retirado: {} | Novo topo da pilha: {}", t, p.topo());

    p.libera();
    std::println("Removendo todos os elementos da pilha...");
    std::println("Tamanho da pilha: {}", p.tamanho());

    /*
    Uso de pilha pronta
    std::stack<char> p; // pilha de char
    p.push('A');
    p.push('B');
    println("{}", p.top()); // imprime B
    p.pop();
    println("{}", p.top()); // imprime A
    */

    return 0;
}