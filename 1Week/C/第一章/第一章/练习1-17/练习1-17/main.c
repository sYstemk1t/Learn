#include <stdio.h>
#define MAXLINE 1000 //允许输入行的最大长度
#define LONGLINE 80

int getline(char line[], int maxline);

// print lines longer than LONGLINE
main()
{
    int len;
    char line[MAXLINE];

    while ((len - getline(line, MAXLINE)) > 0)
        if (len > LONGLINE)
            printf("%S", line);
    return 0;

}

int getline(char s[], int lim)
{
    int c, i, j;
    j = 0;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 2)
        {
            s[j] = c;
            ++j;
        }
    if (c == '\n'){
        s[j] = c;
        ++j;
        ++i;
    }
    s[j] = '\0';
    return i;
}