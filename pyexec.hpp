//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_PYEXEC_HPP
#define METAPYTHON_PYEXEC_HPP

#include <iostream>
#include <string>
#include <python3.10/Python.h>

#include "helpers.hpp"
#include "defines.h"
#include "parsed_arguments.h"


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
		///   def __metagenerator__():string
		/// and returns it's return
		DECL_FUNCTION(inline const char*, execute, (const char* code, PyCompilerFlags* flags = nullptr, int optimize = 2))
		{
			if (verbose_flag)
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " INFO: compiling code... \n" C_RED "CODE" C_RESET "{\n"
				           << code
				           << "\n}" C_RED "CODE" C_RESET "\n";
			
			auto code_obj = Py_CompileStringObject(code, PyUnicode_FromString("@meta@"), Py_file_input, flags, optimize);
			if (!code_obj)
			{
				PyErr_Print();
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " ERROR: can't parse your code.\n";
				return nullptr;
			}
			
			
			auto module = PyImport_ExecCodeModule("@meta@", code_obj);
			if (!module)
			{
				PyErr_Print();
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " ERROR: can't create a module from code.\n";
				return nullptr;
			}
			
			
			auto dict = PyModule_GetDict(module);
			if (!dict)
			{
				PyErr_Print();
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " ERROR: this module have no attributes.\n";
				return nullptr;
			}
			
			
			auto func = PyDict_GetItemString(dict, "__metagenerator__");
			if (!func)
			{
				PyErr_Print();
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " ERROR: can't find function __metagenerator__.\n";
				return nullptr;
			}
			
			
			PyObject* object;
			
			if (!PyCallable_Check(func))
			{
				if (verbose_flag)
					log_stream << get_current_time() << FN_SIGNATURE(execute) << " WARNING: __metagenerator__ is not a function.\n";
				object = func;
			}
			else
			{
				object = PyObject_CallObject(func, nullptr);
			}
			
			
			if (!object)
			{
				PyErr_Print();
				log_stream << get_current_time() << FN_SIGNATURE(execute) << " ERROR: returned an exception.\n";
				return nullptr;
			}
			
			
			PyObject* representation;
			
			if (PyUnicode_Check(object))
				representation = PyUnicode_FromObject(object);
			else
				representation = PyObject_Repr(object);
			
			auto str = PyUnicode_AsUTF8(representation);
			
			if (verbose_flag)
				if (!str)
					log_stream << get_current_time() << FN_SIGNATURE(execute) << " INFO: returned an empty string.\n";
				else
					log_stream << get_current_time() << FN_SIGNATURE(execute) << " INFO: returned \"" << str << "\".\n";
			
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
