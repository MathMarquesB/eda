// Lista 2

import std;
#include <cassert>

// Ex 4
// Escreva um algoritmo que dada uma pilha padrão P externa passada como parâmetro, inverte o conteúdo de P. Somente utilize as estruturas extras permitidas como armazenamento externo(mais espaço constante)

// a) Uma Fila
void inverteA(std::stack<char>* p) {
    std::queue<char> f; // somente essa fila e mais espaço auxiliar constante
    // lePilha(p, &f);
    while(!p->empty()) {
        f.push(p->top());
        p->pop();
    }
    while(!f.empty()) {
        p->push(f.front());
        f.pop();
    }
}

// b) Duas Pilhas
void inverteB(std::stack<char>* p) {
    std::stack<char> p1; // primeira pilha auxiliar
    std::stack<char> p2; // segunda pilha auxiliar
    while(!p->empty()) {
        p1.push(p->top());
        p->pop();
    }
    while(!p1.empty()) {
        p2.push(p1.top());
        p1.pop();
    }
    while(!p2.empty()) {
        p->push(p2.top());
        p2.pop();
    }
}

// c) Uma Pilha
void lePilha(std::stack<char>* p, std::stack<char>* p1) {
    char c = p->top();
    p->pop();
    if (!p->empty()) lePilha(p, p1);
    p1->push(c);
}

void inverteC(std::stack<char>* p) {
    std::stack<char> p1; // uma pilha auxiliar
    lePilha(p, &p1);
    while(!p1.empty()) {
        p->push(p1.top());
        p1.pop();
    }
}


// Funções auxiliares
void imprimePilha(std::stack<char>* p) {
    while(!p->empty()) {
        std::println("{}", p->top());
        p->pop();
    }
}

void iniciaPilha(std::stack<char>* p, const std::string& txt) {
    for (int i = 0; txt[i]; i++) {
        p->push(txt[i]);
    }
}

int main() {
    // Elementos a serem adicionados à fila
    std::string texto = "LISTA 2";
    std::stack<char> p;

    std::println("==== Pilha original ====");
    iniciaPilha(&p, texto);
    imprimePilha(&p);

    std::println("\n==== Questão 4A ====");
    iniciaPilha(&p, texto);
    inverteA(&p);
    imprimePilha(&p);

    std::println("\n==== Questão 4B ====");
    iniciaPilha(&p, texto);
    inverteB(&p);
    imprimePilha(&p);

    std::println("\n==== Questão 4C ====");
    iniciaPilha(&p, texto);
    inverteC(&p);
    imprimePilha(&p);

    return 0;
}