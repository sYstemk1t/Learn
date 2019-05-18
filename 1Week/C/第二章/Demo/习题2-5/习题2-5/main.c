#include <stdio.h>
int  ant(char s1[], char  s2[])
{
    int i;
    int j;
    int k;
    for (i = 0; s1[i] != '\0'; i++)  //  ' \0 '  ×Ö·û´®½áÊø·û
    {
        for (j = 0; s2[j] != '\0'&& j<sizeof(s2); j++)
        {
            if (s2[j] == s1[i])
            {
                return i;
            }
        }
    }
}
int main()
{
    char s1[] = "1bcdefghijklmn";
    char s2[] = "aaabbbccc";
    ant(s1, s2);
    system("pause");
}