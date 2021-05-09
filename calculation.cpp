#include"real.h"
#include<stdio.h>
#include<string>
using namespace std;
real lch[10005], rch[10005];
int nc = 0;
string op;
real build_true(char* s, int x, int y) {
	int c1 = -1, c2 = -1, p = 0, u;
	if (x - y == 1) {
		u = ++nc;
		lch[u] = rch[u] = 0;
		op[u] = s[x];
		real a;
		a = u;
		return a;
	}
	for (int i = x; i < y; i++)
		switch (s[x])
		{
		case '(':p++; break;
		case ')':p--; break;
		case '+':case '-':if (!p)c1 = i; break;
		case '*':case '/':if (!p)c2 = i; break;
		}
	if (c1 < 0)c1 = c2;//找不到括号外的加减号，就用乘除号
	if (c1 < 0)return build_true(s, c1 + 1, y);//整个表达式被一对括号括起
	u = ++nc;
	lch[u] = build_true(s, x, c1);
	rch[u] = build_true(s, c1 + 1, y);
	op[u] = s[c1];
	real a;
	a = u;
	return a;
}