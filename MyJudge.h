

#ifndef MyJudge_h
#define MyJudge_h


inline bool user_win(int M, int N, int x, int y, int(*board)[12]) {

	//ºáÏò¼ì²â
	int i, j;
	int count = 0;
	for (i = y; i >= 0; i--)
		if (!(board[x][i] == 1)) break;
	count += (y - i);
	for (i = y; i < N; i++)
		if (!(board[x][i] == 1)) break;
	count += (i - y - 1);
	/*
	if (count >= 4) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) _cprintf("%d ", board[i][j]);
			_cprintf("\n");
		}
	}
	*/
	if (count >= 4) return true;

	//×İÏò¼ì²â
	count = 0;
	for (i = x; i < M; i++)
		if (!(board[i][y] == 1)) break;
	count += (i - x);
	if (count >= 4) return true;

	//×óÏÂ-ÓÒÉÏ
	count = 0;
	for (i = x, j = y; i < M && j >= 0; i++, j--)
		if (!(board[i][j] == 1)) break;
	count += (y - j);
	for (i = x, j = y; i >= 0 && j < N; i--, j++)
		if (!(board[i][j] == 1)) break;
	count += (j - y - 1);
	if (count >= 4) return true;

	//×óÉÏ-ÓÒÏÂ
	count = 0;
	for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
		if (!(board[i][j] == 1)) break;
	count += (y - j);
	for (i = x, j = y; i < M && j < N; i++, j++)
		if (!(board[i][j] == 1)) break;
	count += (j - y - 1);
	if (count >= 4) return true;

	return false;
}


inline bool comp_win(int M, int N, int x, int y, int(*board)[12]) {

	//ºáÏò¼ì²â
	int i, j;
	int count = 0;
	for (i = y; i >= 0; i--)
		if (!(board[x][i] == 2)) break;
	count += (y - i);
	for (i = y; i < N; i++)
		if (!(board[x][i] == 2)) break;
	count += (i - y - 1);
	if (count >= 4) return true;

	//×İÏò¼ì²â
	count = 0;
	for (i = x; i < M; i++)
		if (!(board[i][y] == 2)) break;
	count += (i - x);
	if (count >= 4) return true;

	//×óÏÂ-ÓÒÉÏ
	count = 0;
	for (i = x, j = y; i < M && j >= 0; i++, j--)
		if (!(board[i][j] == 2)) break;
	count += (y - j);
	for (i = x, j = y; i >= 0 && j < N; i--, j++)
		if (!(board[i][j] == 2)) break;
	count += (j - y - 1);
	if (count >= 4) return true;

	//×óÉÏ-ÓÒÏÂ
	count = 0;
	for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
		if (!(board[i][j] == 2)) break;
	count += (y - j);
	for (i = x, j = y; i < M && j < N; i++, j++)
		if (!(board[i][j] == 2)) break;
	count += (j - y - 1);
	if (count >= 4) return true;

	return false;
}


inline bool is_tie(int N, int *top) {

	bool tie = true;
	for (int i = 0; i < N; i++)
	{
		if (top[i] > 0)
		{
			tie = false;
			break;
		}
	}
	return tie;
}


#endif