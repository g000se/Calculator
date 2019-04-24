#include "Number.h"

bool Integer::check() {
	int i, s = 1;
	string b = digits;
	while (digits[0] > '9' || digits[0] < '0') {
		if (digits[0] == '+') {
			digits.erase(digits.begin());
		}
		else if (digits[0] == '-') {
			s *= -1;
			digits.erase(digits.begin());
		}
		else {
			digits = b;
			return true;
		}
	}
	while (digits[0] == '0'&&digits.length() > 1) {
		digits.erase(digits.begin());
	}
	for (i = 0; i < digits.length(); i++) {
		if (digits[i] > '9' || digits[i] < '0')	{
			digits = b;
			return true;
		}
	}
	if (s < 0 && digits[0] != '0') {
		digits = "-" + digits;
	}
	return false;
}

Integer::Integer(string input) {
	int opr = 0;
	for (int i = 1; i<input.size(); i++) {
		switch (input[i]) {
		case'+':case'*':case'/':case'(':case')':case'-':opr++; break;
		}
	}
	if (opr) {
		NumberObject* result = calc(input);
		input = result->getValue();
		delete result;
	}

	bool allzero = 1;
	string sign = "";

	if (input[0] == '-') {
		sign.push_back('-');
		input.erase(input.begin());
	}

	for (char a : input) {
		if (a != '0')
			allzero = 0;
	}

	if (!allzero) {
		while (input[0] == '0')	{
			input.erase(input.begin());
		}
	}
	digits = sign + input;
}

Integer::Integer() {
	digits.push_back('0');
}

Integer::~Integer() {}

int Integer::length() {
	return digits.size();
}

Integer operator+(Integer num1, Integer num2) {

	if (num1.check() || num2.check()) {
		return Integer("ERROR");
	}
	int i, k, sa = 1, sb = 1;
	string c;
	if (num1.digits[0] == '-') {
		sa = -1;
		num1.digits.erase(num1.digits.begin());
	}
	if (num2.digits[0] == '-') {
		sb = -1;
		num2.digits.erase(num2.digits.begin());
	}
	if (num1.digits.length()<num2.digits.length() || (num1.digits.length() == num2.digits.length() && num1.digits.compare(num2.digits)<0)) {
		c = num1.digits;
		k = sa;
		num1.digits = num2.digits;
		sa = sb;
		num2.digits = c;
		sb = k;
	}
	k = 0;
	for (i = 1; i <= num1.digits.length(); i++) {
		num1.digits[num1.digits.length() - i] += k;
		if (i <= num2.digits.length()) {
			num1.digits[num1.digits.length() - i] += (num2.digits[num2.digits.length() - i] - '0')*sa*sb;
		}
		if (num1.digits[num1.digits.length() - i] < '0') {
			num1.digits[num1.digits.length() - i] += 10;
			k = -1;
		}
		else if (num1.digits[num1.digits.length() - i] > '9') {
			num1.digits[num1.digits.length() - i] -= 10;
			k = 1;
		}
		else {
			k = 0;
		}
	}
	if (k) {
		num1.digits = "1" + num1.digits;
	}
	if (sa < 0) {
		num1.digits = "-" + num1.digits;
	}
	num1.check();
	return Integer(num1.digits);
}

Integer operator-(Integer num1, Integer num2) {
	if (num1.check() || num2.check())
		return Integer("ERROR");
	if (num2.digits[0] == '-')
		num2.digits.erase(num2.digits.begin());
	else
		num2.digits = "-" + num2.digits;
	return num1 + num2;
}

Integer operator*(Integer num1, Integer num2) {
	if (num1.check() || num2.check())
		return Integer("ERROR");
	int i, s = 1;
	Integer c = "0", d[10];
	d[0].digits = "0";
	if (num2.digits[0] == '-') {
		s = -1;
		num2.digits.erase(num2.digits.begin());
	}
	for (i = 1; i < 10; i++) {
		d[i] = d[i - 1] + num1;
	}
	for (i = 0; i < num2.digits.length(); i++) {
		c = c + Integer(d[num2.digits[i] - '0'].digits + string(num2.digits.length() - i - 1, '0'));
	}
	if (s < 0) {
		if (c.digits[0] == '-')
			c.digits.erase(c.digits.begin());
		else
			c.digits = "-" + c.digits;
	}
	c.check();
	return c;
}

Integer operator/(Integer num1, Integer num2) {
	if (num1.check() || num2.check())
		return Integer("ERROR");
	if (num2.digits == "0")
		return Integer("ERROR");
	int i, s = 1;
	Integer c = "0";
	if (num1.digits[0] == '-') {
		s *= -1;
		num1.digits.erase(num1.digits.begin());
	}
	if (num2.digits[0] == '-') {
		s *= -1;
		num2.digits.erase(num2.digits.begin());
	}
	i = num1.digits.length() - num2.digits.length();
	if (i>0)
		num2.digits = num2.digits + string(i, '0');
	while (i >= 0) {
		c = c*Integer("10");
		while (num1.digits.length()>num2.digits.length() || (num1.digits.length() == num2.digits.length() && num1.digits.compare(num2.digits) >= 0)) {
			num1 = num1 - num2;
			c = c + Integer("1");
		}
		num2.digits.erase(num2.digits.end() - 1);
		i--;
	}
	if (s<0)
		c.digits = "-" + c.digits;
	c.check();
	return c;
}

string Integer::getValue() {
	return digits;
}

istream& operator >>(istream& stream, Integer& num) {
	string strNum;
	stream >> strNum;
	num = Integer(strNum);
	return stream;
}

bool operator ==(Integer num1, Integer num2) {
	if (num1.digits == num2.digits)
		return true;
	else
		return false;
}

int Integer::getType() {
	return 1;
}

detail Integer::getDetail() {
	return detail(digits, "1", "0", "1");
}