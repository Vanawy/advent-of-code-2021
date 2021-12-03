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
    int rows = 0;
    
    while (fgets(line, MAX_LEN, fp))
    {
        len = strcspn(line, "\n");
        line[len] = 0;
        strcpy(lines[i++], line);
        rows++;
    }

    char o_pattern[MAX_LEN];
    char c_pattern[MAX_LEN];

    bool o_mask[MAX_ROWS];
    bool c_mask[MAX_ROWS];

    for (size_t i = 0; i < MAX_ROWS; i++)
    {
        o_mask[i] = c_mask[i] = true;
    }

    int o_count = rows;
    int c_count = rows;

    for (size_t i = 0; i < len; i++)
    {
        int o_balance = 0;
        int c_balance = 0;
        for (size_t j = 0; j < rows; j++)
        {
            char c = lines[j][i];
            if (o_count > 1 && o_mask[j]) {
                if (c == '0') o_balance--; else
                if (c == '1') o_balance++;
            } 
            if (c_count > 1 && c_mask[j]) {
                if (c == '0') c_balance--; else
                if (c == '1') c_balance++;
            }
        }
        if (o_count > 1)
            o_pattern[i] = (o_balance >= 0) ? '1' : '0';
        if (c_count > 1)
            c_pattern[i] = (c_balance < 0) ? '1' : '0';
        
        for (size_t j = 0; j < rows; j++)
        {
            char c = lines[j][i];
            if (o_count > 1 && o_mask[j] && c != o_pattern[i]) {
                o_mask[j] = false;
                o_count--;
            }
            if (c_count > 1 && c_mask[j] && c != c_pattern[i]) {
                c_mask[j] = false;
                c_count--;
            }
        }
    }

    int o = 0;
    int co2 = 0;

    for (size_t i = 0; i < rows; i++)
    {
        if (o_mask[i]) {
            printf("CO2: %s\n", lines[i]);
            for (size_t j = 0; j < len; j++)
            {
                int k = len - j -1;
                if (lines[i][j] == '1') {
                    o = (1 << k) | o;
                }
            }
        }

        if (c_mask[i]) {
            printf("O: %s\n", lines[i]);
            for (size_t j = 0; j < len; j++)
            {
                int k = len - j -1;
                if (lines[i][j] == '1') {
                    co2 = (1 << k) | co2;
                }
            }
        }
    }
    

    printf("___\n%d * %d = %d\n", o, co2, o * co2);
    
    
    // printf("Result: \e[32m%d * %d = %d\e[0m\n", gamma, eps, gamma * eps);
    fclose(fp);
    return 0;
}
