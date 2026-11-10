import std;

constexpr int MAX_N = 50;

struct Heap1 {
    int v[MAX_N];
    int N;
    void cria();
    int frente();
    void insere(int chave);
    int remove();
    void troca(int p, int pos, int v[]);
    int pai(int pos);
    void sobe(int pos);
    void constroi_sobe(int v2[], int N2);
    void imprimeSeq();
};

void Heap1::cria() {
    N = 0;
}

int Heap1::frente() {
    return v[0];
}

void Heap1::troca(int p, int pos, int v[]) {
    int tmp = v[p];
    v[p] = v[pos];
    v[pos] = tmp;
}

int Heap1::pai(int pos) {
    return (pos - 1) / 2;
}

void Heap1::sobe(int pos) {
    int p = pai(pos);
    while (pos) {
        if (v[pos] >= v[p])
            break;
        troca(p, pos, v);
        pos = p;
        p = pai(pos);
    }
}

void Heap1::insere(int chave) {
    v[N] = chave;
    N++;
    sobe(N - 1);
}

void Heap1::constroi_sobe(int v2[], int N2) {
    for (int i = 0; i < N2; i++)
        v[i] = v2[i];
    N = N2;
    for (int i = 0; i < N2; i++)
        sobe(i);
}

void Heap1::imprimeSeq() {
    for (int i = 0; i < N; i++)
        std::println("{}", v[i]);
}

int main() {
    int v2[] = {20, 10, 15, 4, 7, 8, 3, 1, 2};

    Heap1 heap;
    heap.cria();
    heap.constroi_sobe(v2, 9);
    heap.imprimeSeq();

    return 0;
}