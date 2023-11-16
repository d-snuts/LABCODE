#include <stdio.h>
int main()
{
    int n;
    printf("Enter how many numbers you want to read from file : ");
    scanf("%d", &n);
    int array[n];
    FILE *file;
    file = fopen("duplicates.dat", "r");
    for (int i = 0; i < n; i++)
        fscanf(file, "%d", &array[i]);
    printf("\nThe content of the array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    int counter = 0, max_repeat, max_count = -1;
    for (int i = 0; i < n; i++)
    {
        int temp = 1;
        if (array[i] == -1)
            continue;

        for (int j = i + 1; j < n; j++)
        {

            if (array[i] == array[j])
            {
                temp++;
                array[j] = -1;
            }
        }
        if (temp > 1)
            counter++;
        if (max_count == -1 || temp > max_count)
        {
            max_repeat = array[i];
            max_count = temp;
        }
    }
    printf("\nTotal number of duplicate values : %d\n", counter);
    printf("The most repeating element in the array : %d", max_repeat);
    return 0;
}