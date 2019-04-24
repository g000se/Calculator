#include "Float.h"

Decimal::~Decimal() {}
Decimal::Decimal(Integer num) {
	numerator = num;
	denominator = Integer("1");
}

Decimal::Decimal(Integer num, Integer deno) {
	numerator = num;
	denominator = deno;
}

Decimal::Decimal(string inStr) {
	int opr = 0;
	for (int i = 1; i<inStr.size(); i++) {
		switch (inStr[i]) 		{
		case'+':case'*':case'/':case'(':case')':case'-':opr++; break;
		}
	}
	if (opr) {
		NumberObject* result = calc(inStr);
		inStr = result->getValue();
		delete result;
	}

	string numberatorStr = "";
	string denominatorStr = "";
	bool pushZeroToNumerator = 0;

	for (int i = 0; i < inStr.size(); i++) {
		if (pushZeroToNumerator) {
			denominatorStr.push_back('0');
		}
		if (inStr[i] == '.') {
			pushZeroToNumerator = 1;
			denominatorStr.push_back('1');
			while (inStr.back() == '0') {
				inStr.pop_back();
			}
		}
		else {
			numberatorStr.push_back(inStr[i]);
		}
	}
	if (!pushZeroToNumerator)
		denominatorStr.push_back('1');
	numerator = Integer(numberatorStr);
	denominator = Integer(denominatorStr);
}

Decimal::Decimal() {
	numerator = Integer();
	denominator = Integer("1");
}

string Decimal::getValue() {
	Integer afterdot("1" + string(100, '0'));

	stringstream temp;
	string actual = "";
	string afterAdd = "";
	int t = 0;

	temp << (numerator / denominator);
	temp >> actual;
	if (actual == "ERROR") {
		return "ERROR";
	}
	actual.push_back('.');
	temp.clear();
	temp << ((numerator*afterdot) / denominator);
	temp >> afterAdd;

	if (afterAdd[0] == '-')	{
		if (actual[0] != '-') {
			actual.insert(0, 1, '-');
		}
		afterAdd.erase(afterAdd.begin(), afterAdd.begin() + 1);
	}
	while (afterAdd.size() > 100) {
		afterAdd.erase(afterAdd.begin(), afterAdd.begin() + 1);
	}
	while (afterAdd.size() < 100) {
		afterAdd.insert(0, 1, '0');
	}
	return actual + afterAdd;
}


istream& operator >> (istream& input, Decimal& in) {
	string inStr = "";
	input >> inStr;
	in = Decimal(inStr);
	return input;
}

Decimal operator+(Decimal float1, Decimal float2) {
	return Decimal((float1.numerator*float2.denominator) + (float2.numerator*float1.denominator), (float1.denominator*float2.denominator));
}

Decimal operator-(Decimal float1, Decimal float2) {
	return Decimal((float1.numerator*float2.denominator) - (float2.numerator*float1.denominator), (float1.denominator*float2.denominator));
}

Decimal operator*(Decimal float1, Decimal float2) {
	return Decimal((float1.numerator*float2.numerator), (float2.denominator*float1.denominator));
}

Decimal operator/(Decimal float1, Decimal float2) {
	return Decimal((float1.numerator*float2.denominator), (float2.numerator*float1.denominator));
}

int Decimal::getType() {
	return 2;
}

Decimal operator+(Decimal float1, Integer num) {
	return float1 + Decimal(num);
}

Decimal operator-(Decimal float1, Integer num) {
	return float1 - Decimal(num);
}

Decimal operator*(Decimal float1, Integer num) {
	return float1 * Decimal(num);
}

Decimal operator/(Decimal float1, Integer num) {
	return float1 / Decimal(num);
}

Decimal operator+(Integer num, Decimal float1) {
	return Decimal(num) + float1;
}

Decimal operator-(Integer num, Decimal float1) {
	return Decimal(num) - float1;
}

Decimal operator*(Integer num, Decimal float1) {
	return Decimal(num) * float1;
}

Decimal operator/(Integer num, Decimal float1) {
	return Decimal(num) / float1;
}

detail Decimal::getDetail() {
	return detail(numerator.getValue(), denominator.getValue(), "0", "1");
}

string Decimal::getDenominator() {
	return denominator.getValue();
}

string Decimal::getNumerator() {
	return numerator.getValue();
}