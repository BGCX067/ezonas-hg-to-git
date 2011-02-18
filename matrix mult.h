//row is the matrix where we select ROWS
//col is the matrix where we select COLUMNS
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

