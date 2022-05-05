#include <iostream>
#include <vector>
#include <random>
#include <cmath>  // Log
#include <climits>

class RSA {
    private:
        std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::vector<int> primos = {2, 3, 5, 7, 11, 13, 17, 19};
        std::vector<int> mensaje_codificado;
        std::vector<int> mensaje_cifrado;
        int p;
        int q;
        int d;
        int Fi;
        int e;
        int n;

        long exponenciacionRapida(int base, int exponente, int modulo); 
        int codificacion(int, std::string); 
        int euclidean_extendido(int, int); 
        bool lehman_peralta(int primo); 
        int cod_mensaje(); 

    public:
        RSA(int p_, int q_, int d_); 
        ~RSA(){}; 

        bool test(); 
        void cifrar(std::string mensaje); 
        void print();
};