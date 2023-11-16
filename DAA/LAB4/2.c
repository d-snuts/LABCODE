#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int counter = 0;
int comparison = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int piv_index(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j)
    {

        while (pivot >= arr[i] && i < high)
        {
            i++;
            comparison++;
        }
        while (pivot < arr[j] && j > low)
        {
            j--;
            comparison++;
        }
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
            comparison++;
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}
void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        counter++;
        int pivot_index = piv_index(arr, low, high);
        quicksort(arr, low, pivot_index - 1);
        quicksort(arr, pivot_index + 1, high);
    }
}
int main()
{
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
        fp = fopen("outQuickAsce.dat", "w");
        printf("\n*****OPENING ASCENDING DATA FILE*****\n");
        break;
    case 2:
        myfile = fopen("inDesc.dat", "r");
        fp = fopen("outQuickDesc.dat", "w");
        printf("\n*****OPENING DESCENDING DATA FILE*****\n");
        break;
    case 3:
        myfile = fopen("inRand.dat", "r");
        fp = fopen("outQuickRand.dat", "w");
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

    quicksort(arr, 0, n - 1);

    printf("\nAfter sorting content of output file : ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", arr[i]);
        printf("%d ", arr[i]);
    }
    fclose(myfile);
    fclose(fp);
    printf("\nNo of comparision : %d\n", comparison);
    // printf("Counter : %d\n", counter);
    if (counter == n - 1)
        printf("Scenario : Worst case\n");
    else if ((double)counter <= log2(n))
        printf("Scenario : Best Case\n");
    else
        printf("Scenario : Average Case\n");
    return 0;
}
