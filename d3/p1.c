#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }
        
    char line[MAX_LEN];
    int data[MAX_LEN] = {0};
    int len = 0;

    while (fgets(line, MAX_LEN, fp))
    {
        len = strcspn(line, "\n");
        line[len] = 0;
        for (size_t i = 0; i < len; i++)
        {
            char c = line[i];
            if(c == '0') data[i]--; else
            if(c == '1') data[i]++;
        }
    }

    int gamma = 0; 
    int eps = 0;
    for (size_t i = 0; i < len; i++)
    {
        int k = len - i -1;
        if (data[i] > 0) {
            gamma = (1 << k) | gamma;
        } else {
            eps = (1 << k) | eps;
        }
    }
    
    
    printf("Result: \e[32m%d * %d = %d\e[0m\n", gamma, eps, gamma * eps);
    fclose(fp);
    return 0;
}
