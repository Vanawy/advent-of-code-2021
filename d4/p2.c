#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define BOARD_SIZE 25

/**
 * @brief 
 * 
 * @param fp file pointer
 * @param results Results array
 * @return int Count of numbers 
 */
int fgetnumbers(FILE *fp, int **results);

void printnumbers(int *numbers, int count);
void printboard(int *board);
void print_marked_board(int *board, int markers);
const char *byte_to_binary(int x, int bits);
const char *byte_to_binary_25(int x);

// void board(int **numbers, int *dest);

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    int *numbers = NULL;
    int count = fgetnumbers(fp, &numbers);
    printnumbers(numbers, count);
    
    // PREPARE BOARDS
    int limit_boards_count = 2;
    int (*boards)[BOARD_SIZE];
    boards = malloc(BOARD_SIZE * limit_boards_count * sizeof(int));
    int board_n = 0;
    int n = 0;
    while (!feof(fp))
    {
        printf("Trying to read line\n");
        int *line = NULL;
        int count = fgetnumbers(fp, &line);
        if (count < 1) continue;
        for (size_t i = 0; i < count; i++)
        {
            boards[board_n][n + i] = line[i];
        }
        n += count;
        if (n >= BOARD_SIZE) {
            printboard(boards[board_n]);
            board_n++;
            n = 0;

            if (board_n >= limit_boards_count) {
                limit_boards_count <<= 1;
                boards = realloc(boards, BOARD_SIZE * limit_boards_count * sizeof(int));
            }
        }
        free(line);
    }
    fclose(fp);

    printf("%d boards found\n", board_n);

    int marked[board_n];
    int won_number_indexes[board_n];
    for (size_t i = 0; i < board_n; i++)
    {
        marked[i] = 0;
        won_number_indexes[i] = -1;
    }
    
    

    // GAME
    int last_won_board_index = -1;
    int last_number = -1;
    for (size_t n_index = 0; n_index < count && last_won_board_index < 0; n_index++)
    {
        int number = numbers[n_index];
        last_number = number;
        printf("Current Number: %d\n", number);
        // mark numbers on boards
        for (size_t i = 0; i < board_n; i++)
        {
            for (size_t j = 0; j < BOARD_SIZE; j++)
            {
                if (boards[i][j] == number) marked[i] |= 1 << (BOARD_SIZE - j - 1);
            }
        }
        if (n_index < 5) continue;
        int board_index = -1;
        for (size_t i = 0; i < board_n; i++)
        {
            if (won_number_indexes[i] > 0) continue; 
            board_index = i;
            for (size_t j = 0; j < 5; j++)
            {
                int row_mask = 0b11111 << j * 5;
                if ((marked[i] & row_mask) == row_mask) {
                    won_number_indexes[i] = n_index;
                }
                int col_mask = 0b100001000010000100001 << j;
                if ((marked[i] & col_mask) == col_mask) {
                    won_number_indexes[i] = n_index;
                }
            }
        }
        bool all_boards_won = true;
        for (size_t i = 0; i < board_n; i++)
        {
            if (won_number_indexes[i] < 0) all_boards_won = false;
        }
        if (all_boards_won) last_won_board_index = board_index;
    }

    print_marked_board(boards[last_won_board_index], marked[last_won_board_index]);   

    int result = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        if (!(marked[last_won_board_index] & 1 << (BOARD_SIZE - i - 1))) {
            result += boards[last_won_board_index][i];
        }
    }
    
    printf("Result: \e[32m%d\e[0m\n", result * last_number);
    free(numbers);
    free(boards);
    return 0;
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

void printnumbers(int *numbers, int count)
{
    if (count < 1) return;
    for (size_t i = 0; i < count; i++)
    {
        printf("%d,", numbers[i]);
    }
    printf("\n");    
}

void printboard(int *board)
{
    print_marked_board(board, 0);
}

void print_marked_board(int *board, int markers)
{
    printf("-----------------\n");  
    for (size_t i = 0; i < BOARD_SIZE;)
    {
        if (markers & 1 << (BOARD_SIZE - i - 1)) {
            // printf("▇\t");
            printf("\e[32m%d\e[0m\t", board[i]);
        } else {
            printf("%d\t", board[i]);
        }
        if (++i % 5 == 0) 
            printf("\n");  
    }
    printf("\n-----------------\n");  
}

const char *byte_to_binary_25(int x)
{
    return byte_to_binary(x, 25);
}

const char *byte_to_binary
(
    int x,
    int bits
)
{
    static char b[40];
    b[0] = '\0';

    int z;
    int i = 1;
    for (z = 1 << (bits - 1); z > 0; z >>= 1, i++)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
        if (i % 5 == 0) strcat(b, "\n");
    }

    return b;
}

