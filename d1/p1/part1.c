#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main (void)
{
    FILE *fp;
    fp = fopen("d1/p1/my.in", "r");

    if (fp == NULL) {
      perror("Failed");
      return 1;
    }

    int prev = -1;
    int count = 0;
        
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        int n = atoi(buffer);
        if (prev == -1) {
            prev = n;
            continue;
        }
        if (n > prev) {
            count++;
        }
        prev = n;

    }
    printf("%d\n", count);
    fclose(fp);
    return 0;
}