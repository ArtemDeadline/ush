#include "../inc/libmx.h"

char* mx_nbr_to_hex(unsigned long nbr) {
    unsigned long nbr1 = nbr;
    int len = 1;
    while (nbr1 / 16 >= 1) {
        nbr1 /= 16;
        len++;
    }
    char *s = mx_strnew(len);
 if (nbr == 0) {
  s[0] = '0';
  return s;
 }
 for (int i = 1; nbr % 16 != 0 || nbr / 16 >= 1; i++) {
  if (nbr % 16 < 10) {
   s[len - i] = nbr % 16 + 48;
        }
  else {
   s[len - i] = nbr % 16 + 87;
        }
  nbr /= 16;
    }
    return s;
}
