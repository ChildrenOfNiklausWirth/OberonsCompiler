#include <stdio.h>
#include "../../Modules/Structures/Set.h"

int test_set_contains() {
    struct Set *set = set_new();

    int rightArray[] = {5, 6, 7};
    for (int i = 0; i < sizeof(rightArray) / 4; ++i)
        set_INCL(set, rightArray[i]);
    for (int i = 0; i < sizeof(rightArray) / 4; ++i)
        if (!set_contains(*set, rightArray[i]))
            return 0;

    if (set_contains(*set, 1929))
        return 0;
    if (set_contains(*set, 238))
        return 0;
    if (set_contains(*set, 935))
        return 0;

    return 1;

}

int test_set_INCL() {

    struct Set *set = set_new();

    int rightArray[] = {5, 6, 7};
    for (int i = 0; i < sizeof(rightArray) / 4; ++i) {
        set_INCL(set, rightArray[i]);
        set_INCL(set, rightArray[i]);
        set_INCL(set, rightArray[i]);
    }
    if (set->size != sizeof(rightArray) / 4)
        return 0;
    for (int j = 0; j < set->size; ++j)
        if (set->array[j] != rightArray[j])
            return 0;
    return 1;

}

int test_set_EXCL() {
    struct Set *set = set_new();

    int rightArray[] = {5, 6, 7};
    for (int i = 0; i < sizeof(rightArray) / 4; ++i) {
        set_INCL(set, rightArray[i]);
        set_INCL(set, rightArray[i]);
        set_INCL(set, rightArray[i]);
    }

    //Добавляем и удаляем addedAndDeletedArray
    int addedAndDeletedArray[] = {10, 12, 15};
    for (int i = 0; i < sizeof(addedAndDeletedArray) / 4; ++i) {
        set_INCL(set, addedAndDeletedArray[i]);
        set_INCL(set, addedAndDeletedArray[i]);
        set_INCL(set, addedAndDeletedArray[i]);
    }


    //Проверяем что он добавился
    if (set->size != sizeof(rightArray) / 4 + sizeof(addedAndDeletedArray) / 4)
        return 0;

    //Удаляем его
    for (int i = 0; i < sizeof(addedAndDeletedArray) / 4; ++i) {
        set_EXCL(set, addedAndDeletedArray[i]);
        set_EXCL(set, addedAndDeletedArray[i]);
        set_EXCL(set, addedAndDeletedArray[i]);
    }

    //Проверяем что addedAndDeletedArray удален корректно
    if (set->size != sizeof(rightArray) / 4)
        return 0;


    for (int j = 0; j < set->size; ++j)
        if (set->array[j] != rightArray[j])
            return 0;

    //Пробуем удалить первый элемент
    set_EXCL(set, rightArray[0]);

    //Провеярем, что удалили корректно
    for (int j = 0; j < set->size; ++j)
        if (set->array[j] != rightArray[j + 1])
            return 0;

    return 1;

}


int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 0;
    printf("Set Testing...\n\n");


    printf("set_contains...\n");
    maxTestDigit++;
    if (test_set_contains() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("set_INCL...\n");
    maxTestDigit++;
    if (test_set_INCL() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("set_EXCL...\n");
    maxTestDigit++;
    if (test_set_EXCL() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");

    return 0;

}