//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_PYCOMPILE_HPP
#define METAPYTHON_PYCOMPILE_HPP

#include <string>
#include "pyexec.hpp"


class pycompile
{
public:
	inline pycompile(const std::string& input_filename, const std::string& output_filename)
			: input_filename(input_filename), output_filename(input_filename) { }
	
	
	/// Does preprocessing on file
	inline void compile()
	{
		/// TODO: parse file, search for static section and execute it
	}
	
	inline ~pycompile() { }

private:
	std::string input_filename;
	std::string output_filename;
};

#endif //METAPYTHON_PYCOMPILE_HPP
