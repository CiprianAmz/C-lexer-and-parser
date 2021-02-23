# include <iostream>
# include <string>
# include "scanner.h"
# include "token.h"
# include "parser.h"
# include "exceptions.h"

int main () {
	std::string fileName;
	std::cout << "Input file name: ";
	std::cin >> fileName ;
	try {
		Parser parser(fileName);
		parser.parse();
	}
	catch (Exception e) {
		e.print();
		return 1;
	}

	return 0;
}