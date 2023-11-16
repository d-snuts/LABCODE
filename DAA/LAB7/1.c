#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int generateRandomNumber(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

double calculateMean(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return (double)sum / n;
}

double calculateMedian(int arr[], int n)
{
    double median;
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (temp[i] > temp[j])
            {
                int tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }

    if (n % 2 == 0)
    {
        median = (temp[(n - 1) / 2] + temp[n / 2]) / 2.0;
    }
    else
    {
        median = temp[n / 2];
    }

    return median;
}

int calculateMode(int arr[], int n)
{
    int maxCount = 0, mode = -1;

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            mode = arr[i];
        }
    }

    return mode;
}

double calculateStandardDeviation(int arr[], int n, double mean)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum / n);
}

double calculateVariance(int arr[], int n, double mean)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sum / n;
}

int main()
{
    int n, choice;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));

    if (array == NULL)
    {
        printf("Memory allocation failed.");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        array[i] = generateRandomNumber(1, 100);
    }

    printf("Array elements: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Calculate Mean\n");
        printf("2. Calculate Median\n");
        printf("3. Calculate Mode\n");
        printf("4. Calculate Standard Deviation\n");
        printf("5. Calculate Variance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Mean: %.2lf\n", calculateMean(array, n));
            break;
        case 2:
            printf("Median: %.2lf\n", calculateMedian(array, n));
            break;
        case 3:
            printf("Mode: %d\n", calculateMode(array, n));
            break;
        case 4:
            printf("Standard Deviation: %.2lf\n", calculateStandardDeviation(array, n, calculateMean(array, n)));
            break;
        case 5:
            printf("Variance: %.2lf\n", calculateVariance(array, n, calculateMean(array, n)));
            break;
        case 6:
            free(array);
            exit(0);
        default:
            printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
