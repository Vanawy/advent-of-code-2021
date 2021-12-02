#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256
#define SAMPLE_SIZE 3
#define SAMPLE_BUF_SIZE (SAMPLE_SIZE + 1)

int main (void)
{
    FILE *fp;
    fp = fopen("d1/p2/my.in", "r");

    if (fp == NULL) {
      perror("Failed");
      return 1;
    }

    int prev_sample_sum = -1;
    int count = 0;
    int line_counter = 0;
        
    char buffer[MAX_LEN];
    int sample[SAMPLE_BUF_SIZE];

    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        int n = atoi(buffer);
        sample[line_counter % SAMPLE_BUF_SIZE] = n;

        if (line_counter + 1 < SAMPLE_SIZE) {
            line_counter++;
            continue;
        }

        int current_sample_sum = 0;
        for (int i = 0; i < SAMPLE_SIZE; i++) {
            int index = (line_counter - SAMPLE_SIZE + i) % SAMPLE_BUF_SIZE;
            current_sample_sum += sample[index];
        }

        printf("%d\n", current_sample_sum);

        if (prev_sample_sum != -1 && current_sample_sum > prev_sample_sum) {
            count++;
        }
        prev_sample_sum = current_sample_sum;
        line_counter++;
    }
    printf("Result: \e[32m%d\e[0m\n", count);
    fclose(fp);
    return 0;
}