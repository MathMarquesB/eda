// Lista 2

import std;
#include <cassert>

constexpr int N = 10;
// Ex 5
// Escreva um algoritmo em que dada uma fila padrão F externa passada como parâmetro, inverte o conteúdo de F. Somente utilize as estruturas extras permitidas como armazenamento externo (mais espaço constante)

// a) Uma Pilha
void inverteA(std::queue<char>* f) {
    std::stack<char> p; // somente essa pilha e mais espaço auxiliar constante

    while (!f->empty()) {
        p.push(f->front());
        f->pop();
    }

    while (!p.empty()) {
        f->push(p.top());
        p.pop();
    }
}

// b) Duas Filas
auto pega_ultimo_elemento(std::queue<char>* f_remove, std::queue<char>* f_insere) {
    auto n = f_remove->front();
    f_remove->pop();
    if (f_remove->empty()) return n;
    f_insere->push(n);
    return pega_ultimo_elemento(f_remove, f_insere);
}

void inverteB(std::queue<char>* f) {
    std::queue<char> f1; // primeira fila auxiliar
    std::queue<char> f2; // segunda fila auxiliar
    
    int original_size = f->size();
    auto n = pega_ultimo_elemento(f, &f1);
    f->push(n);

    while (f->size() < original_size) {
        n = pega_ultimo_elemento(&f1, &f2);
        f->push(n);
        if (f->size() == original_size) return;
        n = pega_ultimo_elemento(&f2, &f1);
        f->push(n);
    }
}

int main() {
    // Elementos a serem adicionados à fila
    std::array<int, N> arr = {'A','B','C','D','E','F','G','H','I','J'};
    std::queue<char> f;

    std::println("==== Questão 5A ====");
    for (int i = 0; i<arr.size(); i++) {
        f.push(arr[i]);
    }
    inverteA(&f);
    for (int i = 0; i<N; i++) {
        std::println("Elemento {}: {}", i, f.front());
        f.pop();
    }

    std::println("==== Questão 5B ====");
    for (int i = 0; i<arr.size(); i++) {
        f.push(arr[i]);
    }
    inverteB(&f);
    for (int i = 0; i<N; i++) {
        std::println("Elemento {}: {}", i, f.front());
        f.pop();
    }

    return 0;
}