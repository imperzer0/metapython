//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_PYCOMPILE_HPP
#define METAPYTHON_PYCOMPILE_HPP

#include <string>

#include "pyexec.hpp"


namespace py
{
	class pycompile
	{
	public:
		inline pycompile(const std::string& input_filename, const std::string& output_filename, std::ostream& log_stream)
				: input_filename(input_filename), output_filename(input_filename), log_stream(log_stream) { }
		
		
		/// Compiles all metacode in input_filename file and writes the output to output_filename
		DECL_FUNCTION(inline void, compile, ())
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
			
			/// TODO: parse ifile, search for static section, execute it and write the result into ofile
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
