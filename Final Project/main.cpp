#include <iostream>

void start();
void setColor(int);
int main() {
	setColor(14);
	std::cout << "*****************************************************************************" << std::endl;
	std::cout << "***                                                                       ***" << std::endl;
	std::cout << "**                          Big Number Calculator                          **" << std::endl;
	std::cout << "***                                                                       ***" << std::endl;
	std::cout << "*****************************************************************************" << std::endl;
	std::cout << "-Type \"help\" to check the function." << std::endl << std::endl;
	setColor(15);
	start();
	return 0;
}
/*兩個運算元不能相連*/
/*運算元不能作為結尾*/
/*+(-5)*/
/*-1*-2*/