#include "log.h"

#include <iostream>
#include <iomanip>
#include <ctime>

namespace Util::Log
{

void write(const char* message)
{
    time_t t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::cout << std::put_time(&tm, "[%m-%d-%Y %H:%M:%S] ") << message << std::endl;
}

}