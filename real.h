#pragma once
#ifndef REAL_H
#define REAL_H
#include"number.h"
#include<string>
class real {
public:
	real() :negative(false) {};
	number numerator;//分子
	number denominator;//分母
	bool negative;//负号
	void getNum(std::string s);
	void showNum();
	void simplification();
	real operator+(real b);
	real operator-(real b);
	real operator*(real b);
	real operator/(real b);
	real operator^(real b);
	void operator++(int);
	void operator--(int);
	real operator=(real a);
	real operator=(int a);
	void operator+=(real b);
	void operator-=(real b);
	void operator*=(real b);
	void operator/=(real b);
};
#endif // !REAL_H