#include <stdio.h>
/*��Ŀû��˵��������������ַ����������Σ�����������*/
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