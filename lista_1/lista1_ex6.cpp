// Lista 2

import std;
#include <cassert>

constexpr int N = 10;

// Ex 6
// Criar uma implementação do TAD Pilha para o tipo 'int', chamada PilhaMin, que oferece os métodos do TAD (em tempos constantes) e também o método obterMinimo(), que retorna o menor elemento da pilha. O método obterMinimo() também deve operar em tempo constante.

struct PilhaMin {
    int tam;
    std::array<int, N> minimos;
    std::array<int, N> valores;

    void cria();
    void libera();
    int tamanho();
    int topo();
    int desempilha();
    void empilha(int t);
    int obterMinimo();
};

void PilhaMin::cria() {
    tam = 0;
}

void PilhaMin::libera() {
    while (tamanho()) {
        desempilha();
    }
}

int PilhaMin::tamanho() {
    return tam;
}

int PilhaMin::topo() {
    return valores[tam-1];
}

int PilhaMin::desempilha() {
    assert(tam);
    return valores[--tam];
}

void PilhaMin::empilha(int t) {
    assert(tam<N);
    valores[tam] = t;
    if (!tam || t < obterMinimo()) minimos[tam] = t;
    else minimos[tam] = minimos[tam-1];
    tam++;
}

int PilhaMin::obterMinimo() {
    assert(tam);
    return minimos[tam-1];
}

void imprimePilha(PilhaMin* p) {
    while(p->tamanho()) {
        std::println("{}", p->desempilha());
    }
}

int main() {
    // Elementos a serem adicionados à pilha
    std::array<int, N> numeros1 = {14,78,40,98,69,46,51,12,40,88};
    std::array<int, N/2> numeros2 = {3,7,51,10,11};
    PilhaMin p;
    p.cria();
    for (int num: numeros1) {
        p.empilha(num);
    }

    while(p.tamanho() > N/2) {
        std::println("Elemento removido: {}", p.desempilha());
        std::println("Mínimo atual: {}\n", p.obterMinimo());
    }

    std::println("Inserindo novos elementos na pilha...");
    for (int num: numeros2) {
        p.empilha(num);
    }

    while(p.tamanho()) {
        std::println("Elemento removido: {}", p.desempilha());
        if (p.tamanho()) std::println("Mínimo atual: {}\n", p.obterMinimo());
        else std::println("Pilha vazia!");
    }

    p.libera();
    return 0;
}