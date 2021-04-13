
#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>


#include <klein/klein.hpp>
#include <vector>
#include <tuple> 

/// Basic tools to manipulate files and directories.

std::string bijectivePlanesToString(const std::vector<kln::plane>& gaPlanes);

std::string readFile(const std::string& fileName);

bool writeFile(const std::string& data, const std::string& fileName);
