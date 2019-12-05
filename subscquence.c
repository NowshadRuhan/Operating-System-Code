#include<stdio.h>
#include<string.h>
int subScquence(char str[200], char check[200], int length, int n)///using modularity
{

    int flag = 0;
    int flager1 = 0;
    if(n>length)
    {
        printf("No sub-scquence\n");
    }
    else if(n<=length)
    {

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<length; j++)
            {
                if(str[j]==check[i])
                {
                    i++;
                    flager1++;
                }
            }
        }
        if(flager1 == n)
        {
            printf("Yes this is sub-scquence\n");
        }
        else
        {
            printf("Not sub-scquence!!\n");
        }

    }
    else
    {
        printf("%s is not sub scquence\n", check);
    }

    return 0 ;
}
int main()
{

    char ch[200];
    printf("Enter the string : ");
    //scanf("%s", ch);
    gets(ch);
    int length = strlen(ch);
    char check[200];
    while(1)
    {
        gets(check);
        int n = strlen(check);
        subScquence(ch,check,length,n);
    }
    return 0;
}



