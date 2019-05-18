
#include<stdio.h>
#include<string.h>


int reverse(int len,char str[])
{
    char c;
    int i = 0;
    for (i = 0; i<len / 2; i++)
    {
        c = str[len - 1 - i];   //str[len-1-i] len-1的因为srtlen()函数返回的是字符串的长度，但数组的下标是从零开始的。
        str[len - 1 - i] = str[i];
        str[i] = c;
    }
}

int main()
{
    int len = 0; //存储字符串长度
    int i = 0;
    char str[50];
    char c;   //用于交换的中间变量
    printf("请输入字符串：\n");
    gets(str);
    len = strlen(str);
    reverse(len, str);

    for (i = 0; i <= len; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}
