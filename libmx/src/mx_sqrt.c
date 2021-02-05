#include "../inc/libmx.h"

int mx_sqrt(int x) {
    for(int n = 1; x < 46341 && n * n <= x; n++)
       if (n * n % x == 0)
            return n;
    return 0;

}
