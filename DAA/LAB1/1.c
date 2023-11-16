#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n, choice;
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int array[n];
    printf("Enter 1 for random number input and 2 for input from disc file : ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        int limit;
        printf("Enter limit for array input : ");
        scanf("%d", &limit);
        srand(time(NULL));
        for (int i = 0; i < n; i++)
            array[i] = (rand() % limit) + 1;
    }
    else if (choice == 2)
    {
        FILE *file;
        file = fopen("numbers.dat", "r");
        for (int i = 0; i < n; i++)
            fscanf(file, "%d,", &array[i]);
    }
    else
        printf("Wrong choice");
    printf("Array Elements : ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    int largest_index = 0, smallest_index = 0;
    for (int i = 1; i < n; i++)
    {
        if (array[i] > array[largest_index])
            largest_index = i;

        if (array[i] < array[smallest_index])
            smallest_index = i;
    }

    int second_smallest = array[largest_index], second_largest = array[smallest_index];

    for (int i = 2; i < n - 1; i++)
    {
        if (array[i] > second_largest && array[i] != array[largest_index])
            second_largest = array[i];

        if (array[i] < second_smallest && array[i] != array[smallest_index])
            second_smallest = array[i];
    }
    printf("\nSecond smallest number : %d\n", second_smallest);
    printf("Second largest number : %d\n", second_largest);
    return 0;
}