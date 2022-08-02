#include <cstdio>
#include <getopt.h>

#include "pycompile.hpp"
#include "defines.h"
#include "parsed_arguments.h"


static constexpr const struct option long_opts[] = {
		{ "input",   required_argument, nullptr,       'i' },
		{ "output",  required_argument, nullptr,       'o' },
		{ "verbose", no_argument,       &verbose_flag, 'v' },
		{ "help",    no_argument,       nullptr,       'h' },
		{ nullptr,   no_argument,       nullptr,       0 }
};

static constexpr const char* short_opts = "i:o:vh";

void help(int exit_code = 0);

void parse_args(int argc, char** argv);

void print_compile_table();

int main(int argc, char** argv)
{
	parse_args(argc, argv);
	print_compile_table();
	return 0;
}

void print_compile_table()
{
	if (inputs.size() != outputs.size())
	{
		std::cerr << "An error occurred during arguments' parse: inputs.size() != outputs.size(): "
		          << inputs.size() << " != " << outputs.size() << "\n"
		                                                          "You must specify the same amount of inputs and outputs (check help)";
		exit(-2);
	}
	std::cout << "Compile table:\n";
	for (auto i = inputs.begin(), j = outputs.begin(); i != inputs.end() && j != outputs.end(); ++i, ++j)
	{
		std::cout << "\t" << *i << " -> " << *j << "\n";
	}
}

void help(int exit_code)
{
	::printf(C_RESET "HELP\n\nUsage: " C_BOLD_MAGENTA "%s" C_RESET " [ARGS]...\n", appname);
	::printf(C_RESET "Arguments:\n", appname);
	::printf(C_RESET "  " C_GREEN "-i" C_RESET " | " C_BOLD_BLUE "--input  " C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "input path\n");
	::printf(C_RESET "  " C_GREEN "-o" C_RESET " | " C_BOLD_BLUE "--output " C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "output path\n");
	::printf(C_RESET "  " C_GREEN "-v" C_RESET " | " C_BOLD_BLUE "--verbose" C_BOLD_YELLOW "         " C_BOLD_WHITE "verbose output\n");
	::printf(C_RESET "  " C_GREEN "-h" C_RESET " | " C_BOLD_BLUE "--help   " C_BOLD_YELLOW "         " C_BOLD_WHITE "get help\n");
	::printf(C_RESET "\n");
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
	while ((c = getopt_long(argc, argv, short_opts, long_opts, &option_index)) >= 0)
	{
		switch (c)
		{
			case 'i':
				inputs.push_back(::optarg);
				break;
			
			case 'o':
				outputs.push_back(::optarg);
				break;
			
			case 'v':
				break;
			
			case 'h':
				help();
			
			default:
				help(-1);
		}
	}
	
}
