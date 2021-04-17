#include"calculator.h"
#include<Windows.h>
#include<string>
#include<iostream>
using namespace std;
int main() {
	system("color f0");
	cout << "格式：a b 操作符，(暂不支持连续运算)\n";
	calculator c;
	c.run();
	system("pause");
	return 0;
}