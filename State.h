

#ifndef AI0_State_h
#define AI0_State_h


#include<cstdio>
#include<iostream>
using namespace std;


class State {
public:
	static int M, N, noX, noY;
	bool flag; // 0 : I'm going to put a chess.  1: the other player
	int *top, **board;
	int lastX, lastY, num, Q;
	State *son[12], *fa;
	State() :num(0), Q(0), fa(0) {
		for (int i = 0; i < 12; i++) son[i] = 0;
	}
	void init(int *_top, int **_board, int _lastX, int _lastY, bool _flag);
	State* expand(int i);
	double getUCB();
	State* find();// return the next v to train
	pair<int, int> train() const;
	void release();
	void debug(int);
};


#endif