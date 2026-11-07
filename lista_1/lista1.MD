# Lista 2 - Pilhas, Filas e Estruturas Lineares

## Questão 1

Optou-se por criar a estrutura auxiliar "NoDeque" para atuar como um nó encadeado, dispensando a necessidade de estabelecer um tamanho de valor fixo.

### Código

```C++
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
    ant->prox = nullptr;
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
```

### Análise da complexidade assintótica
#### Letra A
**Métodos com O(1):**
* cria()
* tamanho()
* inicio()
* insereInicio()
* removeInicio()

**Métodos com O(N):**
* libera()
* fim()
* insereFim()
* removeFim()

Os métodos com O(1) são aqueles que acessam uma variável diretamente (como `tamanho` e `inicio`) ou manipulam uma quantidade constante de variáveis (como `cria` e `insereInicio`). Os métodos com O(N) necessitam percorrer todos os elementos presentes na estrutura, como o `libera` que libera a memória de cada nó.

#### Letras B e C
Como todos os métodos foram herdados da letra A, a complexidade de cada um se mantém.

## Questão 4
### Código
```C++
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
```

### Análise da complexidade assintótica
Nas letras A e C, os métodos criados executam 2 laços sequenciais de tamanho N. Na letra B, são 3 laços. A complexidade dos 3 casos pode ser expressada como `k * N`. Ocultando a constante, a complexidade é definida por O(N).

## Questão 5
### Código
```C++
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
```

### Análise da complexidade assintótica
#### Letra A
Como são feitos dois laços de tamanho N, a complexidade do método é O(N).

#### Letra B
Para cada um dos N elementos inseridos de volta na fila f, a função `pega_ultimo_elemento` percorre recursivamente os elementos restantes entre f1 e f2, totalizando N + (N-1) + ... + 1 = O(N^2) operações.

## Questão 6
Diferente da questão 1, nessa questão, optou-se por usar um tamanho de valor fixo para a estrutura, o que permitiu-se usar dois vetores (`valores` e `minimos`) para armazenar informação, mantendo a complexidade O(1) na maioria dos métodos.

### Código
```C++
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
```

### Análise da complexidade assintótica
Com exceção do método `libera`, o qual é opcional para esta questão, todos os demais métodos operam com complexidade O(1), pois realizam um número constante de operações.

## Questão 8
### Código
```C++
import std;
#include <cassert>

// Ex 8
// Considere o TAD chamado PegaEntreMaiores com a seguinte especificação:
template<typename Agregado, typename Tipo>
concept PegaEntreMaioresTAD = requires(Agregado a, Tipo t) {
    // requer operação 'insere' sobre tipo 't'
    { a.insere(t) };
    // requer operação de retornar o maior elemento
    { a.maior() };
    // requer operação de retornar o segundo maior elemento
    { a.segundomaior() };
    // requer operação de retornar o k-esimo maior elemento
    { a.kmaior(t) };
    // requer operação tamanho, ou seja, numero total de elementos
    { a.tamanho() };
};

// Implemente um TAD PegaEntreMaiores para o tipo int, com as seguintes estratégias:
// 8.a) utilize um vetor não-ordenado para armazenar os valores internamente (analise as complexidades das operações!)
struct PegaEntreMaioresA {
    int tam;
    std::vector<int> valores;
    std::vector<int> maiores;

    void cria();
    void insere(int t);
    int maior();
    int segundomaior();
    int kmaior(int t);
    int tamanho();
};

void PegaEntreMaioresA::cria() {
    tam = 0;
}

void PegaEntreMaioresA::insere(int t) {
    valores.push_back(t);
    if (!tam || t > maior()) maiores.push_back(t);
    else maiores.push_back(maiores[tam-1]);
    tam++;
}

int PegaEntreMaioresA::maior() {
    assert(tam);
    return maiores[tam-1];
}

int PegaEntreMaioresA::segundomaior() {
    assert(tam);
    int primeiromaior = maior();
    for (int i=tam-1; i>=0; i--) {
        if (primeiromaior > maiores[i]) return maiores[i];
    }
    return primeiromaior;
}

int PegaEntreMaioresA::kmaior(int t) {
    assert(tam);
    if (!t) return maior();
    int atual = maior();
    int check = t;
    for (int i=tam-1; i>=0; i--) {
        if (atual > maiores[i]) {
            atual = maiores[i];
            check--;
            if (!check) return atual;
        }
    }
    return atual;
}

int PegaEntreMaioresA::tamanho() {
    return tam;
}
```

### Análise da complexidade assintótica
#### Letra A
**Métodos com O(1)**
* cria()
* tamanho()
* insere(t)
* maior()

**Métodos com O(N)**
* segundomaior()

**Complexidade indefinida**
* kmaior(k)

O uso do vetor auxiliar `maiores` permite encontrar o maior com apenas uma operação. Sabendo esse valor, é possível buscar o segundo maior percorrendo todos os N elementos uma única vez. O maior problema é buscar o k-ésimo elemento sem ordenar o vetor, o que representa uma complexidade de O(N^k).
