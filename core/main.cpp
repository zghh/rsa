#include "integer.h"
#include "rsa.h"
#include "prime.h"
#include "common.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

const int COUNT = 100;
const int BITS[] = {256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096};

void init()
{
}

int main()
{
    init();
    int n = sizeof(BITS) / sizeof(BITS[0]);
    for (int i = 0; i < n; i++)
    {
        double generate = 0.0, encrypt = 0.0, decrypt = 0.0;
        for (int j = 0; j < COUNT; j++)
        {
            clock_t start = clock();
            RSA rsa = RSA(BITS[i]);
            clock_t end = clock();
            generate += (double)(end - start) / CLOCKS_PER_SEC;
            if (BITS[i] >= 2048)
                printf("Generate time = %.5f, index = %d\n", (double)(end - start) / CLOCKS_PER_SEC, j);
            char s[] = "Hello";
            char ciphertext[2000];
            char text[2000];
            start = clock();
            rsa.Encrypt(s, ciphertext);
            end = clock();
            encrypt += (double)(end - start) / CLOCKS_PER_SEC;
            // printf("Encrypt time = %.5f\n", (double)(end - start) / CLOCKS_PER_SEC);
            start = clock();
            rsa.Decrypt(ciphertext, text);
            end = clock();
            decrypt += (double)(end - start) / CLOCKS_PER_SEC;
            // printf("Decrypt time = %.2f\n", (double)(end - start) / CLOCKS_PER_SEC);
            // printf("%s\n", text);
        }
        printf("Number of bits = %d\n", BITS[i]);
        printf("Average generate time = %.5f\n", (double)generate / COUNT);
        printf("Average encrypt time = %.5f\n", (double)encrypt / COUNT);
        printf("Average decrypt time = %.5f\n", (double)decrypt / COUNT);
    }
    return 0;
}