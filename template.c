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

    while (fgets(line, MAX_LEN, fp))
    {
        line[strcspn(line, "\n")] = 0;
    }
    
    printf("Result: \e[32m%d\e[0m\n", -1);
    fclose(fp);
    return 0;
}
