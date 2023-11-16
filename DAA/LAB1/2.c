#include <stdio.h>
int main()
{
    int n;
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int array[n];
    printf("Enter the array elements : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("Input array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    int sum = 0;
    int prefixSum[n];
    for (int i = 0; i < n; i++)
    {
        sum = sum + array[i];
        prefixSum[i] = sum;
    }
    printf("\nOutput array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", prefixSum[i]);
    return 0;
}
