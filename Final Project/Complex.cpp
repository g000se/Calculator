#include "Complex.h"

Complex::Complex() {
	real = Decimal("0");
	ministry = Decimal("0");
}

Complex::Complex(string input) {
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
	int i = input.size();
	string R = "";
	string Z = "";

	if (input.find("i") < input.size()) {
		for (i = int(input.find("i") - 1); i >= 0; i--)	{
			Z.insert(Z.begin(), input[i]);
			if ((input[i] == '+') || (input[i] == '-'))	{
				break;
			}
		}
		if (Z[0] == '+')
			Z.erase(Z.begin());
		ministry = Decimal(Z);
	}
	if (i> 0) {
		for (i--; i >= 0; i--) {
			R.insert(R.begin(), input[i]);
			if ((input[i] == '+') || (input[i] == '-'))	{
				break;
			}
		}
		if (R[0] == '+')
			R.erase(R.begin());
		real = Decimal(R);
	}
	else {
		real = Decimal("0");
	}
}
Complex::~Complex() {}

Complex::Complex(Decimal R, Decimal Z) {
	real = R;
	ministry = Z;
}

Complex::Complex(Decimal R) {
	real = R;
	ministry = Decimal("0");
}

Complex::Complex(Integer R) {
	real = Decimal(R);
	ministry = Decimal("0");
}

Complex operator+(Complex complex1, Complex complex2) {
	return Complex(complex1.real + complex2.real, complex1.ministry + complex2.ministry);
}

Complex operator-(Complex complex1, Complex complex2) {
	return Complex(complex1.real - complex2.real, complex1.ministry - complex2.ministry);
}

Complex operator*(Complex complex1, Complex complex2) {
	return Complex(((complex1.real*complex2.real) - (complex1.ministry*complex2.ministry)), ((complex1.real*complex2.ministry) + (complex2.real*complex1.ministry)));
}

Complex operator/(Complex complex1, Complex complex2) {
	Decimal denominator(complex2.real*complex2.real + complex2.ministry*complex2.ministry);
	Complex result = complex1*Complex(complex2.real, complex2.ministry*Decimal("-1"));
	result.real = result.real / denominator;
	result.ministry = result.ministry / denominator;
	return result;
}

string Complex::getValue() {
	stringstream output;
	stringstream temp;
	string R = "";
	string Z = "";
	temp << real;
	temp >> R;
	temp.clear();
	temp << ministry;
	temp >> Z;
	temp.clear();

	for (int i = 0; i < R.size(); i++) {
		output << R[i];
		if (R[i] == '.') {
			for (int j = 1; j < 11; j++) {
				output << R[i + j];
			}
			break;
		}
	}
	if (Z[0] != '-') output << '+';
	for (int i = 0; i < Z.size(); i++) {
		output << Z[i];
		if (Z[i] == '.') {
			for (int j = 1; j < 11; j++) {
				output << Z[i + j];
			}
			output << 'i';
			break;
		}
	}
	return output.str();
}

istream& operator >> (istream& input, Complex& complex) {
	string temp = "";
	input >> temp;
	complex = Complex(temp);
	return input;
}

int Complex::getType() {
	return 3;
}

Complex operator+(Complex complex, Decimal float1) {
	return complex + Complex(float1);
}

Complex operator-(Complex complex, Decimal float1) {
	return complex - Complex(float1);
}

Complex operator*(Complex complex, Decimal float1) {
	return complex * Complex(float1);
}

Complex operator/(Complex complex, Decimal float1) {
	return complex / Complex(float1);
}

Complex operator+(Decimal float1, Complex complex) {
	return Complex(float1) + complex;
}

Complex operator-(Decimal float1, Complex complex) {
	return Complex(float1) - complex;
}

Complex operator*(Decimal float1, Complex complex) {
	return Complex(float1) * complex;
}

Complex operator/(Decimal float1, Complex complex) {
	return Complex(float1) / complex;
}

Complex operator+(Complex complex, Integer num) {
	return complex + Complex(num);
}

Complex operator-(Complex complex, Integer num) {
	return complex - Complex(num);
}

Complex operator*(Complex complex, Integer num) {
	return complex * Complex(num);
}

Complex operator/(Complex complex, Integer num) {
	return complex / Complex(num);
}

Complex operator+(Integer num, Complex complex) {
	return Complex(num) + complex;
}

Complex operator-(Integer num, Complex complex) {
	return Complex(num) - complex;
}

Complex operator*(Integer num, Complex complex) {
	return Complex(num) * complex;
}

Complex operator/(Integer num, Complex complex) {
	return Complex(num) / complex;
}

detail Complex::getDetail() {
	return detail(real.getNumerator(), real.getDenominator(), ministry.getNumerator(), ministry.getDenominator());
}