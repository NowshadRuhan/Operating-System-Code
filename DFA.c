#include<stdio.h>
int main()
{
    int i,j,n,str;
    printf("The number of state : ");
    scanf("%d", &n);
    getchar();
    char dfa[200][200];
    for(i=0; i<n; i++)
    {
        for(j=0; j<2; j++)
        {
            scanf("%c", &dfa[i][j]);
            getchar();
        }
    }
    printf("\n\n\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<2; j++)
        {
            printf("%c ", dfa[i][j]);
        }
        printf("\n");
    }
    printf("Last state : ");
    char ch;
    scanf("%c", &ch);
    while(1){
        printf("Enter the string : ");
        char str_check[200];
        scanf("%s", str_check);
        check(str_check, ch);
        printf("\n\n\n");
    }
}
void check(char str_check[200], char ch)
{
    printf("%s\n", str_check);

    printf("%c", ch);
}





