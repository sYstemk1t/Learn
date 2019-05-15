#include <stdio.h>
/*编写一个程序，以每行一个单词打印输出*/
int main()
{
    char c = NULL;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            putchar(c);
            printf("\n");
        }
    }
    system("pause");
}
