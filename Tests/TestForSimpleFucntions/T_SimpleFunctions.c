#include "../../Modules/SimpleFunctions/SimpleFunctions.c"
//TODO must be #include "../../Modules/SimpleFunctions/SimpleFunctions.h"
#include <stdio.h>

int test_int_Contains() {
    int massLength = 10;
    int mass[massLength];

    for (int i = 0; i < massLength; ++i)
        mass[i] = i;

    for (int j = 0; j < massLength; ++j)
        if (int_contains(j, mass, massLength) == 0)
            return 0;

    for (int k = 0; k < massLength; ++k)
        if (int_contains(k + massLength, mass, massLength) == 1)
            return 0;


    return 1;

}

int test_ASH() {
    if (ASH(2, 1) != 4)
        return 0;
    if (ASH(4096, 1) != 8192)
        return 0;
    if (ASH(1, 10) != 1024)
        return 0;
    if (ASH(3, 2) != 12)
        return 0;

    return 1;

}

int test_int_hexToDecimal() {
    if (int_hexToDecimal(60) != 96)
        return 0;
    if (int_hexToDecimal(-60) != -96)
        return 0;
    if (int_hexToDecimal(73466) != 472166)
        return 0;
    if (int_hexToDecimal(-73466) != -472166)
        return 0;
    if (int_hexToDecimal(5327) != 21287)
        return 0;
    if (int_hexToDecimal(-5327) != -21287)
        return 0;
    if (int_hexToDecimal(7777777) != 125269879)
        return 0;
    if (int_hexToDecimal(-7777777) != -125269879)
        return 0;
    return 1;

}

int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 3;

    printf("SimpleFunctions Testing...\n\n");

    printf("int_Contains...\n");
    if (test_int_Contains() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("ASH...\n");
    if (test_ASH() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("int_hexToDecimal...\n");
    if (test_int_hexToDecimal() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");

    return 0;

}