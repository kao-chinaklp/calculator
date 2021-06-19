#include"real.h"
#include<string>
#include<stdio.h>
#include<algorithm>
using namespace std;
number gcd(number a, number b) {
	if (b.len == 1 && b.num[0] == 0)return a;
	else return gcd(b, a % b);
}//求最大公约数
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
	if (this->numerator == 0) {
		this->denominator = 1;
		return;
	}
	number c;
	c = gcd(this->denominator, this->numerator);
	this->denominator /= c;
	this->numerator /= c;
}//约分化简
real real::operator+(real b) {
	real a = *this, c;
	if (this->negative)
		if (b.negative)
			c.negative = true;
		else {
			a.negative = false;
			return b - a;
		}
	else
		if (b.negative) {
			b.negative = false;
			return a - b;
		}
	number t;
	t = gcd(a.denominator, b.denominator);
	c.denominator = a.denominator * b.denominator / t;
	a.numerator *= (c.denominator / a.denominator);
	b.numerator *= (c.denominator / b.denominator);
	a.denominator = b.denominator = c.denominator;
	c.numerator = a.numerator + b.numerator;
	c.simplification();
	return c;
}
real real::operator-(real b) {
	real a = *this, c;
	if (a.negative)
		if (b.negative) {
			a.negative = b.negative = false;
			swap(a, b);
		}
		else {
			a.negative = false;
			c = a + b;
			c.negative = true;
			a = c;
			return a;
		}
	else
		if (b.negative) {
			b.negative = false;
			return a + b;
		}
	number t;
	t = gcd(a.denominator, b.denominator);
	c.denominator = a.denominator * b.denominator / t;
	a.numerator *= (c.denominator / a.denominator);
	b.numerator *= (c.denominator / b.denominator);
	a.denominator = b.denominator = c.denominator;
	c.numerator = a.numerator - b.numerator;
	c.simplification();
	return c;
}
real real::operator*(real b) {
	real a = *this, c;
	if (a.negative && !b.negative) {
		a.negative = false;
		c.negative = true;
	}
	if (!a.negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.denominator = a.denominator * b.denominator;
	c.numerator = a.numerator * b.numerator;
	c.simplification();
	return c;
}
real real::operator/(real b) {
	real a = *this, c;
	if (a.negative && !b.negative) {
		a.negative = false;
		c.negative = true;
	}
	if (!a.negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	swap(b.denominator, b.numerator);
	c = a * b;
	return c;
}
real real::operator^(real b) {
	real a = *this;
	if (b.negative)swap(a.denominator, a.numerator);
	real c, e = b, f;
	number d;
	f.denominator = 1;
	f.numerator = 2;
	d = (e.numerator / e.denominator) % (f.numerator / f.denominator);
	if (d.num[0] == 1)
		c.negative = a.negative;
	d = (f.numerator / f.denominator);
	while (d.len != 1 || d.num[0] != 0) {
		c *= a;
		d.num[0]--;
		for (int i = 0; i < d.len; i++) {
			if (d.num[i] >= 0)break;
			d.num[i] += 10;
			d.num[static_cast<unsigned __int64>(i) + 1]--;
		}
		while (d.len > 1 && d.num[static_cast<unsigned __int64>(d.len) - 1] == 0)d.len--, d.num.pop_back();
	}
	return c;
}
real real::radical(real b) {
	real a, c;
	a = *this;
	c = b.numerator;
	a = a ^ c;
	a.numerator = a.numerator.radical(b.denominator);
	a.denominator = a.denominator.radical(b.denominator);
	a.simplification();
}
void real::operator++(int) {
	this->numerator = this->denominator + this->numerator;
	if (!this->numerator.negative)
		if (!this->denominator.negative)this->negative = false;//同是正，得正
		else {
			//前正后负，得负
			this->denominator.negative = false;
			this->negative = true;
		}
	else
		if (!this->denominator.negative) {
			//前负后正，得负
			this->numerator.negative = false;
			this->negative = true;
		}
		else {
			//同是负，得负
			this->denominator.negative = this->numerator.negative = false;
			this->negative = true;
		}
	this->simplification();
}
void real::operator--(int) {
	this->numerator = this->denominator - this->numerator;
	if (!this->numerator.negative)
		if (!this->denominator.negative)this->negative = false;//同是正，得正
		else {
			//前正后负，得负
			this->denominator.negative = false;
			this->negative = true;
		}
	else
		if (!this->denominator.negative) {
			//前负后正，得负
			this->numerator.negative = false;
			this->negative = true;
		}
		else {
			//同是负，得负
			this->denominator.negative = this->numerator.negative = false;
			this->negative = true;
		}
	this->simplification();
}
void real::operator=(real a) {
	this->denominator = a.denominator;
	this->negative = a.negative;
	this->numerator = a.numerator;
}
void real::operator=(number a) {
	this->denominator = 1;
	this->numerator = a;
}
void real::operator=(double a) {
	string s, t;
	int b = a;
	while (b > 0) {
		t = t + char(b % 10);
		b /= 10;
	}
	reverse(s.begin(), s.end());
	if (b < 0)s = "-" + s;
	a = abs(a);
	if (abs(b - a) > 0) {
		a = b - a;
		s = s + ".";
		while (a > 0) {
			s = s + char(int(a * 10));
			a = a * 10 - int(a * 10);
		}
	}
	this->getNum(s);
}
void real::operator+=(real b) {
	real a = *this;
	*this = a + b;
}
void real::operator-=(real b) {
	real a = *this;
	*this = a - b;
}
void real::operator*=(real b) {
	real a = *this;
	*this = a * b;
}
void real::operator/=(real b) {
	real a = *this;
	*this = a / b;
}
bool real::operator<(real a) {
	real b;
	b = *this - a;
	if (b.negative)return true;
	return false;
}
bool real::operator>(real a) {
	real b;
	b = *this - a;
	if (!b.negative)return true;
	return false;
}
bool real::operator==(real a) {
	real b;
	b = *this - a;
	if (b.numerator == 0)return true;
	return false;
}
bool real::operator!=(real a) {
	return !(*this == a);
}