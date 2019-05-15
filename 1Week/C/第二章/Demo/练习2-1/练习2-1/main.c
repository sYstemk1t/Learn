#include <stdio.h>
int main1()
{
    
    signed int i = 0;
    while (1)
    {
        if (i < 0)
        {
            break;
        }
        ++i;
        printf("%d\r\n", i);
    }
    system("pause");
    return 0;
}

int main2()
{
    unsigned int i = 0;
    while (1)
    {
        if (i < 0)
        {
            break;
        }
        ++i;
        printf("%d\r\n", i);
    }
    system("pause");
    return 0;
}

int main()
{

        unsigned char i = 0;
        while (1)
        {
            if (i < 0)
            {
                break;
            }
            ++i;
            printf("%c\r\n", i);
        }
        system("pause");
        return 0;



}

