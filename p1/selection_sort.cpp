import std;

constexpr int N = 15;

template <typename T>
void selection_sort(T* v, int n) {
    int menor;
    T tmp;
    for (int i=0; i<n; i++) {
        menor = i;
        for (int j=i+1; j<n; j++) {
            if (v[j] < v[menor]) menor = j;
        }
        tmp = v[i];
        v[i] = v[menor];
        v[menor] = tmp;
    }
}
int main() {
    std::array<int, N> v = {1,3,2,5,11,6,4,9,10,8,13,12,7,15,14};
    // Usar v.data() por causa do tipo genérico T*
    // Usar &v quando a função esperar std::array<int, N>*
    selection_sort(v.data(), N);
    for (int num: v) std::println("{}", num);
    
    return 0;
}