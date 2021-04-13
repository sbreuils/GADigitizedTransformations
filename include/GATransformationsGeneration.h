
#pragma once


#include <klein/klein.hpp>
#include <vector>

constexpr double pi = 3.14159265358979323846;


/// generate a set of transformations in a considered range, e.g. slant are considered for digitized reflections


/// for digitized reflections in the space, generate a set of planes whose inclinations vary in minAngleLongitude,minAngleLongitude and minAngleLatitude,maxAngleLatitude
/// N^2 is the number of generated planes
std::vector<kln::plane> gaPlanesGeneration(const int N, const float minAngleLongitude, 
                                                        const float maxAngleLongitude, 
                                                        const float minAngleLatitude, 
                                                        const float maxAngleLatitude);


                                    