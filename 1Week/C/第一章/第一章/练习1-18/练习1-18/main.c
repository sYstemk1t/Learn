#include <stdio.h>
#include <stdlib.h>
int getline(char s[], int max);
int main()
{
    int len;
    char line[1000];
    while ((len = getline(line, 1000))>0)
    {
        printf("%s\n", line);
    }

    system("pause");
    return 0;
}
int getline(char s[], int max)
{
    int i, c, k;
    for (i = 0; i < 1000 - 1 && (c = getchar()) != EOF&&c != '\n'; i++)
    {
        s[i] = c;
    }
       
    for (k = i - 1; s[k] == ' ' || s[k] == '\t'; k--)          //���������һ���ַ���ʼ��ǰѭ���жϣ����Ͽո���Ʊ�����ͼ���ѭ����ֱ��������������������Ȼ�������ֹ����
    {
        s[k] = '\0';
    }
    return k;
}
