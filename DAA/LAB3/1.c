#include <stdio.h>
int comparison = 0;
int binary_search(int arr[], int n, int key)
{
    int left = 0, mid, right = n - 1;
    mid = (right + left) / 2;
    while (right > left)
    {
        comparison++;
        if (arr[mid] > key)
            right = mid;
        else if (arr[mid] < key)
            left = mid;
        else
            return mid;
        mid = (right + left) / 2;
    }
    return -1;
}
int main()
{
    int n, index, key;
    printf("Enter the number of elements in the array : ");
    scanf("%d", &n);
    int array[n];
    printf("Enter the sorted array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("Enter the key to be searched : ");
    scanf("%d", &key);
    index = binary_search(array, n, key);
    int temp = index;
    while (array[--temp] == key)
    {
        comparison++;
        index--;
    }
    printf("%d found at index position %d\n", key, index);
    printf("No of comparisions : %d\n", comparison);
    return 0;
}