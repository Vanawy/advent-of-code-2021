#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define FISH_STATES 9

int fgetnumbers(FILE *fp, int **results);
void print_state(long long int *types);

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    long long int state[FISH_STATES] = {0};

    printf("Trying to read line\n");
    int *fishes = NULL;
    int count = fgetnumbers(fp, &fishes);
    for (size_t i = 0; i < count; i++)
    {
        state[fishes[i]]++;
    }
    fclose(fp);

    printf("Initial state:\n");
    print_state(state);

    int max_days = 256;
    long long int total = 0;

    for (int i = 1; i <= max_days; i++)
    {
        long long int new_fishes = state[0];
        long long int new_state[FISH_STATES] = {0};

        for (int j = FISH_STATES - 1; j >= 1; j--)
        {
            new_state[j - 1] = state[j];
        }
        new_state[6] += state[0];

        new_state[8] = new_fishes;

        total = 0;
        for (int j = 0; j < FISH_STATES; j++)
        {
            state[j] = new_state[j];
            total += state[j];
        }
        

        printf("After Day %d (Total - %lld):\n", i, total);
        print_state(state);
    }
    
    
    printf("Result: \e[32m%lld\e[0m\n", total);
    return 0;
}

void print_state(long long int *types)
{
    for (int i = FISH_STATES - 1; i >= 0; i--)
    {
        printf("%d:\t%lld\n", i, types[i]);
    }
    printf("\n");
}

int fgetnumbers(FILE *fp, int **results)
{
    int count = 0;
    char c;
    const int max_digits = 2;
    char number[3] = "  \0";
    int digits = 0;

    int *numbers;
    int max_numbers = 2;
    numbers = (int *) calloc(max_numbers, sizeof(int));

    while((c = fgetc(fp))){
        bool last = (c == '\n' || c == EOF);
        if (last || c == ','|| c == ' ' || digits == max_digits) {
            if (digits == 0) {
                if (last) break;
                continue;
            }
            numbers[count++] = atoi(number);
            number[0] = ' ';
            number[1] = ' ';
            digits = 0;
            if (count >= max_numbers) {
                max_numbers <<= 1;
                numbers = (int *) realloc(numbers, max_numbers * sizeof(int));
            }
            if (last) break;
            continue;
        }
        number[digits++] = c;
    }
    if(*results != NULL) {
        free(*results);
    }
    *results = numbers;
    
    return count;
}
