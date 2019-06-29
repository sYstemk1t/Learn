#include <stdio.h>
#define TRUE 1
#define FALSE 0
int identity_matrix(int matrix[][10]){
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++){
			if (i == j){
				if (matrix[i][j] != 1)
					return FALSE;
			}
			else{
				if (matrix[i][j] != 0)
					return FALSE;
			}
		}
	return TRUE;
}


int main()
{
	int array[10][10];
	identity_matrix(array);
	system("pause");
}