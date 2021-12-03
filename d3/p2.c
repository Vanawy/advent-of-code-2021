#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define MAX_ROWS 1024

int frombinary(char *binary);

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

    bool o_ignore[MAX_ROWS];
    bool c_ignore[MAX_ROWS];

    int o_count = rows;
    int c_count = rows;

    for (size_t i = 0; i < len; i++)
    {
        int o_balance = 0;
        int c_balance = 0;
        for (size_t j = 0; j < rows; j++)
        {
            char c = lines[j][i];
            if (o_count > 1 && !o_ignore[j]) {
                if (c == '0') o_balance--; else
                if (c == '1') o_balance++;
            } 
            if (c_count > 1 && !c_ignore[j]) {
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
            if (o_count > 1 && !o_ignore[j] && c != o_pattern[i]) {
                o_ignore[j] = true;
                o_count--;
            }
            if (c_count > 1 && !c_ignore[j] && c != c_pattern[i]) {
                c_ignore[j] = true;
                c_count--;
            }
        }
    }

    int o = 0;
    int co2 = 0;

    for (size_t i = 0; i < rows; i++)
    {
        if (!o_ignore[i]) {
            printf("CO2: %s\n", lines[i]);
            o = frombinary(lines[i]);
        }

        if (!c_ignore[i]) {
            printf("O: %s\n", lines[i]);
            co2 = frombinary(lines[i]);
        }
    }
    

    printf("___\n%d * %d = %d\n", o, co2, o * co2);
    
    fclose(fp);
    return 0;
}

int frombinary(char *binary)
{
    int r = 0;
    int len = strlen(binary);
    
    for (size_t i = 0; i < len; i++)
    {
        int k = len - i -1;
        if (binary[i] == '1') {
            r = (1 << k) | r;
        }
    }
    return r; 
}
