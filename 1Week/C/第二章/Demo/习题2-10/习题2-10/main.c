#include <stdio.h>
/*
int lower(int c)
{
if (c >= 'A' && c <= 'Z')
return c + 'a' - 'A';
else
return c;
}
*/
int lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;   //ÈýÄ¾ÔËËã·û
}

int main()
{
    char a;
    scanf("%c", &a);
    a = lower(a);
    printf("%c", a);
    system("pause");
    
}