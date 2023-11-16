#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ns 1e+9
void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int N, int i)
{

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr[left] > arr[largest])
        largest = left;

    if (right < N && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapSort(int arr[], int N)
{

    for (int i = N / 2 - 1; i >= 0; i--)

        heapify(arr, N, i);

    for (int i = N - 1; i >= 0; i--)
    {

        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}
int main()
{
    clock_t start, end;
    double cpu_time_used;
    int n, choice;
    printf("Enter the no of elements : ");
    scanf("%d", &n);
    int arr[n];
    FILE *myfile;
    FILE *fp;

    myfile = fopen("inFile.dat", "r");
    fp = fopen("outFile.dat", "w");
    printf("\n*****OPENING DATA FILE*****\n");

    printf("\nBefore sorting content of input file : ");
    for (int i = 0; i < n; i++)
    {
        fscanf(myfile, "%d ", &arr[i]);
        printf("%d ", arr[i]);
    }

    start = clock();
    heapSort(arr, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nAfter sorting content of output file : ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", arr[i]);
        printf("%d ", arr[i]);
    }
    fclose(myfile);
    fclose(fp);
    printf("\nProgram took %.2f nanoseconds to execute \n", cpu_time_used * ns);
    return 0;
}