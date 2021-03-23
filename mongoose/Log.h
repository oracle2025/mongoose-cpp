#pragma once

#ifdef ENABLE_LOGGING
#include <iostream>
#include <string>
#define LOG(x) std::cout << (x) << std::endl;
#else
#define LOG(x)
#endif

#define TRACE_FUNCTION std::cout << (__FILE__) << ": " << (__LINE__) << ": " << (__PRETTY_FUNCTION__) << std::endl;