#include<stdio.h>
int main()
{
    while(1)
    {
        char ch[200];
        gets(ch);
        //scanf("%s", ch);
        int str = strlen(ch);
        suffix(ch, str);
    }
}
void suffix(char ch1[200], int j)
{

    int n = j-1,i;
    while(n>0)
    {
        for(i=n; i<=j; i++)
        {
            printf("%c", ch1[i]);
        }
        n--;
        printf("\n");
    }

}


