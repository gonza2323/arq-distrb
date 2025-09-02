#include <iostream>
#include <cmath>
#include <thread>
#include <sys/time.h>

const int cantDeHilos = 10;
std::thread hilos[cantDeHilos];
long double sumasParciales[cantDeHilos];

long double calcularTermino(int i, long double x)
{
    long double a = 1 / (2.0*i + 1);
    long double b = (x - 1) / (x + 1);
    long double c = 2 * a * pow(b, (2*i + 1));
    return c;
}

void calcularParteSerie(int i0, int i1, long double x, int i)
{
    long double sumaParcial = 0;
    for (int i = i0; i < i1; i++)
    {
        long double termino = calcularTermino(i, x);
        sumaParcial += termino;
    }
    sumasParciales[i] = sumaParcial;
}

int main() {
    long double result = 0;
    long double x;

    std::cout << "Ingrese el valor de x: ";
    std::cin >> x;

    timeval time1, time2;
    gettimeofday(&time1, NULL);
    
    int cantTerminos = 10000000;
    int cantTerminosPorHilo = cantTerminos / cantDeHilos;
    for (int i = 0; i < cantDeHilos; i++) {
        hilos[i] = std::thread(calcularParteSerie, i*cantTerminosPorHilo, (i+1)*cantTerminosPorHilo, x, i);
    }

    for (int i = 0; i < cantDeHilos; i++) {
        if (hilos[i].joinable() == true) {
            hilos[i].join();
            result += sumasParciales[i];
        }
    }
    
    gettimeofday(&time2, NULL);
    std::cout << "Tiempo ejecución: " << double(time2.tv_sec - time1.tv_sec) +
    + double(time2.tv_usec - time1.tv_usec) / 1000000 << std::endl;

    std::cout << result;
}
