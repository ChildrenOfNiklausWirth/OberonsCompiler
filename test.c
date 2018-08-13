#include <stdio.h>
#include <math.h>
#include "Modules/SimpleFunctions/SimpleFunctions.h"


int main() {
    int a = 1 & 0x3F;
    long need = (2 << 18) + (2 << 4);
    printf("%d\n", int_hexToDecimal(40000));
    printf("%d", 0x3FFFF);


    return 0;
}

