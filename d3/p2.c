#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define MAX_ROWS 1024

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    char lines[MAX_ROWS][MAX_LEN] ={{0}};
        
    char line[MAX_LEN];
    int len = 0;
    int i = 0;
    
    while (fgets(line, MAX_LEN, fp))
    {
        len = strcspn(line, "\n");
        line[len] = 0;
        strcpy(lines[i++], line);
    }

    // int o = 0;
    // int co2 = 0;

    char o_pattern[MAX_LEN];
    char c_pattern[MAX_LEN];

    bool o_mask[MAX_ROWS];
    bool c_mask[MAX_ROWS];

    for (size_t i = 0; i < MAX_ROWS; i++)
    {
        o_mask[i] = c_mask[i] = true;
    }
    

    for (size_t i = 0; i < 1; i++)
    {
        int o_balance = 0;
        int c_balance = 0;
        for (size_t j = 0; j < MAX_ROWS && lines[j] != 0; j++)
        {
            char c = lines[j][i];
            if (o_mask[j]) {
                if (c == '0') o_balance--; else
                if (c == '1') o_balance++;
            } 
            if (c_mask[j]) {
                if (c == '0') c_balance--; else
                if (c == '1') c_balance++;
            }
        }
        printf("%d %d\n", o_balance, c_balance);
        o_pattern[i] = o_balance > 0 ? '1' : '0';
        c_pattern[i] = c_balance > 0 ? '0' : '1';
        printf("%s %s\n", o_pattern, c_pattern);
        for (size_t j = 0; j < MAX_ROWS && lines[j] != 0; j++)
        {
            char c = lines[j][i];
            printf("%c", c);
            if (c != o_pattern[i]) {
                o_mask[j] = false;
            }
            if (c != c_pattern[i]) {
                o_mask[j] = false;
            }
        }
        printf("\n");
    }

    for (size_t i = 0; i < 12; i++)
    {
        printf("%d %s\n", c_mask[i], lines[i]);
    }
    

    printf("___\n%s %s\n", o_pattern, c_pattern);
    
    
    // printf("Result: \e[32m%d * %d = %d\e[0m\n", gamma, eps, gamma * eps);
    fclose(fp);
    return 0;
}
