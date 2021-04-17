#include"real.h"
#include<string>
#include<stdio.h>
#include<algorithm>
using namespace std;
number gcd(number a, number b) {
	if (b.len == 1 && b.num[0] == 0)return a;
	else return gcd(b, a % b);
}
void real::getNum(string s) {
	if (s[0] == '-')this->negative = true, s.erase(0, 1);
	int decimal_point = s.find('.');
	if (decimal_point != -1) {
		s.erase(decimal_point, 1);
		this->numerator.getNum(s);
		this->denominator.num.resize(s.size() - 1 - decimal_point);
		this->denominator.num[s.size() - 2 - decimal_point] = 1;
		this->simplification();
	}
	int fractional_line;
	fractional_line = s.find('/');
	if (fractional_line != -1) {
		while (s[0] != '/') {
			this->numerator.num.push_back(s[0] - 48);
			s.erase(0, 1);
			this->numerator.len++;
		}
		reverse(this->numerator.num.begin(), this->numerator.num.end());
		s.erase(0, 1);
		while (s.size() != 0) {
			this->denominator.num.push_back(s[0] - 48);
			s.erase(0, 1);
			this->denominator.len++;
		}
		reverse(this->denominator.num.begin(), this->denominator.num.end());
		this->simplification();
		return;
	}
	this->numerator.getNum(s);
	this->denominator.len = 1;
	this->denominator.num.push_back(1);
}
void real::showNum() {
	if (this->negative)printf("-");
	number a;
	real b = *this;
	a = b.numerator % b.denominator;
	if (a.len == 1 && a.num[0] == 0) {
		b = *this;
		a = b.numerator / b.denominator;
		a.showNum();
		printf(" ");
		return;
	}
	this->numerator.showNum();
	printf("/");
	this->denominator.showNum();
	printf(" ");
}
void real::simplification() {
	number c;
	c = gcd(this->denominator, this->numerator);
	this->denominator = this->denominator / c;
	this->numerator = this->numerator / c;
}
real& real::operator+(real b) {
	real c;
	if (this->negative)
		if (b.negative)
			c.negative = true;
		else {
			this->negative = false;
			return b - *this;
		}
	else
		if (b.negative) {
			b.negative = false;
			return *this - b;
		}
	number t;
	t = gcd(this->denominator, b.denominator);
	c.denominator = this->denominator * b.denominator / t;
	this->numerator = this->numerator * (c.denominator / this->denominator);
	b.numerator = b.numerator * (c.denominator / b.denominator);
	this->denominator = b.denominator = c.denominator;
	c.numerator = this->numerator + b.numerator;
	c.simplification();
	*this = c;
	return *this;
}
real& real::operator-(real b) {
	real c;
	if (this->negative)
		if (b.negative) {
			this->negative = b.negative = false;
			swap(*this, b);
		}
		else {
			this->negative = false;
			c = *this + b;
			c.negative = true;
			*this = c;
			return *this;
		}
	else
		if (b.negative) {
			b.negative = false;
			return *this + b;
		}
	number t;
	t = gcd(this->denominator, b.denominator);
	c.denominator = this->denominator * b.denominator / t;
	this->numerator = this->numerator * (c.denominator / this->denominator);
	b.numerator = b.numerator * (c.denominator / b.denominator);
	this->denominator = b.denominator = c.denominator;
	c.numerator = this->numerator - b.numerator;
	c.simplification();
	*this = c;
	return *this;
}
real& real::operator*(real b) {
	real c;
	if (this->negative && !b.negative) {
		this->negative = false;
		c.negative = true;
	}
	if (!this->negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.denominator = this->denominator * b.denominator;
	c.numerator = this->numerator * b.numerator;
	c.simplification();
	*this = c;
	return *this;
}
real& real::operator/(real b) {
	real c;
	if (this->negative && !b.negative) {
		this->negative = false;
		c.negative = true;
	}
	if (!this->negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	swap(b.denominator, b.numerator);
	c = *this * b;
	*this = c;
	return *this;
}
real& real::operator^(real b) {
	if (b.negative)swap(this->denominator, this->numerator);
	real c, e = b, f;
	number d;
	f.denominator.len = 1;
	f.denominator.num.push_back(1);
	f.numerator.len = 1;
	f.numerator.num.push_back(2);
	d = (e.numerator / e.denominator) % (f.numerator / f.denominator);
	if (d.num[0] == 1)
		c.negative = this->negative;
	d = (f.numerator / f.denominator);
	while (d.len != 1 || d.num[0] != 0) {
		c = c * (*this);
		d.num[0]--;
		for (int i = 0; i < d.len; i++) {
			if (d.num[i] >= 0)break;
			d.num[i] += 10;
			d.num[i + 1]--;
		}
		while (d.len > 1 && d.num[d.len - 1] == 0)d.len--, d.num.pop_back();
	}
	*this = c;
	return *this;
}