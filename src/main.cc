#include "../include/RSA.h"

int main(){
    RSA A(421, 7, 1619);
    RSA B(2347, 347, 5);

    // EJERCICIO 1
    std::cout << "--------------------- Ejemplo 1 ---------------------" << std::endl;
    A.cifrar("MANDADINEROS");
    A.print();

    // EJERCICIO 2
    std::cout << std::endl;
    std::cout << "--------------------- Ejemplo 2 ---------------------" << std::endl;
    B.cifrar("AMIGOMIO");
    B.print();

    return 0;
}   