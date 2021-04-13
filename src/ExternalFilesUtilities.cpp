

#include "ExternalFilesUtilities.h"
#include <string>

std::string bijectivePlanesToString(const std::vector<kln::plane>& gaPlanes){
    std::string data("");

    for(auto plane : gaPlanes){
        data += std::to_string(plane.x()) + ", " + std::to_string(plane.y()) + ", " + std::to_string(plane.z()) + "\n"; 
    }

    return data;
}

bool writeFile(const std::string &data, const std::string &fileName) {

    std::ofstream myfile(fileName,std::ios::out | std::ios::app); // output and add at the end of file
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << fileName << std::endl;
        return false;
    }

    myfile << data;
    myfile.close();

    return true;
}


std::string readFile(const std::string &fileName) {

    std::ifstream myfile;
    myfile.open(fileName, std::ios::in);

    // check if the file is opened
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    // copy the data to a string
    std::string data;
    data.assign( (std::istreambuf_iterator<char>(myfile)) , (std::istreambuf_iterator<char>()) );

    myfile.close();

    return data;
}
