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
    n1 = nw = nc = 0;   //这条语句得意思就是把这三个变量全部赋值为0 
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
        {
            ++n1;
        }
        if (c == ' ' || c == '\n' || c == '\t')   //条件判断语句
        {
            state = OUT;
        }
        else if (state = OUT)    //符合条件判断语句
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d\t%d\t%d\t\n", n1, nw, nc);
    system("pause");
}