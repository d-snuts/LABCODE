#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubblesort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}
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
        }
        else
        {
            array[i] = arr[right];
            right++;
            i++;
        }
    }
    while (left <= mid)
    {
        array[i] = arr[left];
        left++;
        i++;
    }
    while (right <= high)
    {
        array[i] = arr[right];
        right++;
        i++;
    }
    for (int i = low; i <= high; i++)
        arr[i] = array[i - low];
}
void mergeSort(int arr[], int low, int high, int k)
{
    if (high > low)
    {
        if (high - low + 1 > k)
        {
            int mid = (low + high) / 2;
            mergeSort(arr, low, mid, k);
            mergeSort(arr, mid + 1, high, k);
            merge(arr, low, mid, high);
        }
        else
        {
            bubblesort(arr + low, high - low + 1);
        }
    }
}
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
    int k, n;
    printf("Enter the value in which you want to divide the dataset : ");
    scanf("%d", &k);
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Array before sorting : ");
    display(arr, n);
    mergeSort(arr, 0, n - 1, k);
    printf("Array before sorting : ");
    display(arr, n);
    return 0;
}