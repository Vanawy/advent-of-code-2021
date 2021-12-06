#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define SIZE 1000

typedef struct point
{
    int x;
    int y;
} POINT;

typedef struct line
{
    POINT a;
    POINT b;
} LINE;

LINE fgetline(FILE *fp);

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    int map[SIZE * SIZE] = {0};
    
    
    while (!feof(fp))
    {
        LINE line = fgetline(fp);
        int ai, bi, aj, bj;
        ai = aj = 0;
        bi = bj = -1;
        if(line.b.y == line.a.y)
        {
            ai = line.a.x < line.b.x ? line.a.x : line.b.x;
            bi = line.a.x < line.b.x ? line.b.x : line.a.x;
            aj = bj = line.a.y;
        }else if(line.b.x == line.a.x)
        {
            aj = line.a.y < line.b.y ? line.a.y : line.b.y;
            bj = line.a.y < line.b.y ? line.b.y : line.a.y;
            ai = bi = line.a.x;
        }
        for (int i = ai; i <= bi; i++)
        {
            for (int j = aj; j <= bj; j++)
            {
                map[i + j * SIZE]++;
            }
        }
    }

    int result = 0;
    for (size_t i = 0; i < SIZE * SIZE; i++)
    {
        if (map[i] > 1) result++;
    }
        
    printf("Result: \e[32m%d\e[0m\n", result);
    fclose(fp);
    return 0;
}

LINE fgetline(FILE *fp)
{
        
    char str[MAX_LEN];
    fgets(str, MAX_LEN, fp);
    int len = strcspn(str, "\n");
    str[len] = 0;

    char buf[] = "   \0";
    int buf_i = 0;

    int num[4];
    int num_i = 0;

    for(int i = 0; i <= len; i++) 
    {
        char c = str[i];
        if (c < '0' || c > '9' || i == len) {
            if (buf_i > 0) {
                num[num_i++] = atoi(buf);
                buf_i = 0;
                buf[0] = ' ';
                buf[1] = ' ';
                buf[2] = ' ';
            }
            continue;
        }
        buf[buf_i++] = c;
    }

    LINE line;
    line.a.x = num[0];
    line.a.y = num[1];
    line.b.x = num[2];
    line.b.y = num[3];
    return line;
}
