#include <print>
int main() {
int x1 = 7;
std::println("x1 é {}", x1); /* x1 é 7 */
double x6 = x1 / 2.0;
std::println("metade de {} é {}", x1, x6); // metade de 7 é 3.5
char b = 'L';
std::println("isto é uma {}etra", b); // isto é uma Letra
std::print("Olá mundo! \n"); // Olá mundo! (quebra de linha)
return 0;
}