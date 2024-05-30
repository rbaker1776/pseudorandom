#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int BITSTRING_SIZE = 16000000;


int main() 
{
    srand(time(NULL));
    FILE *file = fopen("randomness.txt", "wb");

    for (int i = 0; i < BITSTRING_SIZE / 4; i++) {
        int r = rand();
        fwrite(&r, sizeof(r), 1, file);
    }

    fclose(file);
    return 0;
}
