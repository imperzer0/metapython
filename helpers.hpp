//
// Created by imper on 7/31/22.
//

#ifndef METAPYTHON_HELPERS_HPP
#define METAPYTHON_HELPERS_HPP

#include <ctime>


#define TIME_FORMAT " [ %d.%m.%y  %H:%M:%S ] "


inline static char* get_current_time()
{
	time_t rawtime;
	time(&rawtime);
	auto timeinfo = localtime(&rawtime);
	auto buffer = new char[64];
	::strftime(buffer, 64, TIME_FORMAT, timeinfo);
	buffer[63] = 0;
	return buffer;
}

#endif //METAPYTHON_HELPERS_HPP
