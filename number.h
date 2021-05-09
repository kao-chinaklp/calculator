#pragma once
#ifndef NUMBER_H
#define NUMBER_H
#include<vector>
#include<string>
#include<stdio.h>
class number
{
public:
	number() :len(0), negative(false) { num.clear(); };
	int len;//整数位数
	bool negative;//负号
	std::vector<int>num;//本体
	void getNum(std::string s) {
		if (s[0] == '-') {
			this->negative = true;
			s.erase(0, 1);
		}
		this->len = (int)s.size();
		this->num.resize(this->len);
		for (int i = this->len - 1; i >= 0; i--)
			this->num[static_cast<unsigned __int64>(this->len) - i - 1] = s[i] - 48;
	}
	void showNum() {
		if (this->negative)
			if (this->len != 1 || this->num[0] != 0)printf("-");
		for (int i = this->len - 1; i >= 0; i--)
			printf("%d", this->num[i]);
		//printf("\n");
	}
	number operator+(number b);
	number operator-(number b);
	number operator*(number b);
	number operator/(number b);
	number operator%(number b);
	number operator^(number b);
	void operator++(int);
	void operator--(int);

private:

};
#endif // !NUMBER_H