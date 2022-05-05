#include "../include/RSA.h"

RSA::RSA(int p_, int q_, int d_) : p(p_), q(q_), d(d_) {
    Fi = (p - 1) * (q - 1);
    n = p * q;
}

int 
RSA::euclidean_extendido(int a, int b){
    int i = 1;
    std::vector<int> x, z;

    x.push_back(a);
    x.push_back(b);

    z.push_back(0);
    z.push_back(1);

    while (x[i - 1] % x[i] != 0){
        x.push_back(x[i - 1] % x[i]);
        z.push_back((-(x[i - 1] / x[i]) * z[i] + z[i - 1]) % a);
        i++;
    }
    if (x[i] == 1){
        if (z[i] < 0)
            z[i] += a;

        return z[i];
    }
    return 0;
}

int 
RSA::exponenciacionRapida(int a, int b, int m){   // a = base, b = exp, m = mod
    int x = 1;
    int y = a % m;
    while (b > 0 && y > 1){
        if (b%2 != 0){
            x = (x*y) % m;
            b--;
        } else {
            y = (y*y) % m;
            b = b/2;
        }
    }
    return x;
}

void 
RSA::cifrar(std::string mensaje) {
    if (!test())
        return;

    int size_bloque = (int)std::log(n) / (int)std::log(alfabeto.size());
    std::cout << "Tamaño del bloque: " << size_bloque << "\n";

    int bloque = 0;
    for (int i = 0; i < int(mensaje.size()); i++) {
        std::string bloque_mensaje = mensaje.substr(i, size_bloque);
        bloque = codificacion(size_bloque, bloque_mensaje);
        mensaje_codificado.push_back(bloque);
        mensaje_cifrado.push_back(exponenciacionRapida(bloque, e, n));
        i += size_bloque - 1;
    }
}

int 
RSA::codificacion(int size_bloque, std::string mensaje) {
    int resultado = 0;
    for (int i = 0; i < int(size_bloque); i++) {
        resultado += alfabeto.find(mensaje[i]) * pow(alfabeto.size(), size_bloque - (i + 1));
    }
    return resultado;
}

bool 
RSA::lehman_peralta(int primo){
    //Comprobar que no es divisible por ningún primo pequeño
    for (int i = 0; i < int(primos.size()); i++)
        if ((primo % primos[i] == 0) && (primo != primos[i]))
            return false;

    //Enteros aleatorios entre 2 y p-1
    std::vector<int> aleatorios;

    for (int i = 0; i < 6; i++)
        aleatorios.push_back(2 + rand() % (primo - 3)); // sumo 2 por el mínimo y resto 3 para que sea como máximo primo - 1

    // Calcular Ai^((p-1)/2) % p. Si todos dan 1 es compuesto.
    bool compuesto = true;
    for (int i = 0; i < int(aleatorios.size()); i++)
        if (exponenciacionRapida(aleatorios[i], (p - 1) / 2, p) != 1){
            compuesto = false;
            break;
        }

    if (compuesto)
        return false;

    // Si existe un i tal que Ai^((p-1)/2) % p != -1, es compuesto.
    int Ai = 0;
    for (int i = 0; i < int(aleatorios.size()); i++) {
        Ai = exponenciacionRapida(aleatorios[i], (p - 1) / 2, p);
        if (Ai != 1)
            Ai -= p;

        if (Ai != -1 && Ai != 1)
            return false;
    }

    // Es posible que sea primo
    return true;
}

bool 
RSA::test() {
    if (!lehman_peralta(p)) {
        std::cout << "P no es primo.\n";
        return false;
    }

    if (!lehman_peralta(q)) {
        std::cout << "Q no es primo.\n";
        return false;
    }

    e = euclidean_extendido(Fi,d);
    if (e == 0) {
        std::cout << "D no es primo con Fi(n).\n";
        return false;
    }

    return true;
}

void 
RSA::print() {
    std::cout << "D:" << d << "\n";
    std::cout << "Fi:" << Fi << "\n";
    std::cout << "E:" << e << "\n";
    std::cout << "N:" << n << "\n";

    std::cout << "Mensaje codificado: ";
    for (int i = 0; i < int(mensaje_codificado.size()); i++){
        std::cout << mensaje_codificado[i] << " ";
    }

    std::cout << "\nMensaje cifrado: ";
    for (int i = 0; i < int(mensaje_cifrado.size()); i++){
        std::cout << mensaje_cifrado[i] << " ";
    }
    std::cout << "\n";
}
