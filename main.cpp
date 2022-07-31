#include <iostream>
#include "pyexec.hpp"


int main(int argc, char** argv)
{
	py::pyexec exec(std::cout);
	
	std::cout << exec.execute(
			"def __generator__():\n"
			"  return \"everything is ok\"\n"
	) << "\n";
	
	return 0;
}
