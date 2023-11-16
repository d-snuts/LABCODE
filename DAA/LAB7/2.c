#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_NUMBERS 100
#define NUM_CLASS_INTERVALS 6

struct ClassInterval
{
    char name[20];
    double start;
    double end;
    double midpoint;
    int frequency;
    int cumulative_frequency;
};

int main()
{

    srand(time(NULL));

    double random_numbers[NUM_RANDOM_NUMBERS];
    for (int i = 0; i < NUM_RANDOM_NUMBERS; i++)
    {
        random_numbers[i] = (double)(rand() % 60001);
    }

    struct ClassInterval class_intervals[NUM_CLASS_INTERVALS] = {
        {"a. < 100", 0, 100, 50, 0, 0},
        {"b. 100 to 500", 100, 500, 300, 0, 0},
        {"c. 500 to 5000", 500, 5000, 2750, 0, 0},
        {"d. 5000 to 10000", 5000, 10000, 7500, 0, 0},
        {"e. 10000 to 50000", 10000, 50000, 30000, 0, 0},
        {"f. > 50000", 50000, 60000, 55000, 0, 0}};

    for (int i = 0; i < NUM_RANDOM_NUMBERS; i++)
    {
        for (int j = 0; j < NUM_CLASS_INTERVALS; j++)
        {
            if (random_numbers[i] >= class_intervals[j].start && random_numbers[i] < class_intervals[j].end)
            {
                class_intervals[j].frequency++;
            }
        }
    }

    int cumulative_frequency = 0;
    for (int i = 0; i < NUM_CLASS_INTERVALS; i++)
    {
        cumulative_frequency += class_intervals[i].frequency;
        class_intervals[i].cumulative_frequency = cumulative_frequency;
    }

    printf("Class interval\tMid point\tFrequency\tCumulative Frequency\n");
    for (int i = 0; i < NUM_CLASS_INTERVALS; i++)
    {
        printf("%s\t%.2lf\t\t%d\t\t%d\n", class_intervals[i].name, class_intervals[i].midpoint, class_intervals[i].frequency, class_intervals[i].cumulative_frequency);
    }

    return 0;
}
