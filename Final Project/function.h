#pragma once
#include <windows.h>
#include "Complex.h"

int main();
void help();
void clear();
void record();
void graph();
void exit();
void setColor(int);

void help() {
	setColor(11);
	cout << "	This program can calculate: " << endl;
	cout << "	-Arithmetic of Integer " << endl;
	cout << "	-Arithmetic of Floating Point Number " << endl;
	cout << "	-Arithmetic of Complex Number " << endl << endl;
	cout << "	Here are all commands that you can use: " << endl;
	cout << "	-clear > Clear the screen " << endl;
	cout << "	-exit  > Exit the program " << endl << endl;
	setColor(15);
}

void clear() {
	system("cls");
	main();
}

void record() {

}

void graph() {
	cout << "             ____________________________________________________" << endl;
	cout << "            /                                                    \\ " << endl;
	cout << "           |    _____________________________________________     |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |  C:\> _                                      |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |                                             |    |" << endl;
	cout << "           |   |_____________________________________________|    |" << endl;
	cout << "           |                                                      |" << endl;
	cout << "            \\____________________________________________________/" << endl;
	cout << "                   \\_______________________________________/" << endl;
	cout << "                _______________________________________________" << endl;
	cout << "             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_" << endl;
	cout << "          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_" << endl;
	cout << "       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_" << endl;
	cout << "    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_" << endl;
	cout << " _-'.-.-.-.-.-. .---.-. .-----------------------------. .-.---. .---.-.-.-.`-_" << endl;
	cout << ":-----------------------------------------------------------------------------:" << endl;
	cout << "`---._.-----------------------------------------------------------------._.---'" << endl << endl;
}

void exit() {
	
	exit(0);
}

void setColor(int color) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}