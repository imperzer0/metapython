#include <iostream>
#include <getopt.h>
#include <deque>
#include "pycompile.hpp"


static std::deque<std::string> inputs, outputs;
static const char* appname = "metapython";

static constexpr const struct option long_opts[] = {
		{ "input",  required_argument, nullptr, 'i' },
		{ "output", required_argument, nullptr, 'o' },
		{ nullptr,  no_argument,       nullptr, 0 }
};

static constexpr const char* short_opts = "i:o:";

void help(int exit_code = 0);

void parse_args(int argc, char** argv);

int main(int argc, char** argv)
{
	parse_args(argc, argv);
	return 0;
}

#define C_RESET "\u001b[0m"

#define C_BLACK "\u001b[30m"
#define C_RED "\u001b[31m"
#define C_GREEN "\u001b[32m"
#define C_YELLOW "\u001b[33m"
#define C_BLUE "\u001b[34m"
#define C_MAGENTA "\u001b[35m"
#define C_CYAN "\u001b[36m"

#define C_BOLD_BLACK "\u001b[30;1m"
#define C_BOLD_RED "\u001b[31;1m"
#define C_BOLD_GREEN "\u001b[32;1m"
#define C_BOLD_YELLOW "\u001b[33;1m"
#define C_BOLD_BLUE "\u001b[34;1m"
#define C_BOLD_MAGENTA "\u001b[35;1m"
#define C_BOLD_CYAN "\u001b[36;1m"
#define C_BOLD_WHITE "\u001b[37;1m"

void help(int exit_code)
{
	::printf(C_RESET "HELP\n\nUsage: " C_BOLD_MAGENTA "%s" C_RESET " [ARGS]...\n", appname);
	::printf(C_RESET "Arguments:\n", appname);
	::printf(C_RESET "  " C_GREEN "-i" C_RESET " | " C_BOLD_BLUE "--input " C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "input path\n");
	::printf(C_RESET "  " C_GREEN "-o" C_RESET " | " C_BOLD_BLUE "--output" C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "output path\n\n");
	::printf(C_RESET C_BOLD_WHITE "*You can use multiple -i and -o parameters which will compile multiple files.\n");
	::printf(C_RESET C_BOLD_WHITE " But the amount of -i and -o arguments must be the same.\n");
	::printf(C_RESET C_BOLD_WHITE " Also if you are using directory as input you must specify a directory as an\n");
	::printf(C_RESET C_BOLD_WHITE " output (or an non-existing path, which means that directory will be created).\n");
	::printf(C_RESET C_BOLD_WHITE " Input and output arguments are adding to the separate lists.\n");
	::printf(C_RESET C_BOLD_WHITE " It means that you can write something like this:\n");
	::printf(
			C_RESET " " C_BOLD_MAGENTA "%s" C_BOLD_BLUE " -i" C_BOLD_WHITE " file1.mpy"
			C_BOLD_BLUE " -i" C_BOLD_WHITE " file2.mpy" C_BOLD_BLUE " -o" C_BOLD_WHITE " file1.py"
			C_BOLD_BLUE " -i" C_BOLD_WHITE " dir3-in/" C_BOLD_BLUE " -o" C_BOLD_WHITE " file2.py"
			C_BOLD_BLUE " -o" C_BOLD_WHITE " dir3-out/\n",
			appname
	);
	::printf(C_RESET C_BOLD_WHITE " Compiler will interpret it as:\n");
	::printf(C_RESET C_BOLD_WHITE " file1.mpy -> file1.py\n");
	::printf(C_RESET C_BOLD_WHITE " file2.mpy -> file2.py\n");
	::printf(C_RESET C_BOLD_WHITE " dir3-in/ -> dir3-out/\n");
	::printf(C_RESET);
	::exit(exit_code);
}

void parse_args(int argc, char** argv)
{
	appname = argv[0];
	
	if (argc < 2) help();
	
	int option_index = 0, c;
	while ((c = getopt_long(argc, argv, short_opts, long_opts, &option_index)) < 0)
	{
		switch (c)
		{
			case 'i':
				inputs.push_back(::optarg);
				break;
			
			case 'o':
				outputs.push_back(::optarg);
				break;
			
			default:
				help(-1);
		}
	}
	
}
