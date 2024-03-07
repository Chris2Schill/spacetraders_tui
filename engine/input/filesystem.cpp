#include "filesystem.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace filesystem
{

std::string readSourceFile(const std::string filepath)
{
    std::ifstream fstream(filepath);
    if (fstream.fail())
    {
        std::cout << "[" __FILE__ << ":" << __LINE__ << "] "
                  << "[" << __FUNCTION__ << "]: "
                  << "error - failed to open file " << filepath << std::endl;
    }
    std::stringstream ss;

    std::string line;
    while (getline(fstream, line)) { ss << line << std::endl; }

    return ss.str();
}

} // end namespace filesystem
