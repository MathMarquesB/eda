import std;

// Função auxiliar de partição (Esquema Lomuto ajustado para intervalo [ini, fim))
template<typename T>
int particiona(std::vector<T>& v, int ini, int fim) {
    T pivo = v[fim - 1]; // Escolhe o último elemento da fatia como pivô
    int i{ini};
    int tmp{0};

    for (int j = ini; j < fim - 1; ++j) {
        if (v[j] <= pivo) {
            tmp = v[i]; v[i] = v[j]; v[j] = tmp;
            ++i;
        }
    }
    tmp = v[i]; v[i] = v[fim - 1]; v[fim - 1] = tmp;
    return i; // Retorna o índice final do pivô
}

// Algoritmo Quick Sort
template<typename T>
void quick_sort(std::vector<T>& v, int ini, int fim) {
    if (fim - ini <= 1) return;
    int p = particiona(v, ini, fim);
    quick_sort(v, ini, p);
    quick_sort(v, p + 1, fim);
}

int main() {
    // 1. Convertido de C-array para std::vector para ser compatível com quick_sort
    std::vector<int> numbers = {9, 3, 4, 5, 6, 2, 1, 7, 10, 8};

    std::println("Antes da ordenacao:");
    for (int num : numbers) {
        std::print("{} ", num);
    }
    std::println("");

    // 2. Chamada do quick_sort passando o intervalo [0, tamanho)
    quick_sort(numbers, 0, static_cast<int>(numbers.size()));

    std::println("\nDepois da ordenacao:");
    for (int num : numbers) {
        std::print("{} ", num);
    }
    std::println("");

    return 0;
}