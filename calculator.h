#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include"real.h"
#include<stack>
class calculator {
public:
	void run();
	void clear();

private:
	std::stack<real>s;
	void enter(real num);
	bool getTwoOperands(real& opnd1, real& opnd2);
	void compute(char op);
};
#endif // !CALCULATOR_H