#include <vector>
#include "NumberObject.h"
#include "Complex.h"

using namespace std;

NumberObject::NumberObject() {}
NumberObject::~NumberObject() {}
detail NumberObject::getDetail() {
	return detail("0", "1", "0", "1");
}

string NumberObject::getValue() {
	return "";
};

int NumberObject::getType() {
	return 0;
}

ostream& operator <<(ostream& stream, NumberObject& num) {
	stream << num.getValue();
	return stream;
}

NumberObject& operator +(NumberObject& num1, NumberObject& num2) {
	detail d1("0", "1", "0", "1"), d2("0", "1", "0", "1");
	d1 = num1.getDetail();
	d2 = num2.getDetail();

	NumberObject *result;

	if ((num1.getType() == 3) || (num2.getType() == 3)) {
		result = new Complex(Complex(Decimal(Integer(d1.numerR), Integer(d1.denominR)), Decimal(Integer(d1.numerZ), Integer(d1.denominZ))) + Complex(Decimal(Integer(d2.numerR), Integer(d2.denominR)), Decimal(Integer(d2.numerZ), Integer(d2.denominZ))));
	}
	else if ((num1.getType() == 2) || (num2.getType() == 2)) {
		result = new Decimal(Decimal(Integer(d1.numerR), Integer(d1.denominR)) + Decimal(Integer(d2.numerR), Integer(d2.denominR)));
	}
	else {
		result = new Integer((Integer(d1.numerR) + Integer(d2.numerR)));
	}
	return *result;
}

NumberObject& operator -(NumberObject& num1, NumberObject& num2) {
	detail d1("0", "1", "0", "1"), d2("0", "1", "0", "1");
	d1 = num1.getDetail();
	d2 = num2.getDetail();

	NumberObject *result;

	if ((num1.getType() == 3) || (num2.getType() == 3))	{
		result = new Complex(Complex(Decimal(Integer(d1.numerR), Integer(d1.denominR)), Decimal(Integer(d1.numerZ), Integer(d1.denominZ))) - Complex(Decimal(Integer(d2.numerR), Integer(d2.denominR)), Decimal(Integer(d2.numerZ), Integer(d2.denominZ))));
	}
	else if ((num1.getType() == 2) || (num2.getType() == 2)) {
		result = new Decimal(Decimal(Integer(d1.numerR), Integer(d1.denominR)) - Decimal(Integer(d2.numerR), Integer(d2.denominR)));
	}
	else {
		result = new Integer((Integer(d1.numerR) - Integer(d2.numerR)));
	}
	return *result;
}

NumberObject& operator *(NumberObject& num1, NumberObject& num2) {
	detail d1("0", "1", "0", "1"), d2("0", "1", "0", "1");
	d1 = num1.getDetail();
	d2 = num2.getDetail();

	NumberObject *result;

	if ((num1.getType() == 3) || (num2.getType() == 3)) {
		result = new Complex(Complex(Decimal(Integer(d1.numerR), Integer(d1.denominR)), Decimal(Integer(d1.numerZ), Integer(d1.denominZ))) * Complex(Decimal(Integer(d2.numerR), Integer(d2.denominR)), Decimal(Integer(d2.numerZ), Integer(d2.denominZ))));
	}
	else if ((num1.getType() == 2) || (num2.getType() == 2)) {
		result = new Decimal(Decimal(Integer(d1.numerR), Integer(d1.denominR)) * Decimal(Integer(d2.numerR), Integer(d2.denominR)));
	}
	else {
		result = new Integer((Integer(d1.numerR) * Integer(d2.numerR)));
	}
	return *result;
}

NumberObject& operator /(NumberObject& num1, NumberObject& num2) {
	detail d1("0", "1", "0", "1"), d2("0", "1", "0", "1");
	d1 = num1.getDetail();
	d2 = num2.getDetail();

	NumberObject *result;

	if ((num1.getType() == 3) || (num2.getType() == 3))	{
		result = new Complex(Complex(Decimal(Integer(d1.numerR), Integer(d1.denominR)), Decimal(Integer(d1.numerZ), Integer(d1.denominZ))) / Complex(Decimal(Integer(d2.numerR), Integer(d2.denominR)), Decimal(Integer(d2.numerZ), Integer(d2.denominZ))));
	}
	else if ((num1.getType() == 2) || (num2.getType() == 2)) {
		result = new Decimal(Decimal(Integer(d1.numerR), Integer(d1.denominR)) / Decimal(Integer(d2.numerR), Integer(d2.denominR)));
	}
	else {
		result = new Integer((Integer(d1.numerR) / Integer(d2.numerR)));
	}
	return *result;
}

int precedence(string opr) {
	if ((opr == "+") || (opr == "-")) {
		return 1;
	}
	else if ((opr == "*") || (opr == "/")) {
		return 2;
	}
	return 0;
}

void infixToPostfix(const vector<string>& infix, vector<string>& Postfix) {
	vector<string> stackForOperator;

	for (string element : infix) {
		if ((element.size() == 1) && ((element == "+") || (element == "-") || (element == "*") || (element == "/") || (element == "(") || (element == ")"))) {
			if (stackForOperator.size() == 0) {
				stackForOperator.push_back(element);
			}
			else	if (element[0] == ')') {
				while (stackForOperator.size() && (stackForOperator.back() != "(")) {
					Postfix.push_back(stackForOperator.back());
					stackForOperator.pop_back();
				}
				stackForOperator.pop_back();
			}
			else if (element == "(") {
				stackForOperator.push_back(element);
			}
			else {
				while (stackForOperator.size() && (precedence(stackForOperator.back()) >= precedence(element))) {
					Postfix.push_back(stackForOperator.back());
					stackForOperator.pop_back();
				}
				stackForOperator.push_back(element);
			}
		}
		else {
			Postfix.push_back(element);
		}
	}
	while (stackForOperator.size()) {
		Postfix.push_back(stackForOperator.back());
		stackForOperator.pop_back();
	}

}

void stringToInfix(string& command, vector<string>&infix) {
	string numStr = "";
	if (command[0] == '-')numStr.push_back('0');
	for (int i = 0; i < command.size(); i++) {
		if (i == command.size()) {
			infix.push_back(numStr);
			numStr.clear();
		}
		if (((command[i] == '+') || (command[i] == '-') || (command[i] == '*') || (command[i] == '/') || (command[i] == ')'))) {
			if (command[i] == ')' && (i < command.size()) && (command[i + 1]) == 'i') {
				int k = 0;
				int leftpar = 1;
				for (k = infix.size() - 1; leftpar != 0; k--) {
					if (infix[k] == ")") leftpar++;
					if (infix[k] == "(") leftpar--;
				}
				infix.insert(infix.begin() + k + 1, "(");

				command.insert(i + 2, ")");
				command.insert(i + 1, "*1");
			}
			if (numStr != "")
				infix.push_back(numStr);
			infix.push_back(command.substr(i, 1));
			numStr.clear();
		}
		else if ((command[i] == '(')) {
			infix.push_back(command.substr(i, 1));
			if (command[i + 1] == '-') {
				numStr.push_back('0');
			}
		}
		else {
			numStr.push_back(command[i]);
		}
	}
	if (numStr != "")
		infix.push_back(numStr);
	for (auto& a : infix) {
		if (a == "i") {
			a = "1i";
		}
	}
	return;
}

int haveOperator(const vector<string>& Postfix) {
	for (int index = 0; index<Postfix.size(); index++) {
		if ((Postfix[index] == "+") || (Postfix[index] == "/") || (Postfix[index] == "*") || (Postfix[index] == "-")) {
			return index;
		}
	}
	return 0;
}

NumberObject* calcPostfix(vector<string> Postfix) {
	vector<NumberObject*> PostFix;
	int typeOfResult = 0;

	for (int i = 0; i < Postfix.size(); i++) {
		if (Postfix[i].find("i") <Postfix[i].size()) {
			typeOfResult = 3;
			break;
		}
		else if (Postfix[i].find(".") <Postfix[i].size()) {
			if (typeOfResult < 2)typeOfResult = 2;
		}
		else {
			if (typeOfResult < 1)typeOfResult = 1;
		}
	}

	for (int i = 0; i < Postfix.size(); i++) {
		if ((Postfix[i] != "+") && (Postfix[i] != "-") && (Postfix[i] != "*") && (Postfix[i] != "/")) {
			switch (typeOfResult) {
			case 1:
				PostFix.push_back(new Integer(Postfix[i]));
				break;
			case 2:
				PostFix.push_back(new Decimal(Postfix[i]));
				break;
			case 3:
				PostFix.push_back(new Complex(Postfix[i]));
				break;
			}
		}
		else {
			PostFix.push_back(NULL);
		}
	}

	int location = 0;
	while (location = haveOperator(Postfix)) {
		switch (Postfix[location][0]) {
		case'+':
			PostFix[location] = &(*PostFix[location - 2] + *PostFix[location - 1]);

			Postfix[location] = "0";
			break;
		case'-':
			PostFix[location] = &(*PostFix[location - 2] - *PostFix[location - 1]);

			Postfix[location] = "0";
			break;
		case'*':
			PostFix[location] = &(*PostFix[location - 2] * *PostFix[location - 1]);

			Postfix[location] = "0";
			break;
		case'/':
			PostFix[location] = &(*PostFix[location - 2] / *PostFix[location - 1]);

			Postfix[location] = "0";
			break;
		}

		Postfix.erase(Postfix.begin() + location - 2, Postfix.begin() + location);

		delete PostFix[location - 2];
		delete PostFix[location - 1];
		PostFix.erase(PostFix.begin() + location - 2, PostFix.begin() + location);
	}
	return PostFix[0];
}

NumberObject* calc(string cal) {
	vector<string> infix;
	vector<string> Postfix;
	string resultStr;

	NumberObject *result;

	for (int i = 0; i < cal.size(); ++i) {
		try {
			throw cal[i];
		}
		catch (char v) {
			if (i == 0) {
				if (!(v >= '0' && v <= '9')) {
					if ((v != '(') && (v != '-') && (v != 'i') || (((v == '(') || (v == '-')) && cal.size() == 1)) {
						setColor(12);
						cout << "> Input error! Try again." << endl << endl;
						setColor(15);
						start(); /*Test Block*/
					}
				}
			}
			else {
				if (!(v >= '0' && v <= '9')) {
					if ((v != '+') && (v != '-') && (v != '*') && (v != '/') && (v != '(') && (v != ')') && (v != 'i') && (v != '.')) {
						setColor(12);
						cout << "> Input error! Try again." << endl << endl;
						setColor(15);
						start(); /*Test Block*/
					}
				}
			}
		}
	}

	stringToInfix(cal, infix);
	infixToPostfix(infix, Postfix);
	result = calcPostfix(Postfix);
	return result;
}