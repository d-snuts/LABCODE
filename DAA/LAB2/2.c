#include <stdio.h>
#include <stdlib.h>
int GCD(int x, int y)
{
    int temp = x;
    x = y % x;
    y = temp;
    if (x == 0)
        return y;
    else
        GCD(x, y);
}
int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    FILE *temp;
    temp = fopen(argv[2], "w");
    for (int i = 4; i < argc; i++)
        fprintf(temp, "%d ", atoi(argv[i]));
    fclose(temp);
    FILE *file;
    file = fopen(argv[2], "r");
    FILE *fp;
    fp = fopen(argv[3], "w");
    int num1, num2, result;
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d %d", &num1, &num2);
        if (num1 > num2)
            result = GCD(num2, num1);
        else
            result = GCD(num1, num2);

        fprintf(fp, "The GCD of %d and %d is %d\n", num1, num2, result);
    }
    fclose(file);
    fclose(fp);
    FILE *FP;
    FP = fopen(argv[3], "r");
    char line[100];
    fp = fopen(argv[3], "r");
    while (fgets(line, 100, FP))
        printf(line);
    fclose(FP);
    return 0;
}