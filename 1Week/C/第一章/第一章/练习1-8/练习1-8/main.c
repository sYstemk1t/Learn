#include <stdio.h>
/*˼·����ˣ���Ϊ��Ҫascll����е��ַ�����ת������*/
/*
int main()
{
    char c = NULL;
    int c1 = NULL;
    while (getchar(c) != EOF)
    {
        if (c == '13')   //13����ascll����еÿո�
        {
            ++c1;
        }
        printf("һ����%d���ո�", c1);
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
    printf("�ո����%d", c1);
    printf("�Ʊ������%d", c2);
    printf("���з�%d", c3);
}