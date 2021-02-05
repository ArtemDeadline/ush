#include "../inc/libmx.h"
double mx_pow(double a, unsigned int pow) {
    if (pow == 0)
        return 1;

    double const_a = a;

    while(pow-- > 1)
        a *= const_a;
    
    return a;
}
