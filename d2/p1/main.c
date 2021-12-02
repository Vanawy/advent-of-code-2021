#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main (int argc, char *argv[])
{
    if (argc < 2) {
        printf("Excepted argument\n");
        return 1;
    }
    FILE *fp;
    fp = fopen( argv[1], "r");

    if (fp == NULL) {
      perror("Failed");
      return 2;
    }
        
    char buffer[MAX_LEN];

    int x, y;
    x = y = 0;

    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        char dir[MAX_LEN];
        int value = 0; 
        sscanf(buffer, "%s %d", dir, &value);

        if (strcmp(dir, "forward") == 0) {
            x += value;
        } else if(strcmp(dir, "up") == 0) {
            y -= value;
        } else if(strcmp(dir, "down") == 0) {
            y += value;
        }
    }
    
    printf("Result: \e[32m%d\e[0m\n", x * y);
    fclose(fp);
    return 0;
}