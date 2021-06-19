#pragma once
#ifndef REAL_H
#define REAL_H
#include"number.h"
#include<string>
class real {
public:
	real() :negative(false) {};
	number numerator;//����
	number denominator;//��ĸ
	bool negative;//����
	void getNum(std::string s);
	void showNum();
	void simplification();
	real operator+(real b);
	real operator-(real b);
	real operator*(real b);
	real operator/(real b);
	real operator^(real b);
	real radical(real b);//������
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