
#include<stdio.h>
#include<string.h>


int reverse(int len,char str[])
{
    char c;
    int i = 0;
    for (i = 0; i<len / 2; i++)
    {
        c = str[len - 1 - i];   //str[len-1-i] len-1����Ϊsrtlen()�������ص����ַ����ĳ��ȣ���������±��Ǵ��㿪ʼ�ġ�
        str[len - 1 - i] = str[i];
        str[i] = c;
    }
}

int main()
{
    int len = 0; //�洢�ַ�������
    int i = 0;
    char str[50];
    char c;   //���ڽ������м����
    printf("�������ַ�����\n");
    gets(str);
    len = strlen(str);
    reverse(len, str);

    for (i = 0; i <= len; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}
