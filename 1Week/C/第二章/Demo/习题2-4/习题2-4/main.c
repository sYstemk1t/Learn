#include <stdio.h>

int htoi(char s[]);


int main()
{
    int a = htoi("1234");
    int b = htoi("0x1f");
    int c = htoi("0XAD");
    printf("十进制:%d, 十六进制:%#x\n", a, a);
    printf("十进制:%d, 十六进制:%#x\n", b, b);
    printf("十进制:%d, 十六进制:%#x\n", c, c);
    return 0;

}

int htoi(char s[])
{
    int n, i;
    n = 0;
    for (i = 0; s[i] != '\0'; ++i)
    {
        if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
        {
            i = i + 2;
        }
        if ((s[i] >= '0'&&s[i] <= '9'))
        {
            n = n * 16 + s[i] - '0';
        }
        else if (s[i] >= 'a'&&s[i] <= 'f')
        {
            n = n * 16 + 10 + s[i] - 'a';
        }
        else if (s[i] >= 'A'&&s[i] <= 'F')
        {
            n = n * 16 + 10 + s[i] - 'A';
        }


    }
}