#include <stdio.h>
#include <stdlib.h>

struct ITEM
{
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;
};

void maxHeapify(struct ITEM arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
    {
        largest = left;
    }

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
    {
        largest = right;
    }

    if (largest != i)
    {

        struct ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        maxHeapify(arr, n, largest);
    }
}

void heapSort(struct ITEM arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {

        struct ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        maxHeapify(arr, i, 0);
    }
}

int main()
{
    int n, capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    for (int i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%lf %lf", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &capacity);

    heapSort(items, n);

    double maxProfit = 0.0;

    printf("Item No\tProfit\tWeight\tAmount to be taken\n");
    for (int i = 0; i < n; i++)
    {
        if (capacity >= items[i].item_weight)
        {
            printf("%d\t%.6lf\t%.6lf\t1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            capacity -= items[i].item_weight;
            maxProfit += items[i].item_profit;
        }
        else
        {
            double fraction = (double)capacity / items[i].item_weight;
            printf("%d\t%.6lf\t%.6lf\t%.6lf\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            maxProfit += (fraction * items[i].item_profit);
            break;
        }
    }

    printf("Maximum profit: %.6lf\n", maxProfit);

    return 0;
}