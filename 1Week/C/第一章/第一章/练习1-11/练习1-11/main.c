#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
    int c;
    int n1;
    int nw;
    int nc;
    int state;
    state = OUT;
    n1 = nw = nc = 0;   //����������˼���ǰ�����������ȫ����ֵΪ0 
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
        {
            ++n1;
        }
        if (c == ' ' || c == '\n' || c == '\t')   //�����ж����
        {
            state = OUT;
        }
        else if (state = OUT)    //���������ж����
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d\t%d\t%d\t\n", n1, nw, nc);
    system("pause");
}