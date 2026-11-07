// Lista 2

import std;
#include <cassert>

// Ex 1
// Considere um tipo chamado Deque, que inclui manipulação de dois extremos em uma estrutura linear (como se operasse como Pilha e Fila simultaneamente).

// Código do enunciado
template<typename Agregado, typename Tipo>
concept DequeTAD = requires(Agregado a, Tipo t) {
    // requer operação de consulta ao elemento 'inicio'
    { a.inicio() };
    // requer operação de consulta ao elemento 'fim'
    { a.fim() };
    // requer operação 'insereInicio' sobre tipo 't'
    { a.insereInicio(t) };
    // requer operação 'insereFim' sobre tipo 't'
    { a.insereFim(t) };
    // requer operação 'removeInicio' e retorna tipo 't'
    { a.removeInicio() };
    // requer operação 'removeFim' e retorna tipo 't'
    { a.removeFim() };
};

// 1.a) Satisfaça as seguintes operações de um DequeTAD para o tipo 'char', utilizando uma estrutura Sequencial OU uma estrutura encadeada:

// Estrutura auxiliar para representar um nó
struct NoDeque {
    char dado;
    NoDeque* prox;
};

struct Deque {
// implementar métodos propostos no TAD Deque
    int N; // Tamanho do Deque
    NoDeque* primeiro_no;

    void cria();
    void libera();
    int tamanho();
    char inicio();
    char fim();
    void insereInicio(char c);
    void insereFim(char c);
    char removeInicio();
    char removeFim();
};

void Deque::cria() {
    N = 0;
    primeiro_no = nullptr;
}

void Deque::libera() {
    while (primeiro_no) {
        removeInicio();
    }
}

int Deque::tamanho() {
    return N;
}

char Deque::inicio() {
    assert(tamanho());
    return primeiro_no->dado;
}

char Deque::fim() {
    assert(tamanho());
    NoDeque* temp = primeiro_no;
    while(temp->prox) {
        temp = temp->prox;
    }
    return temp->dado;
}

void Deque::insereInicio(char c) {
    NoDeque* temp = new NoDeque{.dado = c, .prox=primeiro_no};
    primeiro_no = temp;
    N++;
}

void Deque::insereFim(char c) {
    // Caso com a lista vazia
    if (!primeiro_no) {
        primeiro_no = new NoDeque{.dado = c, .prox=nullptr};
    } else {
        NoDeque* ult_no = primeiro_no;
        while (ult_no->prox) {
            ult_no = ult_no->prox;
        }
        NoDeque* temp = new NoDeque{.dado = c, .prox=nullptr};
        ult_no->prox = temp;
    }
    N++;
}

char Deque::removeInicio() {
    assert(tamanho());
    NoDeque* temp = primeiro_no;
    char r = primeiro_no->dado;
    primeiro_no = primeiro_no->prox;
    delete(temp);
    N--;
    return r;
}

char Deque::removeFim() {
    assert(tamanho());
    // Caso com 1 único elemento
    if (!primeiro_no->prox) {
        char r = primeiro_no->dado;
        delete primeiro_no;
        primeiro_no = nullptr; // CORREÇÃO: Limpa o ponteiro principal
        N--;
        return r;
    }

    // Caso com 2 ou mais elementos: busca o penúltimo nó
    NoDeque* ant = primeiro_no;
    while (ant->prox->prox != nullptr) {
        ant = ant->prox;
    }

    NoDeque* ult_no = ant->prox;
    char r = ult_no->dado;

    delete ult_no;
    ant->prox = nullptr; // CORREÇÃO: O penúltimo nó agora vira o novo fim!
    N--;

    return r;
}

static_assert(DequeTAD<Deque, char>); // testa se Deque está correto

//1.b) Implemente uma estrutura PilhaDeque para tipo 'char', utilizando somente um Deque como armazenamento interno e mais espaço auxiliar constante:
struct PilhaDeque{
    Deque d; // Deque para 'char' (veja exercício anterior)
    void cria() {d.cria();}
    void libera() {d.libera();}
    int tamanho() {return d.tamanho();}
    void insere(char c) {d.insereInicio(c);}
    char remove() {return d.removeInicio();}
    char topo() {return d.inicio();}
};

// 1.c) Implemente uma estrutura FilaDeque para tipo ‘char’, utilizando somente um Deque como armazenamento interno e mais espaço auxiliar constante:
struct FilaDeque {
    Deque d; // Deque para ‘char’ (veja exercício anterior)
    void cria() {d.cria();}
    void libera() {d.libera();}
    int tamanho() {return d.tamanho();}
    void insere(char c) {d.insereFim(c);}
    char remove() {return d.removeInicio();}
    char primeiro() {return d.inicio();}
};

int main() {
    std::println("==== Questão 1A ====");
    Deque d;
    d.cria();

    std::println("\nSe o código compilou, então a estrutura dos métodos está correta.");
    
    std::println("\n1. Teste de inserção no início:\nInserindo os elementos na ordem: E, D, C, B, A.");
    d.insereInicio('E');
    d.insereInicio('D');
    d.insereInicio('C');
    d.insereInicio('B');
    d.insereInicio('A');

    std::println("\n2. Teste de consulta ao inicio:\nO item esperado é 'A' (o úlimo elemento adicionado) e o tamanho esperado é 5.\nResultado:\n- Início: {}\n- Tamanho: {}", d.inicio(), d.tamanho());

    std::println("\n3. Teste de remoção do inicio:\nO item removido esperado é 'A', o novo topo esperado é B e o tamanho esperado é 4.\nResultado:\n- Removido: {}\n- Topo: {}\n- Tamanho: {}", d.removeInicio(), d.inicio(), d.tamanho());

    std::println("\n4. Teste de consulta ao fim:\nO item esperado é 'E' e o tamanho esperado é 4.\nResultado:\n- Último: {}\n- Tamanho: {}", d.fim(), d.tamanho());

    std::println("\n5. Teste de remoção do fim:\nA função será chamada duas vezes.");
    d.removeFim();
    d.removeFim();
    std::println("O novo último item esperado é 'C' e o tamanho esperado é 2.\nResultado:\n- Último: {}\nTamanho: {}", d.fim(), d.tamanho());

    std::println("\n6. Teste de inserção no fim:");
    d.insereFim('Z');
    std::println("O novo último item esperado é 'Z' e o tamanho esperado é 3.\nResultado:\n- Último: {}\nTamanho: {}", d.fim(), d.tamanho());

    d.libera();

    std::println("\n\n==== Questão 1B ====");
    PilhaDeque p;
    p.cria();

    std::println("\n1. Teste de inserção:\nInserindo os elementos na ordem: E, D, C, B, A.");
    p.insere('E');
    p.insere('D');
    p.insere('C');
    p.insere('B');
    p.insere('A');

    std::println("\n2. Teste de consulta ao topo:\nO item esperado é 'A' (o úlimo elemento adicionado) e o tamanho esperado é 5.\nResultado:\n- Início: {}\n- Tamanho: {}", p.topo(), p.tamanho());

    p.libera();

    std::println("\n\n==== Questão 1C ====");
    FilaDeque f;
    f.cria();
    
    std::println("\n1. Teste de inserção:\nInserindo os elementos na ordem: E, D, C, B, A.");
    f.insere('E');
    f.insere('D');
    f.insere('C');
    f.insere('B');
    f.insere('A');

    std::println("\n2. Teste de consulta ao início:\nO item esperado é 'E' (o primeiro elemento adicionado) e o tamanho esperado é 5.\nResultado:\n- Início: {}\n- Tamanho: {}", f.primeiro(), f.tamanho());

    std::println("\n3. Teste de remoção:\nO item removido esperado é 'E', o novo primeiro esperado é D e o tamanho esperado é 4.\nResultado:\n- Removido: {}\n- Primeiro: {}\n- Tamanho: {}", f.remove(), f.primeiro(), f.tamanho());

    std::println("\n4. Teste de remoções consecutivas:\nA função será chamada quatro vezes.");
    f.remove();
    f.remove();
    f.remove();
    f.remove();
    std::println("O tamanho esperado é 0.\nResultado:\n- Tamanho: {}", f.tamanho());

    std::println("\n5. Teste de inserção após a lista ficar vazia:\nInserindo o elemento 'Z'.");
    f.insere('Z');
    std::println("O início esperado é 'Z' e o tamanho esperado é 1.\nResultado:\n- Primeiro: {}\n- Tamanho: {}",f.primeiro(), f.tamanho());

    f.libera();

    return 0;
}