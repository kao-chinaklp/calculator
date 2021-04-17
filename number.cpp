#include"number.h"
#include<algorithm>
using namespace std;
void complement(number* a, int len) {
	for (; len > 0; len--)
		a->num.push_back(0), a->len++;
}
bool compare(number a, number b) {
	if (a.len < b.len)complement(&a, b.len - a.len);
	if (a.len > b.len)complement(&b, a.len - b.len);
	while (a.len > 1 && a.num[a.len - 1] == 0)a.len--;
	while (b.len > 1 && b.num[b.len - 1] == 0)b.len--;
	if (a.len < b.len)return true;
	if (a.len > b.len)return false;
	for (int i = (int)a.num.size() - 1; i >= 0; i--) {
		if (a.num[i] < b.num[i])return true;
		if (a.num[i] > b.num[i])return false;
	}
	return false;
}
number &number::operator+(number b) {
	number c;
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
	if (this->len < b.len)complement(this, b.len - this->len);
	if (this->len > b.len)complement(&b, this->len - b.len);
	c.len = max(this->len, b.len);
	c.num.resize(c.len);
	int t = 0;
	for (int i = 0; i < c.len; i++) {
		c.num[i] = this->num[i] + b.num[i] + t;
		t = c.num[i] / 10;
		c.num[i] %= 10;
	}
	if (t)c.num.push_back(t), c.len++;
	*this = c;
	return *this;
}
number &number::operator-(number b) {
	number c;
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
	if (this->len < b.len)complement(this, b.len - this->len);
	if (this->len > b.len)complement(&b, this->len - b.len);
	if (compare(*this, b)) {
		c.negative = true;
		swap(*this, b);
	}
	c.len = max(this->len, b.len);
	c.num.resize(c.len);
	for (int i = 0; i < c.len; i++) {
		if (this->num[i] < b.num[i]) {
			this->num[i + 1]--;
			this->num[i] += 10;
		}
		c.num[i] = this->num[i] - b.num[i];
	}
	while (c.len > 1 && c.num[c.len - 1] == 0) {
		c.len--;
		c.num.pop_back();
	}
	*this = c;
	return *this;
}
number &number::operator*(number b) {
	number c;
	if (this->negative && !b.negative) {
		this->negative = false;
		c.negative = true;
	}
	if (!this->negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = this->len + b.len;
	c.num.resize(c.len);
	for (int i = 0; i < this->len; i++)
		for (int j = 0; j < b.len; j++)
			c.num[i + j] += this->num[i] * b.num[j];
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
	while (c.len > 1 && c.num[c.len - 1] == 0) {
		c.len--;
		c.num.pop_back();
	}
	*this = c;
	return *this;
}
number& number::operator/(number b) {
	number c;
	if (this->negative && !b.negative) {
		this->negative = false;
		c.negative = true;
	}
	if (!this->negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = 1;
	c.num.push_back(0);
	if (this->len < b.len)complement(this, b.len - this->len);
	if (this->len > b.len)complement(&b, this->len - b.len);
	while (!compare(*this, b)) {
		c.num[0]++;
		for (int i = 0; i < c.len; i++) {
			if (c.num[i] < 10)break;
			c.num[i] %= 10;
			if (i + 1 == c.len)c.num.push_back(0), c.len++;
			c.num[i + 1]++;
		}
		*this = *this - b;
	}
	*this = c;
	return *this;
}
number& number::operator%(number b) {
	number c;
	if (this->negative && !b.negative) {
		this->negative = false;
		c.negative = true;
	}
	if (!this->negative && b.negative) {
		b.negative = false;
		c.negative = true;
	}
	c.len = 1;
	c.num.push_back(0);
	if (this->len < b.len)complement(this, b.len - this->len);
	if (this->len > b.len)complement(&b, this->len - b.len);
	while (!compare(*this, b))
		*this = *this - b;
	return *this;
}
number& number::operator^(number b) {
	number c, d, e;
	d.len = 1;
	d.num.push_back(2);
	e = b;
	d = e % d;
	if (d.num[0] == 1)
		this->negative = c.negative;
	c.len = 1;
	c.num.push_back(1);
	while (b.len != 1 || b.num[0] != 0) {
		c = c * (*this);
		b.num[0]--;
		for (int i = 0; i < b.len; i++) {
			if (b.num[i] >= 0)break;
			b.num[i] += 10;
			b.num[i + 1]--;
		}
		while (b.len > 1 && b.num[b.len - 1] == 0)b.len--, b.num.pop_back();
	}
	*this = c;
	return *this;
}