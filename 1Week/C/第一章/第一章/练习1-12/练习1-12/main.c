#include <stdio.h>
/*��дһ��������ÿ��һ�����ʴ�ӡ���*/
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
