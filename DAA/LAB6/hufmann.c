
#include <stdio.h>
#include <stdlib.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
    struct SYMBOL *left;
    struct SYMBOL *right;
};

struct SYMBOL *createSymbol(char alphabet, int frequency)
{
    struct SYMBOL *symbol = (struct SYMBOL *)malloc(sizeof(struct SYMBOL));
    symbol->alphabet = alphabet;
    symbol->frequency = frequency;
    symbol->left = NULL;
    symbol->right = NULL;
    return symbol;
}

void swap(struct SYMBOL **a, struct SYMBOL **b)
{
    struct SYMBOL *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct SYMBOL *symbols[], int size, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && symbols[left]->frequency < symbols[smallest]->frequency)
        smallest = left;

    if (right < size && symbols[right]->frequency < symbols[smallest]->frequency)
        smallest = right;

    if (smallest != index)
    {
        swap(&symbols[index], &symbols[smallest]);
        minHeapify(symbols, size, smallest);
    }
}

void buildMinHeap(struct SYMBOL *symbols[], int size)
{
    int i = (size - 1) / 2;
    for (; i >= 0; i--)
    {
        minHeapify(symbols, size, i);
    }
}

struct SYMBOL *extractMin(struct SYMBOL *symbols[], int *size)
{
    struct SYMBOL *minSymbol = symbols[0];
    symbols[0] = symbols[(*size) - 1];
    (*size)--;
    minHeapify(symbols, *size, 0);
    return minSymbol;
}

void insert(struct SYMBOL *symbols[], int *size, struct SYMBOL *symbol)
{
    (*size)++;
    int i = *size - 1;
    while (i > 0 && symbol->frequency < symbols[(i - 1) / 2]->frequency)
    {
        symbols[i] = symbols[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    symbols[i] = symbol;
}

struct SYMBOL *buildHuffmanTree(char alphabets[], int frequencies[], int n)
{
    struct SYMBOL *symbols[n];
    for (int i = 0; i < n; i++)
    {
        symbols[i] = createSymbol(alphabets[i], frequencies[i]);
    }

    int size = n;
    buildMinHeap(symbols, size);

    while (size > 1)
    {
        struct SYMBOL *left = extractMin(symbols, &size);
        struct SYMBOL *right = extractMin(symbols, &size);
        struct SYMBOL *parent = createSymbol('-', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        insert(symbols, &size, parent);
    }

    return symbols[0];
}

void inorderTraversal(struct SYMBOL *root)
{
    if (root)
    {
        inorderTraversal(root->left);
        printf("%c ", root->alphabet);
        inorderTraversal(root->right);
    }
}

int main()
{
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int frequencies[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &alphabets[i]);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &frequencies[i]);
    }

    struct SYMBOL *root = buildHuffmanTree(alphabets, frequencies, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);

    return 0;
}