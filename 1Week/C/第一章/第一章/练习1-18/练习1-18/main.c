#include <stdio.h>
#include <stdlib.h>
int getline(char s[], int max);
int main()
{
    int len;
    char line[1000];
    while ((len = getline(line, 1000))>0)
    {
        printf("%s\n", line);
    }

    system("pause");
    return 0;
}
int getline(char s[], int max)
{
    int i, c, k;
    for (i = 0; i < 1000 - 1 && (c = getchar()) != EOF&&c != '\n'; i++)
    {
        s[i] = c;
    }
       
    for (k = i - 1; s[k] == ' ' || s[k] == '\t'; k--)          //从数组最后一个字符开始往前循环判断，符合空格或制表符，就继续循环，直到不符合条件后跳出，然后加入终止符。
    {
        s[k] = '\0';
    }
    return k;
}
