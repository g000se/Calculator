#pragma once
#include "Float.h"

class Complex :public NumberObject {
private:
	Decimal real;
	Decimal ministry;
public:
	Complex(string);
	Complex(Decimal);
	Complex(Integer);
	Complex(Decimal, Decimal);
	~Complex();
	Complex();

	int getType();
	virtual string getValue();
	virtual detail getDetail();
	//operator overload
	friend Complex operator +(Complex, Complex);
	friend Complex operator -(Complex, Complex);
	friend Complex operator *(Complex, Complex);
	friend Complex operator /(Complex, Complex);
	friend istream& operator >>(istream&, Complex&);
	//-----------------------------------------------------complex & float
	friend Complex operator +(Complex, Decimal);
	friend Complex operator -(Complex, Decimal);
	friend Complex operator *(Complex, Decimal);
	friend Complex operator /(Complex, Decimal);

	friend Complex operator +(Decimal, Complex);
	friend Complex operator -(Decimal, Complex);
	friend Complex operator *(Decimal, Complex);
	friend Complex operator /(Decimal, Complex);
	//-----------------------------------------------------complex & number
	friend Complex operator +(Complex, Integer);
	friend Complex operator -(Complex, Integer);
	friend Complex operator *(Complex, Integer);
	friend Complex operator /(Complex, Integer);

	friend Complex operator +(Integer, Complex);
	friend Complex operator -(Integer, Complex);
	friend Complex operator *(Integer, Complex);
	friend Complex operator /(Integer, Complex);
};