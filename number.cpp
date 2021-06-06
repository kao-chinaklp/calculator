#include"number.h"
#include<algorithm>
using namespace std;
void complement(number* a, int len) {
	for (; len > 0; len--)
		a->num.push_back(0), a->len++;
}//²¹Áã
number number::operator+(number b) {
	number a = *this, c;
	if (a.negative)
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
	if (a.len < b.len)complement(&a, b.len - a.len);
	if (a.len > b.len)complement(&b, a.len - b.len);
	c.len = max(a.len, b.len);
	c.num.resize(c.len);
	int t = 0;
	for (int i = 0; i < c.len; i++) {
		c.num[i] = a.num[i] + b.num[i] + t;
		t = c.num[i] / 10;
		c.num[i] %= 10;
	}
	if (t)c.num.push_back(t), c.len++;
	return c;
}
number number::operator-(number b) {
	number a = *this, c;
	if (a.negative)
		if (b.negative) {
			a.negative = b.negative = false;
			swap(a, b);
		}
		else {
			a.negative = false;
			c = a + b;
			c.negative = true;
			return c;
		}
	else
		if (b.negative) {
			b.negative = false;
			return a + b;
		}
	if (a.len < b.len)complement(&a, b.len - a.len);
	if (a.len > b.len)complement(&b, a.len - b.len);
	if (a > b) {
		c.negative = true;
		swap(a, b);
	}
	c.len = max(a.len, b.len);
	c.num.resize(c.len);
	for (int i = 0; i < c.len; i++) {
		if (a.num[i] < b.num[i]) {
			a.num[static_cast<unsigned __int64>(i) + 1]--;
			a.num[i] += 10;
		}
		c.num[i] = a.num[i] - b.num[i];
	}
	while (c.len > 1 && c.num[static_cast<unsigned __int64>(c.len) - 1] == 0) {
		c.len--;
		c.num.pop_back();
	}
	return c;
}
number number::operator*(number b) {
	number a = *this, c;
	if (a.negative && !b.negative) {
		a.negative = false;
		c.negative = true;
	}
	if (!a.negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = a.len + b.len;
	c.num.resize(c.len);
	for (int i = 0; i < a.len; i++)
		for (int j = 0; j < b.len; j++)
			c.num[static_cast<unsigned __int64>(i) + j] += a.num[i] * b.num[j];
	int t = 0;
	for (int i = 0; i < c.len; i++) {
		c.num[i] += t;
		t = c.num[i] / 10;
		c.num[i] %= 10;
	}
a1:
	if (t) {
		c.num.push_back(t % 10);
		t /= 10;
		goto a1;
	}
	while (c.len > 1 && c.num[static_cast<unsigned __int64>(c.len) - 1] == 0) {
		c.len--;
		c.num.pop_back();
	}
	return c;
}
number number::operator/(number b) {
	number a = *this, c;
	if (a.negative && !b.negative) {
		a.negative = false;
		c.negative = true;
	}
	if (!a.negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = 1;
	c.num.push_back(0);
	if (a.len < b.len)complement(&a, b.len - a.len);
	if (a.len > b.len)complement(&b, a.len - b.len);
	while (a > b) {
		c++;
		a = a - b;
	}
	return c;
}
number number::operator%(number b) {
	number a = *this, c;
	if (a.negative && !b.negative) {
		a.negative = false;
		c.negative = true;
	}
	if (!a.negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = 1;
	c.num.push_back(0);
	if (a.len < b.len)complement(&a, b.len - a.len);
	if (a.len > b.len)complement(&b, a.len - b.len);
	while (a > b)
		a = a - b;
	return a;
}
number number::operator^(number b) {
	number a = *this, c, d, e;
	d.len = 1;
	d.num.push_back(2);
	e = b;
	d = e % d;
	if (d.num[0] == 1)
		a.negative = c.negative;
	c.len = 1;
	c.num.push_back(1);
	while (b.len != 1 || b.num[0] != 0) {
		c = c * a;
		b--;
		while (b.len > 1 && b.num[static_cast<unsigned __int64>(b.len) - 1] == 0)b.len--, b.num.pop_back();
	}
	return c;
}
number radical(number a, number b) {
	number c;
	c.len = 1;
	c.num.push_back(0);
	while (a > (c ^ b)) c++;
	c--;
	return c;
}
void number::operator++(int) {
	number a;
	a.num.push_back(1);
	a.len = 1;
	*this = *this + a;
}
void number::operator--(int) {
	number a;
	a.num.push_back(1);
	a.len = 1;
	*this = *this - a;
}
void number::operator+=(number b) {
	number a = *this;
	*this = a + b;
}
void number::operator-=(number b) {
	number a = *this;
	*this = a - b;
}
void number::operator*=(number b) {
	number a = *this;
	*this = a * b;
}
void number::operator/=(number b) {
	number a = *this;
	*this = a / b;
}
void number::operator%=(number b) {
	number a = *this;
	*this = a % b;
}
void number::operator=(int a) {
	while (a) {
		this->num.push_back(a % 10);
		this->len++;
		a /= 10;
	}
}
bool number::operator>(number a) {
	if (this->len > a.len)return true;
	if (this->len < a.len)return false;
	for (int i = static_cast<unsigned __int64>(a.len) - 1; i >= 0; i--)
		if (this->num[i] <= a.num[i])return false;
	return true;
}
bool number::operator<(number a) {
	if (this->len < a.len)return true;
	if (this->len > a.len)return false;
	for (int i = static_cast<unsigned __int64>(a.len) - 1; i >= 0; i--)
		if (this->num[i] >= a.num[i])return false;
	return true;
}
bool number::operator==(number a) {
	if (this->len != a.len)return false;
	for (int i = static_cast<unsigned __int64>(a.len) - 1; i >= 0; i--)
		if (this->num[i] != a.num[i])return false;
	return true;
}
bool number::operator!=(number a) {
	return !(*this == a);
}
bool number::operator>(int a) {
	number b;
	b = a;
	return *this > b;
}
bool number::operator<(int a) {
	number b;
	b = a;
	return *this < b;
}
bool number::operator==(int a) {
	number b;
	b = a;
	return *this == b;
}
bool number::operator!=(int a) {
	number b;
	b = a;
	return *this != b;
}