#include <stdio.h>
#include <stdlib.h>

int insertion_Sort(int arr[], int size)
{
    int counter = 0;
    int temp, index;
    for (int i = 1; i < size; i++)
    {
        temp = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (temp < arr[j])
            {
                counter++;
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return counter;
}
int main(int argc, char *argv[])
{
    int n, choice;
    printf("Enter the no of elements : ");
    scanf("%d", &n);
    int array[n];
    FILE *myfile;
    FILE *fp;
    printf("Enter 1 for Ascending Data, 2 for Descending Data and 3 forRandom Data : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        myfile = fopen("inAsce.dat", "r");
        fp = fopen("outInsAsce.dat", "w");
        printf("\n*****OPENING ASCENDING DATA FILE*****\n");
        break;
    case 2:
        myfile = fopen("inDesc.dat", "r");
        fp = fopen("outInsDesc.dat", "w");
        printf("\n*****OPENING DESCENDING DATA FILE*****\n");
        break;
    case 3:
        myfile = fopen("inRand.dat", "r");
        fp = fopen("outInsRand.dat", "w");
        printf("\n*****OPENING RANDOM DATA FILE*****\n");
        break;
    default:
        printf("\nERROR\n");
        exit(0);
    }
    printf("\nBefore sorting content of input file : ");
    for (int i = 0; i < n; i++)
    {
        fscanf(myfile, "%d ", &array[i]);
        printf("%d ", array[i]);
    }
    int comparison = insertion_Sort(array, n);
    printf("\nAfter sorting content of output file : ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", array[i]);
        printf("%d ", array[i]);
    }
    fclose(myfile);
    fclose(fp);
    printf("\nNo of comparision : %d", comparison);
    printf("\nScenario : ");
    if (comparison == 0)
        printf("Best Case");
    else
        printf("Worst case");
    return 0;
}