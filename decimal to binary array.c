#include <stdio.h>

int main()
{
    unsigned int decimal;
    int bits, i;

    printf("Enter decimal number: ");
    scanf("%u", &decimal);

    bits = sizeof(decimal) * 8;   // Number of bits

    printf("Total Bits = %d\n", bits);
    printf("Binary Number = ");

    for(i = bits - 1; i >= 0; i--)
    {
        printf("%d", (decimal >> i) & 1);
    }

    return 0;
}