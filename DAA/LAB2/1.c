#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define bits 16

void binary(int x, int i, bool array[])
{
    int rem = x % 2;
    x = x / 2;
    array[i--] = rem;
    if (x <= 1)
    {
        array[i--] = x;
        return;
    }
    else
        binary(x, i, array);
}

int main(int argc, char *argv[])
{
    int n, num;
    n = atoi(argv[1]);
    FILE *temp;
    temp = fopen(argv[2], "w");
    for (int i = 4; i < argc; i++)
        fprintf(temp, "%d ", atoi(argv[i]));
    fclose(temp);
    FILE *file;
    FILE *FP;
    file = fopen(argv[2], "r");
    FP = fopen(argv[3], "w");
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d ", &num);
        int i = bits - 1;
        bool array[bits] = {0};
        binary(num, i, array);
        fprintf(FP, "The binary equivalent of %d is ", num);
        for (int z = 0; z < bits; z++)
            fprintf(FP, "%d", array[z]);

        fprintf(FP, "\n");
    }
    fclose(file);
    fclose(FP);
    FILE *fp;
    char line[100];
    fp = fopen(argv[3], "r");
    while (fgets(line, 100, fp))
        printf(line);
    fclose(fp);
    return 0;
}