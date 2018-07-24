#include "SimpleFunctions.h"
#include <math.h>

int int_contains(int digit, const int mass[], int massSize) {
    for (int i = 0; i < massSize; ++i)
        if (mass[i] == digit)
            return 1;
    return 0;

}

unsigned long ASH(unsigned long x, long n) {
    return (unsigned long) (x * pow(2, n));
}

int int_hexToDecimal(int digit) {
    int result = 0;
    int multiplier = 1;
    int currentDigit;

    while (digit != 0) {
        currentDigit = digit % 10;
        digit = digit / 10;
        result += currentDigit * multiplier;
        multiplier *= 16;

    }
    return result;

}