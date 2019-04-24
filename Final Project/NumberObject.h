#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void start();
void setColor(int);
struct detail {
	detail(string nR, string dR, string nZ, string dZ) :numerR(nR), denominR(dR), numerZ(nZ), denominZ(dZ) {};;
	string numerR;
	string denominR;
	string numerZ;
	string denominZ;
};

class NumberObject {
public:
	NumberObject();
	virtual ~NumberObject();
	virtual int getType(); //Integer=1 Decimal=2 Complex=3
	virtual string getValue();
	virtual detail getDetail();
	friend ostream& operator <<(ostream&, NumberObject&);
	friend NumberObject& operator +(NumberObject&, NumberObject&);
	friend NumberObject& operator -(NumberObject&, NumberObject&);
	friend NumberObject& operator *(NumberObject&, NumberObject&);
	friend NumberObject& operator /(NumberObject&, NumberObject&);
};

int precedence(string);
void infixToPostfix(const vector<string>&, vector<string>&);
void stringToInfix(string&, vector<string>&);
NumberObject* calcPostfix(vector<string>);
NumberObject* calc(string);