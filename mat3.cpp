/*-----------------------------------------------------------------------------*/
/* FILE		: 1.cpp .cc
/* AUTHOR	: Jonas ORINOVSKI "jokoon"
/* DATE		: 2010-1013
/* DESCR	: <Lecture de date par fonction>
/* CONTACT	: ezjonas@gmail.com jorinovski@gmail.com
/* TYPE		: SOURCE FILE (.C .CC .CXX .CPP)
/*-----------------------------------------------------------------------------*/

#include <cstdio>
#include <cstdlib>

typedef int mat3[3][3];
void MatProduct(mat3 _row, mat3 _col, mat3 _m)
{
//row is the matrix where we select ROWS
//col is the matrix where we select COLUMNS
//m is the result matrix
//left indice index rows, right indice index columns

	///////////// 1st line: /////////////
	// 1st line of the left matrix by hte 3 cols of the right matrix
	// here the row of the left matrix is always the same
	
	// 1st col
	_m[0][0] =
		_row[0][0] * _col[0][0]
	+	_row[0][1] * _col[1][0]
	+	_row[0][2] * _col[2][0];

	// 2nd col
	_m[0][1] =
		_row[0][0] * _col[0][1]
	+	_row[0][1] * _col[1][1]
	+	_row[0][2] * _col[2][1];

	// 3rd col
	_m[0][2] =
		_row[0][0] * _col[0][2]
	+	_row[0][1] * _col[1][2]
	+	_row[0][2] * _col[2][2];

	///////////// 2nd line: /////////////
	// 2nd line of the left matrix by hte 3 cols of the right matrix
	// 1st col
	_m[1][0] =
		_row[1][0] * _col[0][0]
	+	_row[1][1] * _col[1][0]
	+	_row[1][2] * _col[2][0];

	// 2nd col
	_m[1][1] =
		_row[1][0] * _col[0][1]
	+	_row[1][1] * _col[1][1]
	+	_row[1][2] * _col[2][1];

	// 3rd col
	_m[1][2] =
		_row[1][0] * _col[0][2]
	+	_row[1][1] * _col[1][2]
	+	_row[1][2] * _col[2][2];

	///////////// 3rd line: /////////////
	// 3rd line of the left matrix by hte 3 cols of the right matrix

	// 1st col
	_m[2][0] =
		_row[2][0] * _col[0][0]
	+	_row[2][1] * _col[1][0]
	+	_row[2][2] * _col[2][0];

	// 2nd col
	_m[2][1] =
		_row[2][0] * _col[0][1]
	+	_row[2][1] * _col[1][1]
	+	_row[2][2] * _col[2][1];

	// 3rd col
	_m[2][2] =
		_row[2][0] * _col[0][2]
	+	_row[2][1] * _col[1][2]
	+	_row[2][2] * _col[2][2];
}


void Show(_mat3 _m)
{
	printf("---------------------\n");
	printf("%d\t%d\t%d\n", _m[0][0], _m[0][1], _m[0][2]);
	printf("%d\t%d\t%d\n", _m[1][0], _m[1][1], _m[1][2]);
	printf("%d\t%d\t%d\n", _m[2][0], _m[2][1], _m[2][2]);
	printf("---------------------\n");
}

void Input(_mat3 _m)
{
	printf("Enter the 1st line's 3 ele_ments separated by spaces\n");
	scanf("%d %d %d", &_m[0][0], &_m[0][1], &_m[0][2]);

	printf("2nd line\n");
	scanf("%d %d %d", &_m[1][0], &_m[1][1], &_m[1][2]);

	printf("3rd line\n");
	scanf("%d %d %d", &_m[2][0], &_m[2][1], &_m[2][2]);
}

void main()
{
	mat3 m;

	Input(m);
	Show(m);

	system("PAUSE");
}