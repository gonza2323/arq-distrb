#include <iostream>
#include <cmath>
#include <thread>
#include <sys/time.h>
#include <vector>

const int cantDeHilos = 10;
std::thread hilos[cantDeHilos];
std::vector<long long int> vectoresDePrimos[cantDeHilos];

void buscarPrimos(std::vector<long long int>& primos, int i0, int i1, int i) {
    for (long long int i = i0; i < i1; i++) {
        bool es_primo = true;
        for (long long int primo : primos) {
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
}

int main() {
    long long int N = 10000000;
    std::vector<long long int> primos = {2};
    std::vector<long long int> result = {};

    timeval time1, time2;
    gettimeofday(&time1, NULL);
    
    for (long long int i = 3; i < ceil(sqrtl(N)); i++)
    {
        bool es_primo = true;
        for (long long int primo : primos) {
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

    for (size_t i = ceil(sqrtl(N)); i < N; i++)
    {
        /* code */
    }

    for (int i = 0; i < cantDeHilos; i++) {
        if (hilos[i].joinable() == true) {
            hilos[i].join();
            
            primos.insert(vec1.end(), vec2.begin(), vec2.end());
        }
    }
    
    for (int i = primos.size() - 10; i < primos.size(); i++) {
        std::cout << primos[i] << '\n';
    }
    
    gettimeofday(&time2, NULL);
    std::cout << "Tiempo ejecución: " << double(time2.tv_sec - time1.tv_sec) +
    + double(time2.tv_usec - time1.tv_usec) / 1000000 << std::endl;

}
