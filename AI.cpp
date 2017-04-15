#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <conio.h>
#include <atlstr.h>
#include "AI.h"
#include "State.h"
#include "MyJudge.h"
using namespace std;

int State::M = 0;
int State::N = 0;
int State::noX = 0;
int State::noY = 0;


pair<int, int> AI_getPoint(const int M, const int N, const int*_top, int**board, const int lastX, const int lastY, const int noX, const int noY) {
	//AllocConsole();
	//_cprintf("\n========================== My Program Begins ========================\n");
	//return make_pair(0, 0);
	srand((int)time(0));
	int time0 = clock();
	static int top[12];
	for (int i = 0; i < N; i++) top[i] = _top[i];
	//_cprintf("asdasd\n");
	// 如果能够获胜，直接下在那一点
	static int bb[12][12];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) bb[i][j] = board[i][j];
	//_cprintf("asdasd\n");
	static bool flag[12];
	for (int i = 0; i < N; i++) flag[i] = false;
	for (int i = 0; i<N; i++)
		if (top[i] > 0) {
			//_cprintf("i=%d\n", i);
			flag[i] = true;
			bb[top[i] - 1][i] = 2;
			if (comp_win(M, N, top[i] - 1, i, bb)) {
				//_cprintf("return wirh %d %d\n", top[i] - 1, i);
				return make_pair(top[i] - 1, i);
			}
			bb[top[i] - 1][i] = 1;
			if (user_win(M, N, top[i] - 1, i, bb)) {
				//_cprintf("user_win\n");
				return make_pair(top[i] - 1, i);
			}
			if (top[i] > 1 && i != noY || top[i] - 2 != noX) {
				bb[top[i] - 1][i] = 2;
				bb[top[i] - 2][i] = 1;
				if (user_win(M, N, top[i] - 2, i, bb)) flag[i] = false;
				bb[top[i] - 2][i] = 0;
			}
			bb[top[i] - 1][i] = 0;
		}
	//_cprintf("asdasd\n");
	State::M = M;
	State::N = N;
	State::noX = noX;
	State::noY = noY;

	// 蒙特卡洛树
	State *root=new State;
	//_cprintf("Before root->init()\n");
	root->init(top, board, lastX, lastY, false);
	//_cprintf("After root->init()\n");
	int ttt = 0;
	while (clock()-time0<2500) {
		//_cprintf("\n---------------------------- ttt=%d -------------------------\n", ttt++);
		State *v = root->find();
		pair<int,int> tmp=v->train();
		while (v!=0) {
			v->num += tmp.first;
			v->Q += tmp.second;
			//tmp.second = -tmp.second;
			v = v->fa;
		}
	}
	//_cprintf("\n\n======================= everything ended =====================\n");
	//root->debug(1);
	int tmp = 0, j = 0;
	for (int i = 0; i<N; i++)
		if (root->son[i] && root->son[i]->num > tmp && flag[i]) {
			tmp = root->son[i]->num;
			j = i;
		}
	pair<int, int> ans = make_pair(top[j] - 1, j);
	//_cprintf("Before root->release()");
	root->release();
	return ans;
}