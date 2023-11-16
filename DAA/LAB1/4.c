#include <stdio.h>
void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
void ROTATE_RIGHT(int arr[], int x)
{
    for (int i = x - 1; i > 0; i--)
        EXCHANGE(&arr[i], &arr[i - 1]);
}
int main()
{
    int n, element;
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int array[n];
    printf("Enter the array elements : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("Enter the no. of element you want to rotate right from first : ");
    scanf("%d", &element);
    printf("\nInput array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    ROTATE_RIGHT(array, element);
    printf("\nOutput array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    return 0;
}
