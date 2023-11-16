#include <stdio.h>
#include <math.h>

double x[] = {3, 6, 19, 9, 29, 12, 39, 15};
double y[] = {6, 9, 29, 12, 39, 15, 49};

double calculateMean(double arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

double calculateMedian(double arr[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    if (n % 2 == 0)
    {

        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }
    else
    {

        return arr[n / 2];
    }
}

int main()
{
    int n = sizeof(x) / sizeof(x[0]);

    double xMean = calculateMean(x, n);
    double yMean = calculateMean(y, n);
    double xMedian = calculateMedian(x, n);
    double yMedian = calculateMedian(y, n);

    printf("Mean of X: %.2lf\n", xMean);
    printf("Median of X: %.2lf\n", xMedian);
    printf("Mean of Y: %.2lf\n", yMean);
    printf("Median of Y: %.2lf\n", yMedian);

    if (n >= 3)
    {
        double diffX = x[1] - x[0];
        double diffY = y[1] - y[0];
        if ((y[2] - y[1]) / diffY == (y[1] - y[0]) / diffY)
        {
            printf("The relationship is linear.\n");
        }
        else if ((y[2] - y[1]) / diffY - (y[1] - y[0]) / diffY == (y[2] - y[1] - y[1] + y[0]) / (diffY * diffX))
        {
            printf("The relationship is quadratic.\n");
        }
        else
        {
            printf("The relationship is cubic or higher order.\n");
        }
    }

    double givenX = 18;
    double estimatedY;

    printf("Estimated Y for X = %.2lf: %.2lf\n", givenX, estimatedY);

    return 0;
}
