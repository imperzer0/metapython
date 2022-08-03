//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_PYCOMPILE_HPP
#define METAPYTHON_PYCOMPILE_HPP

#include <string>
#include <list>

#include "pyexec.hpp"


namespace py
{
	class pycompile
	{
	public:
		inline pycompile(const std::string& input_filename, const std::string& output_filename, std::ostream& log_stream)
				: input_filename(input_filename), output_filename(input_filename), log_stream(log_stream) { }
		
		
		/// Compiles all metacode in input_filename file and writes the output to output_filename
		DECL_FUNCTION(inline void, compile, (PyCompilerFlags * flags = nullptr, int optimize = 2))
		{
			if (!check_files_extensions())
				log_stream << get_current_time() << FN_SIGNATURE(compile)
				           << " WARNING: File \"" << input_filename << "\" and/or \"" << output_filename
				           << "\" has/have wierd extension(s)\n";
			
			FILE* ifile = ::fopen(input_filename.c_str(), "rb");
			if (!ifile)
			{
				log_stream << get_current_time() << FN_SIGNATURE(compile)
				           << " ERROR: Can't open file \"" << input_filename << "\" for reading\n";
				return;
			}
			
			FILE* ofile = ::fopen(output_filename.c_str(), "wb");
			if (!ofile)
			{
				log_stream << get_current_time() << FN_SIGNATURE(compile)
				           << " ERROR: Can't open file \"" << output_filename << "\" for writing\n";
				return;
			}
			
			if (verbose_flag)
				log_stream << get_current_time() << FN_SIGNATURE(compile)
				           << " INFO: Parsing the file \"" << input_filename << "\"...\n";
			
			std::list<char> quot_queue;
			
			size_t zaminach_count = 0;
			bool zaminach_area = false;
			std::string metacode;
			char c;
			while (true)
			{
				if (::feof(ifile)) break;
				
				c = ::fread(&c, sizeof c, 1, ifile);
				
				if (zaminach_area) metacode += c;
				
				if (c == '\'' || c == '"') // toggle string literals
				{
					if (quot_queue.empty())
						quot_queue.push_back(c);
					else if (quot_queue.back() == c)
						quot_queue.pop_back();
				}
				
				if (c == '@' && quot_queue.empty()) // check for @@@ not in the string literal
					++zaminach_count;
				else zaminach_count = 0;
				
				if (zaminach_count == 3)
				{
					if (!(zaminach_area = !zaminach_area)) // trigger once on ending zaminach
					{
						py::pyexec exec(log_stream);
						metacode.pop_back();
						metacode.pop_back();
						auto res = exec.execute(metacode.c_str(), flags, optimize);
						
						if (verbose_flag)
							log_stream << get_current_time() << FN_SIGNATURE(compile)
							           << " INFO: Writing execution result into \"" << output_filename << "\"...\n";
					}
				}
				
				if (!zaminach_area) metacode.clear(); // clear string if not in zaminach area
			}
		}
		
		inline ~pycompile() { }
		
		inline bool check_files_extensions()
		{
			return extension_of(input_filename) == ".mpy" && // metapython extension
			       extension_of(output_filename) == ".py";
		}
	
	private:
		std::string input_filename;
		std::string output_filename;
		std::ostream& log_stream;
		
		#ifdef TEST
	public:
		#endif
		
		inline static std::string extension_of(const std::string& filename)
		{
			size_t pos = filename.find_last_of('.');
			if (pos == std::string::npos) return "";
			else return filename.substr(pos);
		}
	};
	
}
#endif //METAPYTHON_PYCOMPILE_HPP
