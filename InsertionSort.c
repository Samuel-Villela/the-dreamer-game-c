#include <stdio.h>
void insertionSort(int vetor[],int tamanho)
{
    int temp,i,j;
    for(i = 1; i<tamanho; i ++)
    {
        j = i;
        while(j>0 && vetor[j-1]>vetor[j])
        {
            temp = vetor[j];
            vetor[j] = vetor[j-1];
            vetor[j-1] = temp;
            j--;
        }
    }
}
int main()
{
    int tamanho,i;
    scanf("%d",&tamanho);
    int v[tamanho];
    for(i=0;i<tamanho;i++)
    {
        scanf("%d",&v[i]);
    }
    insertionSort(v,tamanho);
    for(i=0;i<tamanho;i++)
    {
        printf("%d",v[i]);
    }

    return 0;
}