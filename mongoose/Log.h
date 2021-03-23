#pragma once
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef ENABLE_LOGGING
#include <iostream>
#include <string>
#define LOG(x) std::cout << (x) << std::endl;
#else
#define LOG(x)
#endif

#define TRACE_FUNCTION std::cout << (__FILENAME__) << ": " << (__LINE__) << ": " << (__PRETTY_FUNCTION__) << std::endl;