#include <iostream>
#include "calculator.h"
#include "logger.h"

int main() {
	Calculator* calc = new Calculator(new Logger());

	int a = calc->add(1,2);
	
	std::cout << a << std::endl;

	return 0;
}