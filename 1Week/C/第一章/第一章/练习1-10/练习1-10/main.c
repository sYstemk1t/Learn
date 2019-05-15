/*将制表符更换为\t*/
#include <stdio.h>
int main()
{
    int c = NULL;
    int i = NULL;;
    int g = NULL;
    while (getchar(c) != EOF)
    {
        if (c == '\t')
        {
            printf("\\t");
        }
        if (c == "\b")
        {
            printf("\\");
        }
        if (c == '\b')
        {
            if (c != '\t')
            {
                putchar(c);
            }
        }
    }
    system("pause");
}