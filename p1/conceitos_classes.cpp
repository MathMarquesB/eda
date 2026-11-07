import std;

// 1. Definição do Conceito C++20/23
template<typename Agregado, typename Tipo>
concept ConjuntoTAD = requires(Agregado a, Tipo t)
{
    { a.pertence(t) } -> std::same_as<bool>;
    { a.insere(t)   } -> std::same_as<bool>;
    { a.remove(t)   } -> std::same_as<bool>;
    { a.tamanho()   } -> std::same_as<int>;
};

// 2. Classe que implementa a interface exigida
template<typename T>
class MeuConjunto {
private:
    std::unordered_set<T> elementos;

public:
    MeuConjunto() = default;

    bool insere(T item) {
        // insert().second retorna true se o elemento foi inserido com sucesso
        return elementos.insert(item).second;
    }

    bool pertence(T item) const {
        return elementos.contains(item);
    }

    bool remove(T item) {
        // erase() retorna o número de elementos removidos (0 ou 1)
        return elementos.erase(item) > 0;
    }

    int tamanho() const {
        return static_cast<int>(elementos.size());
    }
};

// 3. Função Genérica Restrita pelo Conceito
template<typename C, typename T>
requires ConjuntoTAD<C, T>
void processarConjunto(C& conjunto, T elemento) {
    std::println("--- Testando Operacoes ---");
    
    bool inseriu = conjunto.insere(elemento);
    std::println("Inserindo '{}': {}", elemento, inseriu ? "Sucesso" : "Já existia");

    std::println("Pertence ao conjunto? {}", conjunto.pertence(elemento));
    std::println("Tamanho atual: {}", conjunto.tamanho());

    bool removeu = conjunto.remove(elemento);
    std::println("Removendo '{}': {}", elemento, removeu ? "Sucesso" : "Não encontrado");
    std::println("Tamanho apos remocao: {}", conjunto.tamanho());
}

int main() {
    // Validação estática em tempo de compilação:
    // Garante que MeuConjunto<std::string> satisfaz ConjuntoTAD para std::string
    static_assert(ConjuntoTAD<MeuConjunto<std::string>, std::string>);

    MeuConjunto<std::string> nomes;

    std::println("Inicializando testes com MeuConjunto<std::string>...");
    processarConjunto(nomes, std::string("C++23"));

    return 0;
}