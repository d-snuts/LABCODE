#include <stdio.h>
#include <stdlib.h>
struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
int main(int argc, char *argv[])
{
    int n;
    printf("Enter the number of students : ");
    scanf("%d", &n);
    struct person *per;
    FILE *myfile;
    myfile = fopen("data.dat", "r");
    // for (int i = 0; i < n; i++)
    // {
    per = (struct person *)malloc(sizeof(struct person));
    fscanf(myfile, "%i %s %i %i %i", &per->id, per->name, &per->age, &per->height, &per->weight);
    // fscanf(myfile, "%d ", &per[i]->age);
    // fscanf(myfile, "%d ", &per[i]->height);
    // fscanf(myfile, "%d ", &per[i]->weight);
    // fscanf(myfile, "%c", per[i]->name);
    printf("Hello\n");
    // }
    fclose(myfile);
    // for (int i = 0; i < n; i++)
    // {
    printf("ID : %d\n", per->id);
    printf("Name : %s\n", per->name);
    printf("Age : %d\n", per->age);
    printf("Height : %d\n", per->height);
    printf("Weight : %d\n", per->weight);
    // }
    return 0;
}