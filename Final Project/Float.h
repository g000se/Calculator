#pragma once
#include "Number.h"

class Decimal :public NumberObject {
private:
	Integer numerator;
	Integer denominator;
public:
	Decimal(Integer);
	Decimal(Integer, Integer);
	Decimal(string);
	Decimal();
	~Decimal();

	string getNumerator();
	string getDenominator();
	virtual string getValue();
	int getType();
	virtual detail getDetail();
	//operator overload
	friend istream& operator >>(istream&, Decimal&);
	friend Decimal operator +(Decimal, Decimal);
	friend Decimal operator -(Decimal, Decimal);
	friend Decimal operator *(Decimal, Decimal);
	friend Decimal operator /(Decimal, Decimal);
	//---------------------------------------------------float & number
	friend Decimal operator +(Decimal, Integer);
	friend Decimal operator -(Decimal, Integer);
	friend Decimal operator *(Decimal, Integer);
	friend Decimal operator /(Decimal, Integer);

	friend Decimal operator +(Integer, Decimal);
	friend Decimal operator -(Integer, Decimal);
	friend Decimal operator *(Integer, Decimal);
	friend Decimal operator /(Integer, Decimal);
};