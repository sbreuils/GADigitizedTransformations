
#include "GATransformationsGeneration.h"



std::vector<kln::plane> gaPlanesGeneration(const int N, const float minAngleLongitude, 
                                                        const float maxAngleLongitude, 
                                                        const float minAngleLatitude, 
                                                        const float maxAngleLatitude){
    std::vector<kln::plane> planesVector;


    planesVector.push_back(kln::plane(-3.0, 4.0, 7.0, 0.0));


    return planesVector;


}