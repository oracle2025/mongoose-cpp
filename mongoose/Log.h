#pragma once

#ifdef ENABLE_LOGGING
#include <iostream>
#include <string>
#define LOG(x) std::cout << (x) << std::endl;
#else
#define LOG(x)
#endif

#define TRACE_FUNCTION LOG(__PRETTY_FUNCTION__)