#ifndef SORT
#define SORT
#include <stddef.h>
#include <string.h> 


void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(char** arr, size_t length)
{
    if (length < 2) return;
    size_t pivot_index = length / 2;
    char* pivot = arr[pivot_index];

    size_t i = 0, j = length - 1;
    while (i <= j)
    {
        while (strcmp(arr[i], pivot) < 0) i++;
        while (strcmp(arr[j], pivot) > 0) j--;
        if (i <= j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            if (j > 0) j--;
        }
    }
    if (j > 0) quick_sort(arr, j + 1);
    quick_sort(arr + i, length - i);
}

#endif 