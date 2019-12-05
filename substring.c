#include<stdio.h>
#include<string.h>

void subString(char str[200], int n, int ln)///using modularity
{

    for (int len = ln; len <= ln; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;
            for (int k = i; k <= j; k++)
            {
                printf("%c", str[k]);
            }
            printf("\n");
        }
    }
}
int main()
{

    char ch[200];
    printf("Enter the string : ");
    //scanf("%s", ch);
    gets(ch);
    int ln ;
    while(1)
    {
        printf("Enter the substring number : ");
        scanf("%d", &ln);
        int length = strlen(ch);
        if(ln>length)
        {
            printf("No sub-string. ");
        }
        else
        {
            subString(ch,length,ln);
        }
    }
    return 0;
}

