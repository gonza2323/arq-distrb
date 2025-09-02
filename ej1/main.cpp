#include <iostream>
#include <cmath>
#include <sys/time.h>

int main() {
    long double result = 0;
    long double x;

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    std::cout << "Ingrese el valor de x: ";
    std::cin >> x;

    for (int i = 0; i < 10000000; i++)
    {
        long double a = 1 / (2.0*i + 1);
        long double b = (x - 1) / (x + 1);
        long double c = 2 * a * pow(b, (2*i + 1));
        result += c;
    }

    gettimeofday(&time2, NULL);
    std::cout << "Tiempo ejecución: " << double(time2.tv_sec - time1.tv_sec) +
    + double(time2.tv_usec - time1.tv_usec) / 1000000 << std::endl;
    
    std::cout << result;
}
