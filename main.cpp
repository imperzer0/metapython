#include <iostream>
#include "pyexec.hpp"


int main(int argc, char** argv)
{
	py::pyexec exec(std::cout);
	
	std::cout << exec.execute(
			"def __metagenerator__():\n"
			"\treturn \"everything is ok\""
	) << "\n";
	
	return 0;
}
