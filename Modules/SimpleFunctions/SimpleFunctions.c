#include "SimpleFunctions.h"
#include <math.h>
#include <stdio.h>

int namesEquals(char *name1, int size1, char *name2, int size2) {
    if (size1 == size2) {

        for (int i = 0; i < size1; ++i)
            if (name1[i] != name2[i])
                return 0;

        return 1;

    } else
        return 0;
}

void binaryPrint(long n) {
    int length = 32;
    if (n < 0) {
        printf("%d", 1);
        n *= -1;
        length--;
    }
    for (int i = 0; i < length; ++i)
        printf("%d", (int) ((n >> length - i - 1) & 1));
    printf("\n");

}
