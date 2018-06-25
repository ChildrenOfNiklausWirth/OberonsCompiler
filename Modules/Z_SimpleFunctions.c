#include "Z_SimpleFunctions.h"


int int_contains(int digit, const int mass[], int massSize) {
    for (int i = 0; i < massSize; ++i)
        if (mass[i] == digit)
            return 1;
    return 0;

}