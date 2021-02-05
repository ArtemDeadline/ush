#include "../inc/libmx.h"

int mx_whitespace(int c) {
    return  c == '\f' || c == '\n' ||  
    c == '\r' || c == '\t' || c == '\v' || c == ' ';
}
