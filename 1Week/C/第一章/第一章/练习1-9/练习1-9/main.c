#include <stdio.h>
/*题目没有说明输入得内容是字符串还是整形，按照整形做*/
int main()
{      
    int c = NULL;
    int lastc = NULL;
    while (getchar(c) != EOF)
    {
        if (c != ' ')
        {
            putchar(c);
        }
        if (c == ' ')
        {
            if (lastc != ' ')
            {
                putchar(c);
            }
        }
    }
}