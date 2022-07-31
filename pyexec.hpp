//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_PYEXEC_HPP
#define METAPYTHON_PYEXEC_HPP

#include <iostream>
#include <string>
#include <python3.10/Python.h>

#include "get_current_time.hpp"


#define STR(exp) #exp

#define DECL_FUNCTION(fn_name, prefix, postfix) static constexpr const char* fn_name##_signature = STR(prefix fn_name postfix); \
prefix fn_name postfix

#define FN_SIGNATURE(name) name##_signature


namespace py
{
	class pyexec
	{
	public:
		inline pyexec(std::ostream& log_stream) : log_stream(log_stream)
		{
			Py_Initialize();
		}
		
		pyexec(const pyexec&) = delete;
		
		pyexec(pyexec&&) = delete;
		
		/// Executes python function with signature:
		///   def __generator__():string
		/// and returns it's return
		DECL_FUNCTION(execute, inline const char*, (const char* code, PyCompilerFlags* flags = nullptr, int optimize = 1))
		{
			auto module = Py_CompileStringExFlags(code, "@metacode@", 0, flags, optimize);
			
			if (module == nullptr)
			{
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " can't parse your code.\n";
				return nullptr;
			}
			
			
			auto func = PyObject_GetAttrString(module, "__generator__");
			auto object = PyObject_CallNoArgs(func);
			
			if (object == nullptr)
			{
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " returned an exception.\n";
				return nullptr;
			}
			
			
			auto representation = PyObject_Repr(object);
			auto str = PyUnicode_AsUTF8(representation);
			
			log_stream << get_current_time() << FN_SIGNATURE(execute) << " returned \"" << str << "\".\n";
			
			return str;
		}
		
		inline ~pyexec()
		{
			Py_Finalize();
		}
	
	private:
		std::ostream& log_stream;
		
	};
}

#endif //METAPYTHON_PYEXEC_HPP
