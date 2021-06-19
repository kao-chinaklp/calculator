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
	real radical(real b);//开根号
	void operator++(int);
	void operator--(int);
	void operator=(real a);
	void operator=(number a);
	void operator=(double a);
	void operator+=(real b);
	void operator-=(real b);
	void operator*=(real b);
	void operator/=(real b);
	bool operator<(real a);
	bool operator>(real a);
	bool operator==(real a);
	bool operator!=(real a);
};
#endif // !REAL_H