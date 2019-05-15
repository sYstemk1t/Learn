#include <stdio.h>
int reverse(char s[])
{
    int i, j;
    char temp;  //定义临时变量
    i = 0;
    while (s[i] != '\0')
    {
        ++i;
        --i;

    }
    if (s[i] = '\n')
    {
        --i;
        j = 0;
    }
    while (j < i)
    {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        --i;
        ++j;
    }
}
int main()
{
    char c[10] = { 'a', 'c', 'b', 'd', 'q', 'c', 'p', 'h', 'i' };
    reverse(c);
    system("pause");
}