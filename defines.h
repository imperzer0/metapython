//
// Created by imper on 8/2/22.
//

#ifndef METAPYTHON_DEFINES_H
#define METAPYTHON_DEFINES_H


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


#define STR(exp) #exp

#define FN_STR(keywords, fn_name, arguments) \
        C_MAGENTA STR(keywords) " " C_RESET C_BOLD_CYAN STR(fn_name) C_RESET C_YELLOW STR(arguments) C_RESET
#define DECL_FUNCTION(keywords, fn_name, arguments) \
        static constexpr const char* fn_name##_signature = FN_STR(keywords, fn_name, arguments); \
        keywords fn_name arguments

#define FN_SIGNATURE(name) name##_signature


#endif //METAPYTHON_DEFINES_H
