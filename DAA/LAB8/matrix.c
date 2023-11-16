#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int dims[n + 1];
    for (int i = 0; i < n; i++)
    {
        printf("Enter row and column size of A%d: ", i + 1);
        scanf("%d %d", &dims[i], &dims[i + 1]);
    }
    n = n + 1;
    int M[n][n];
    int S[n][n];

    for (int i = 1; i < n; i++)
        M[i][i] = 0;

    for (int chain_len = 2; chain_len < n; chain_len++)
    {
        for (int i = 1; i < n - chain_len + 1; i++)
        {
            int j = i + chain_len - 1;
            M[i][j] = __INT32_MAX__;
            for (int k = i; k <= j - 1; k++)
            {
                int cost = M[i][k] + M[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < M[i][j])
                {
                    M[i][j] = cost;
                    S[i][j] = k;
                }
            }
        }
    }

    printf("M Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i <= j)
                printf("%d ", M[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i < j)
                printf("%d ", S[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    printf("The optimal ordering of the given matrices requires %d scalar multiplications\n", M[1][n - 1]);

    return 0;
}
