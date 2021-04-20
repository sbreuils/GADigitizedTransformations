

#include "ExternalFilesUtilities.h"
#include <string>


std::string bijectivePlanesDetailedToString(const std::vector<kln::plane>& gaPlanes){
    std::string data("");

    // test if after one scale approximation we find a Pythagorean triple (with line of reflection either (2k+1,1) or (k+1,k))
    for(int i=0 ; i< gaPlanes.size() ; ++i){
        kln::plane gaBijectivePlane = gaPlanes[i];
        float x = gaBijectivePlane.x();
        float y = gaBijectivePlane.y();

        float k_pi_over_four = y/(x-y);
        float k_zero = (x-y)/(2.0f*y);
        if(std::abs(std::round(k_pi_over_four)-k_pi_over_four) < std::abs(std::round(k_zero)-k_zero) && std::abs(std::round(k_pi_over_four)-k_pi_over_four) < epsilon ){
            data += std::to_string(gaBijectivePlane.x()) + ", " + std::to_string(gaBijectivePlane.y()) + ", " + std::to_string(gaBijectivePlane.z())
                 + " ; ( "+ std::to_string(k_pi_over_four+1)+ " ,"+ std::to_string(k_pi_over_four) + ")\n"; //"Bijective digitized reflection, associated k Pi/4 = "<< k_pi_over_four << std::endl;
        }else{
            if(std::abs(std::round(k_zero)-k_zero) < std::abs(std::round(k_pi_over_four)-k_pi_over_four) && std::abs(std::round(k_zero)-k_zero) < epsilon){
//                data += "Bijective digitized reflection, associated k 0 = " +  std::to_string(k_zero) + "\n";
                data += std::to_string(gaBijectivePlane.x()) + ", " + std::to_string(gaBijectivePlane.y()) + ", " + std::to_string(gaBijectivePlane.z())
                        + " ; ( "+ std::to_string(2*k_zero+1)+ " ,"+ std::to_string(1) + ")\n"; //"Bijective digitized reflection, associated k Pi/4 = "<< k_pi_over_four << std::endl;
            }else{
                if(k_zero == 0){
                    data += std::to_string(gaBijectivePlane.x()) + ", " + std::to_string(gaBijectivePlane.y()) + ", " + std::to_string(gaBijectivePlane.z())
                         + " ; ( "+ std::to_string(2*k_zero+1)+ " ,"+ std::to_string(1) + ")\n";
                }else{
                    data += std::to_string(gaBijectivePlane.x()) + ", " + std::to_string(gaBijectivePlane.y()) + ", " + std::to_string(gaBijectivePlane.z()) + "\n";
                }
            }
        }
    }

    return data;
}


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
