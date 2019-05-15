#include <stdio.h>
/*思路想错了，以为需要ascll码表中得字符来做转换计数*/
/*
int main()
{
    char c = NULL;
    int c1 = NULL;
    while (getchar(c) != EOF)
    {
        if (c == '13')   //13代表ascll码表中得空格
        {
            ++c1;
        }
        printf("一共有%d个空格", c1);
        break;
    }
    system("pause");
}

*/


int main()
{
    int c = NULL;
    int c1 = NULL;
    int c2 = NULL;
    int c3 = NULL;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            ++c1;
        }
        if (c == '\t')
        {
            ++c2;
        }
        if (c == '\n')
        {
            ++c3;
        }
        
    }
    printf("空格个数%d", c1);
    printf("制表符个数%d", c2);
    printf("换行符%d", c3);
}