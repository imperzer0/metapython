#include <cstdio>
#include <getopt.h>
#include <dirent.h>

#include "pycompile.hpp"
#include "defines.h"
#include "parsed_arguments.h"


static constexpr const struct option long_opts[] = {
		{ "input",   required_argument, nullptr,       'i' },
		{ "output",  required_argument, nullptr,       'o' },
		{ "verbose", no_argument,       &verbose_flag, 'v' },
		{ "version", no_argument,       nullptr,       'V' },
		{ "help",    no_argument,       nullptr,       'h' },
		{ nullptr,   no_argument,       nullptr,       0 }
};

static constexpr const char* short_opts = "i:o:vhV";


std::deque<std::basic_string<char>> tmpins, tmpouts;


void version();

void help(int exit_code = 0);

void parse_args(int argc, char** argv);

void print_compile_table();

void compile_all_files();


int main(int argc, char** argv)
{
	parse_args(argc, argv);
	print_compile_table();
	compile_all_files();
	return 0;
}



auto system(const std::string& command)
{
	return ::system(command.c_str());
}

void expand_directory_into_list(const std::string& input_prefix, const std::string& output_prefix, const std::string& directory = "")
{
	DIR* dir;
	struct dirent* entry;
	
	if (!(dir = opendir((input_prefix + directory).c_str())))
		return;
	
	while ((entry = readdir(dir)))
	{
		auto path = directory + "/" + entry->d_name;
		if (entry->d_type == DT_DIR)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			::system("mkdir -p" + std::string(verbose_flag ? "v" : "") + " \"" + output_prefix + path + "\"");
			expand_directory_into_list(input_prefix, output_prefix, path);
		}
		else
		{
			inputs.push_back(input_prefix + path);
			outputs.push_back(output_prefix + path + ".py");
		}
	}
	closedir(dir);
	
}

void compile_all_files()
{
	tmpins = inputs;
	tmpouts = outputs;
	inputs = outputs = { };
	
	struct stat sti, sto;
	for (auto i = tmpins.begin(), o = tmpouts.begin(); i != tmpins.end() && o != tmpouts.end(); ++i, ++o)
	{
		sti = { };
		sto = { };
		int resi = ::stat(i->c_str(), &sti);
		int reso = ::stat(o->c_str(), &sto);
		
		if (resi < 0)
		{
			std::cerr << "Can't find filesystem entry \"" << *i << "\"\n";
			::exit(-4);
		}
		
		if (S_ISDIR(sti.st_mode))
		{
			if (reso >= 0 && !S_ISDIR(sto.st_mode))
			{
				std::cerr << "\"" << *i << "\" is a directory but \"" << *o << "\" in not (and can't be).";
				::exit(-3);
			}
			else if (reso < 0) ::system("mkdir -p" + std::string(verbose_flag ? "v" : "") + " \"" + *o + "\"");
			
			expand_directory_into_list(*i, *o);
		}
		else if (S_ISREG(sti.st_mode))
		{
			if (S_ISREG(sto.st_mode) || reso < 0)
			{
				inputs.push_back(*i);
				outputs.push_back(*o);
			}
			else
			{
				std::cerr << "\"" << *i << "\" is a regular file but \"" << *o << "\" in not (and can't be).";
				::exit(-6);
			}
		}
		else
		{
			std::cerr << "\"" << *i << "\" is not a file or directory\n";
			::exit(-5);
		}
	}
	
	for (auto i = inputs.begin(), o = outputs.begin(); i != inputs.end() && o != outputs.end(); ++i, ++o)
	{
		py::pycompile compile(*i, *o, std::cerr);
		compile.compile();
	}
}

void print_compile_table()
{
	if (inputs.size() != outputs.size())
	{
		std::cerr << "An error occurred during arguments' parse: inputs.size() != outputs.size(): "
		          << inputs.size() << " != " << outputs.size() << "\n"
		                                                          "You must specify the same amount of inputs and outputs (check help)";
		::exit(-2);
	}
	std::cout << "Compile table:\n";
	for (auto i = inputs.begin(), o = outputs.begin(); i != inputs.end() && o != outputs.end(); ++i, ++o)
	{
		std::cout << "\t" << *i << " -> " << *o << "\n";
	}
}

void version()
{
	::printf(C_YELLOW "Version of " C_BOLD_MAGENTA APPLICATION_NAME C_RESET ": " C_BOLD_BLUE APPLICATION_VERSION "\n\n");
}

void help(int exit_code)
{
	version();
	
	::printf(C_RESET "HELP\n\nUsage: " C_BOLD_MAGENTA APPLICATION_NAME C_RESET " [ARGS]...\n");
	::printf(C_RESET "Arguments:\n");
	::printf(C_RESET "  " C_GREEN "-i" C_RESET " | " C_BOLD_BLUE "--input  " C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "input path\n");
	::printf(C_RESET "  " C_GREEN "-o" C_RESET " | " C_BOLD_BLUE "--output " C_BOLD_YELLOW " <path>  " C_BOLD_WHITE "output path\n");
	::printf(C_RESET "  " C_GREEN "-v" C_RESET " | " C_BOLD_BLUE "--verbose" C_BOLD_YELLOW "         " C_BOLD_WHITE "verbose output\n");
	::printf(
			C_RESET "  " C_GREEN "-V" C_RESET " | " C_BOLD_BLUE "--version" C_BOLD_YELLOW "         " C_BOLD_WHITE "print application version\n"
	);
	::printf(C_RESET "  " C_GREEN "-h" C_RESET " | " C_BOLD_BLUE "--help   " C_BOLD_YELLOW "         " C_BOLD_WHITE "get help\n");
	::printf(C_RESET "\n");
	::printf(C_RESET C_BOLD_WHITE "*You can use multiple -i and -o parameters which will compile multiple files.\n");
	::printf(C_RESET C_BOLD_WHITE " But the amount of -i and -o arguments must be the same.\n");
	::printf(C_RESET C_BOLD_WHITE " Also if you are using directory as input you must specify a directory as an\n");
	::printf(C_RESET C_BOLD_WHITE " output (or an non-existing path, which means that directory will be created).\n");
	::printf(C_RESET C_BOLD_WHITE " Input and output arguments are adding to the separate lists.\n");
	::printf(C_RESET C_BOLD_WHITE " It means that you can write something like this:\n");
	::printf(
			C_RESET " " C_BOLD_MAGENTA APPLICATION_NAME C_BOLD_BLUE " -i" C_BOLD_WHITE " file1.mpy"
			C_BOLD_BLUE " -i" C_BOLD_WHITE " file2.mpy" C_BOLD_BLUE " -o" C_BOLD_WHITE " file1.py"
			C_BOLD_BLUE " -i" C_BOLD_WHITE " dir3-in/" C_BOLD_BLUE " -o" C_BOLD_WHITE " file2.py"
			C_BOLD_BLUE " -o" C_BOLD_WHITE " dir3-out/\n"
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
			
			case 'V':
				version();
				::exit(0);
			
			default:
				help(-1);
		}
	}
	
}
