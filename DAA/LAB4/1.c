#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ns 1e+9
int comparison = 0;
void merge(int arr[], int low, int mid, int high)
{

    int array[low + high + 1];
    int i = 0;
    int left = low;
    int right = mid + 1;
    while (left <= mid && right <= high)
    {
        if (arr[left] < arr[right])
        {
            array[i] = arr[left];
            left++;
            i++;
            comparison++;
        }
        else
        {
            array[i] = arr[right];
            right++;
            i++;
            comparison++;
        }
    }
    while (left <= mid)
    {
        array[i] = arr[left];
        left++;
        i++;
        comparison++;
    }
    while (right <= high)
    {
        array[i] = arr[right];
        right++;
        i++;
        comparison++;
    }
    for (int i = low; i <= high; i++)
        arr[i] = array[i - low];
}
void mergeSort(int arr[], int low, int high)
{
    if (low == high)
        return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
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
    printf("Enter 1 for Ascending Data, 2 for Descending Data and 3 forRandom Data : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        myfile = fopen("inAsce.dat", "r");
        fp = fopen("outMergeAsce.dat", "w");
        printf("\n*****OPENING ASCENDING DATA FILE*****\n");
        break;
    case 2:
        myfile = fopen("inDesc.dat", "r");
        fp = fopen("outMergeDesc.dat", "w");
        printf("\n*****OPENING DESCENDING DATA FILE*****\n");
        break;
    case 3:
        myfile = fopen("inRand.dat", "r");
        fp = fopen("outMergeRand.dat", "w");
        printf("\n*****OPENING RANDOM DATA FILE*****\n");
        break;
    default:
        printf("\nERROR\n");
        exit(0);
    }
    printf("\nBefore sorting content of input file : ");
    for (int i = 0; i < n; i++)
    {
        fscanf(myfile, "%d ", &arr[i]);
        printf("%d ", arr[i]);
    }

    start = clock();
    mergeSort(arr, 0, n - 1);
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
    printf("\nNo of comparision : %d\n", comparison);
    printf("Program took %.2f nanoseconds to execute \n", cpu_time_used * ns);
    return 0;
}