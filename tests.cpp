#include <iostream>
#include "pyexec.hpp"


void test(const std::string& str1, const std::string& str2)
{
	if (str1 == str2)
		std::cout << "(\"" << str1 << "\" == \" " << str2 << "\") \033[32mOK\033[0m\n";
	else
		std::cout << "(\"" << str1 << "\" != \" " << str2 << "\") \033[31mFAILED\033[0m\n";
}

void test_code_execution(const std::string& code, const std::string& ans)
{
	py::pyexec exec(std::cout);
	test(exec.execute(code.c_str()), ans);
}

int main(int argc, char** argv)
{
	test_code_execution(
			R"CODE(
def __metagenerator__():
	return "everything is ok"
)CODE",
			"everything is ok"
	);
	
	test_code_execution(
			R"CODE(__metagenerator__ = "everything is ok")CODE",
			"everything is ok"
	);
	
	test_code_execution(
			R"CODE(__metagenerator__ = 88)CODE",
			"88"
	);
	
	test_code_execution(
			R"CODE(__metagenerator__ = 88 + 1)CODE",
			"89"
	);
	
	test_code_execution(
			R"CODE(
def __metagenerator__():
	return 100
)CODE",
			"100"
	);
	
	return 0;
}