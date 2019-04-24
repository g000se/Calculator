#include <fstream>
#include "Complex.h"
#include "function.h"

int main();
void start() {
	string command = "";
	ofstream Ouput("Answer.txt");
	cout << "Input Formula: ";
	while (cin >> command) {
		if (command == "help") {
			help();
		}
		else if (command == "clear") {
			clear();
		}
		else if (command == "exit") {
			exit();
		}
		else if (command == "graph") {
			graph();
		}
		else if (command == "record") {

		}
		else {
			NumberObject* result;
			result = calc(command);
			//Answer
			setColor(12);
			cout << "> " << *result << " " << endl << endl;
			Ouput << *result << endl << "==========================" << endl;
			setColor(15);
			delete result;
			command.clear();
		}
		cout << "Input Formula: ";
	}
	return;
}