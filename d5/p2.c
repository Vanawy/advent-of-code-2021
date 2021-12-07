#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define SIZE 10

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

void print_line(LINE line)
{
    printf("%d,%d -> %d,%d\n",
        line.a.x, line.a.y,
        line.b.x, line.b.y
    );
}

bool fgetline(FILE *fp, LINE *result);

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
        LINE line;
        if (!fgetline(fp, &line)) {
            continue;
        }

        int ii, ji;
        int id = line.b.x - line.a.x;
        if (id == 0) {
            ii = 0;
        } else if(id > 0) {
            ii = 1;
        } else {
            ii = -1;
        }
        
        int jd = line.b.y - line.a.y;
        if (jd == 0) {
            ji = 0;
        } else if(jd > 0) {
            ji = 1;
        } else {
            ji = -1;
        }
        for (
            int i = line.a.x, j = line.a.y; 
            (ii > 0 ? i <= line.b.x : i >= line.b.x) 
            && (ji > 0 ? j <= line.b.y : j >= line.b.y); 
            i += ii, j += ji
        )
        {
            map[i + j * SIZE]++;
        }
    }

    int answer = 0;
    for (size_t i = 0; i < SIZE * SIZE; i++)
    {
        if (map[i] > 1) answer++;
    }
    
    printf("Result: \e[32m%d\e[0m\n", answer);
    fclose(fp);
    return 0;
}

bool fgetline(FILE *fp, LINE *result)
{
    LINE line;
    int parsed = fscanf(
        fp, "%d,%d -> %d,%d\n", 
        &line.a.x, &line.a.y,
        &line.b.x, &line.b.y
    );
    if (parsed != 4) {
        return false;
    }
    *result = line;
    return true;
}
