#include <iostream>
#include "pyexec.hpp"


int main(int argc, char** argv)
{
	py::pyexec exec(std::cout);
	
	std::cout << exec.execute(
			"def __metagenerator__():\n"
			"\treturn \"everything is ok\""
	) << "\n";
	
	std::cout << exec.execute(
			"__metagenerator__ = \"everything is ok\""
	) << "\n";
	
	std::cout << exec.execute(
			"__metagenerator__ = 88"
	) << "\n";
	
	return 0;
}
