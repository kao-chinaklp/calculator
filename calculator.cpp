#include"calculator.h"
#include<iostream>
#include<sstream>
#include<cmath>
using namespace std;
void calculator::enter(real num) {
	s.push(num);
}
bool calculator::getTwoOperands(real& opnd1, real& opnd2) {
	if (s.empty()) {
		cerr << "缺了个数！\n";
		return false;
	}
	opnd1 = s.top();
	s.pop();
	if (s.empty()) {
		cerr << "缺了个数！\n";
		return false;
	}
	opnd2 = s.top();
	s.pop();
	return true;
}
void calculator::compute(char op) {
	real operand1, operand2;
	bool result = getTwoOperands(operand1, operand2);
	if (result) {
		switch (op) {
		case '+':
			s.push(operand2 + operand1);
			break;
		case '-':
			s.push(operand2 - operand1);
			break;
		case '*':
			s.push(operand2 * operand1);
			break;
		case '/':
			if (operand1.numerator.len == 1 && operand1.numerator.num[0] == 0) {
				cerr << "除数为0！\n";
				stack<real>().swap(s);
			}
			else s.push(operand2 / operand1);
			break;
		}
		real t = s.top();
		t.showNum();
	}
	else
		stack<real>().swap(s);
}
void calculator::run() {
	string str;
	while (cin >> str) {
		switch (str[0]) {
		case 'c':
			stack<real>().swap(s);
			break;
		case '-':
			if (str.size() > 1) {
				real a;
				a.getNum(str);
				enter(a);
			}
			else
				compute(str[0]);
			break;
		case '+':
		case '*':
		case '/':
			compute(str[0]);
			break;
		default: {
			real a;
			a.getNum(str);
			enter(a);
		}
		}
	}
}