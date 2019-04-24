#pragma once
#include "NumberObject.h"

class Integer :public NumberObject {
private:
	string digits;
	bool check();
public:
	Integer(string);
	Integer();
	virtual ~Integer();
	//length
	int length();
	virtual  string getValue();
	int getType();
	virtual detail getDetail();
	// operator overload
	friend Integer operator +(Integer, Integer);
	friend Integer operator -(Integer, Integer);
	friend Integer operator *(Integer, Integer);
	friend Integer operator /(Integer, Integer);
	friend istream& operator >>(istream&, Integer&);
	friend bool operator ==(Integer, Integer);
};