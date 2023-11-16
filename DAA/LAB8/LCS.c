#include <stdio.h>
#include <string.h>
int main()
{
    char str1[100], str2[100];

    printf("Enter the first string : ");
    scanf("%s", str1);

    printf("Enter the second string : ");
    scanf("%s", str2);
    int m = strlen(str1);
    int n = strlen(str2);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    int matrix[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                matrix[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1])
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            else
                matrix[i][j] = (matrix[i - 1][j] > matrix[i][j - 1]) ? matrix[i - 1][j] : matrix[i][j - 1];
        }
    }

    int length = matrix[m][n];

    char lcs[length + 1];
    lcs[length] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs[--length] = str1[i - 1];
            i--;
            j--;
        }
        else if (matrix[i - 1][j] > matrix[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS : %s\n", lcs);
    printf("LCS Length : %d\n", strlen(lcs));

    return 0;
}