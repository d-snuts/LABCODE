#include <stdio.h>
int binary_search(int arr[], int size, int key)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

void insertion(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int x = binary_search(arr, i, arr[i]);
        int temp = arr[i];
        for (int j = i; j > x; j--)
            arr[j] = arr[j - 1];
        arr[x] = temp;
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
    int n;
    printf("Enter the size of array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Array before sort : ");
    display(arr, n);
    insertion(arr, n);
    printf("Array after sort : ");
    display(arr, n);
    return 0;
}
