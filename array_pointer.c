#include <stdio.h>
#include <stdlib.h>

int* freqOfElements(const int inputArr[], int size, int *maxOut) {
    // find the max value to size the frequency array
    int maxVal = inputArr[0];
    for (int i = 1; i < size; i++) {
        if (inputArr[i] > maxVal) maxVal = inputArr[i];
    }

    // frequency array indexed by value
    int *freqArr = (int*)calloc(maxVal + 1, sizeof(int));
    if (freqArr == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        freqArr[inputArr[i]]++;
    }

    *maxOut = maxVal;
    return freqArr;
}

int main() {
    int original[] = {1, 200, 200, 4000,4000};
    int size = sizeof(original)/sizeof(original[0]);
    int maxVal;

    int *result = freqOfElements(original, size, &maxVal);
    if (result != NULL) {
        for (int i = 0; i <= maxVal; i++) {
            if (result[i] > 0)
                printf("%d:%d\n", i, result[i]);
        }
        free(result);
    }
    return 0;
}