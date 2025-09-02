#include <iostream>
#include <cmath>
#include <thread>
#include <sys/time.h>
#include <algorithm>
#include <vector>

const int cantDeHilos = 10;
std::thread hilos[cantDeHilos];
std::vector<long int> vectoresDePrimos[cantDeHilos];

void buscarPrimos(std::vector<long int>& primos, int i0, int i1, int threadIndex) {
    for (long int i = i0; i < i1; i += 2) {
        bool es_primo = true;
        for (long int primo : primos) {
            if (primo > ceil(sqrtl(i)))
                break;

            if (i % primo == 0) {
                es_primo = false;
                break;
            }
        }

        if (es_primo)
            vectoresDePrimos[threadIndex].push_back(i);
    }
}

int main() {
    long int N = 10000000;
    std::vector<long int> primos = {2};

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    for (int i = 0; i < cantDeHilos; i++)
    {
        vectoresDePrimos[i] = std::vector<long int>();
    }
    
    // Buscamos los primos entre 2 y raíz de N
    for (long int i = 3; i < ceil(sqrtl(N)); i += 2)
    {
        bool es_primo = true;
        for (long int primo : primos) {
            if (primo > ceil(sqrtl(i)))
                break;

            if (i % primo == 0) {
                es_primo = false;
                break;
            }
        }

        if (es_primo)
            primos.push_back(i);
    }

    long int raiz = (long int)(ceil(sqrtl(N)));
    long int tamanoIntervalo = (N - raiz) / cantDeHilos;
    long int ultimoIntervalo = (N - raiz) % cantDeHilos;
    for (int i = 0; i < cantDeHilos - 2; i++)
    {
        long int inicioIntervalo = raiz + i * tamanoIntervalo;
        long int finIntervalo = raiz + (1 + 1) * tamanoIntervalo;
        hilos[i] = std::thread(buscarPrimos, &primos, inicioIntervalo, finIntervalo, i);
    }
    hilos[cantDeHilos-1] = std::thread(buscarPrimos, &primos, N - ultimoIntervalo, N, cantDeHilos-1);

    for (int i = 0; i < cantDeHilos; i++) {
        if (hilos[i].joinable() == true) {
            hilos[i].join();
            
            primos.insert(primos.end(), vectoresDePrimos[i].begin(), vectoresDePrimos[i].end());
        }
    }
    
    for (int i = primos.size() - 10; i < primos.size(); i++) {
        std::cout << primos[i] << '\n';
    }
    
    gettimeofday(&time2, NULL);
    std::cout << "Tiempo ejecución: " << double(time2.tv_sec - time1.tv_sec) +
    + double(time2.tv_usec - time1.tv_usec) / 1000000 << std::endl;

}
