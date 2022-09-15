#include <math.h>
#include <limits.h>

double acos(double x){puts("acos");}
double asin(double x){puts("asin");}
double exp(double x){puts("exp");}

double fmod(double numer, double denom){puts("fmod");}

// adapted from musl
double frexp(double x, int* exp) {
    unsigned int i = *(unsigned int*)&x;
    int e = (i >> 23) & 0xff;
    if(!e) {
        if(x) {
            x = frexp(x * 18446744073709551616.0f, exp);
            *exp -= 64; 
        } else {
            *exp = 0;
        }
        return x;
    } else if(e == 0xff) {
        return x;
    }

    *exp = e - 0x7e;
    i &= 0x807fffff;
    i |= 0x3f000000;
    return *(float*)&i;
}

double ldexp(double x, int exp){puts("ldexp");}
double log(double x){puts("log");}
double log10(double x){puts("log10");}
double pow(double base, double exponent){puts("pow");}
