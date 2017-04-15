#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <conio.h>
#include <atlstr.h>
#include "State.h"
#include "MyJudge.h"
using namespace std;

void State::init(int *_top, int **_board, int _lastX, int _lastY, bool _flag) {
	//_cprintf("\n=========== init() ===========\n");_cprintf("_lastX=%d _lastY=%d\n", _lastX, _lastY);
	lastX = _lastX, lastY = _lastY;
	top = new int[N];
	for (int i = 0; i < N; i++) top[i] = _top[i];
	board = new int*[M];
	for (int i = 0; i < M; i++) {
		board[i] = new int[N];
		for (int j = 0; j < N; j++) board[i][j] = _board[i][j];
	}
	flag = _flag;
}


State* State::expand(int i) {
	son[i] = new State;
	son[i]->fa = this;
	son[i]->init(top, board, top[i] - 1, i, flag ^ 1);
	son[i]->board[top[i] - 1][i] = 2 - flag;
	son[i]->top[i]--;
	if (son[i]->top[i] - 1 == noX && i == noY) son[i]->top[i]--;
	return son[i];
}


double State::getUCB() {
	double C = 500, eps = 1e-3;
	if (flag) return (double)Q * 100 / (num + eps) + C * sqrt(log(fa->num + 1) / (num + eps));
	else return -(double)Q * 100 / (num + eps) + C * sqrt(log(fa->num + 1) / (num + eps));
}

State* State::find() {
	for (int i = 0; i < N; i++)
		if (!son[i] && top[i]>0) return expand(i);
	static double _INF = -1e18;
	double tmp = _INF;
	int j = -1;
	for (int i = 0; i<N; i++)
		if (son[i]) {
			double t = son[i]->getUCB();
			if (t > tmp) {
				tmp = t;
				j = i;
			}
		}
	if (j >= 0) return son[j]->find();
	return this;
}


inline int random(int n) {
	return rand() % n;
}

pair<int, int> State::train() const {
	static int top[12], board[12][12];
	int cnt = 10000, w = 0;
	for (int tt = 0; tt < cnt; tt++) {

		for (int i = 0; i < N; i++) top[i] = this->top[i];
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) board[i][j] = this->board[i][j];

		int lastX = this->lastX, lastY = this->lastY;
		bool t0, t1, t2, flag = this->flag;

		for (;;) {
			/*
			_cprintf("\n\n");
			for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) _cprintf("%d ", board[i][j]);
			_cprintf("\n");
			}
			*/

			if (t0 = is_tie(N, top)) break;
			if (t1 = user_win(M, N, lastX, lastY, board)) break;
			if (t2 = comp_win(M, N, lastX, lastY, board)) break;

			int i = random(N);
			//_cprintf("\ni=%d\n", i);
			while (top[i] == 0) i = random(N);
			board[top[i] - 1][i] = 2 - flag;
			lastX = top[i] - 1;
			lastY = i;
			flag ^= 1;
			top[i]--;
			if (top[i] - 1 == noX && i == noY) top[i]--;
		}
		/*
		_cprintf("\n\n");
		for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) _cprintf("%d ", board[i][j]);
		_cprintf("\n");
		}
		*/
		flag = this->flag;
		if (t2) w += 2;
		else if (t0) w += 1;
	}
	return make_pair(cnt, w);
}


void State::release() {
	for (int i = 0; i < N; i++)
		if (son[i]) son[i]->release();
	delete[] top;
	for (int i = 0; i < M; i++)
		delete[] board[i];
	delete[] board;
}


void State::debug(int asd) {
	_cprintf("\ntop: ");
	for (int i = 0; i < N; i++) _cprintf("%d ", top[i]);
	_cprintf("\n");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) _cprintf("%d ", board[i][j]);
		_cprintf("\n");
	}
	_cprintf("\nnum=%d  Q=%d\n\n", num, Q);
	if (fa) _cprintf("UCB=%.3f\n", getUCB());
	if (asd==1) {
		for (int i = 0; i < N; i++)
			if (son[i]) {
				_cprintf("\n\nson[%d]:\n", i);
				son[i]->debug(0);
			}
	}
}