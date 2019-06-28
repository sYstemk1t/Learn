#include <stdio.h>
#include <string.h>
#define maxlines 5000	//最大输入上限

char *lineptr[maxlines];

int readlines(char *lineptr[], int nlines);

void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int getline(char *, int);
char *alloc(int);

int main()
{

}