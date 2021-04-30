
#ifndef GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H
#define GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H

#include "GADigitizedRotation.h"

#include "scene.h"

#include "GATransformationsGeneration.h"


// test in 2D, and the grid has points defined in the plane
bool isBijectiveDigitizedReflectionAnInvolution(Z2Grid grid, int kmax){
    bool isInvolution = true;
    int numberOfDifferentPoints=0;
    for(int k = 0 ; k< kmax ; ++k) {
        GADigitizedReflectionNormalVector digitizedRef(-(k+1), k,0);

        for (auto pt1 : grid) {
            kln::point pt1_reflected = digitizedRef(pt1);

            kln::point pt1_reflected_twice = digitizedRef(pt1_reflected);

            if (pt1_reflected_twice.x() != pt1.x() || pt1_reflected_twice.y() != pt1.y()) {
                numberOfDifferentPoints++;
                isInvolution = false;
            }
        }
    }
    return isInvolution;
}


bool isDigitizedReflectionBijective(const Z3Grid& grid, const kln::plane& reflectionPlane){
    bool isBijective = true;
    int numberOfDifferentPoints=0;
    GADigitizedReflection digitizedRef(reflectionPlane);

    std::cout << "number of grid points that are tested =" << grid.size() << std::endl;

    for (auto pt1 : grid) {
        kln::point pt1_reflected = digitizedRef(pt1);
        kln::point pt1_reflected_twice = digitizedRef(pt1_reflected);

        if (pt1_reflected_twice.x() != pt1.x() || pt1_reflected_twice.y() != pt1.y() || pt1_reflected_twice.z() != pt1.z() ) { // components are integers
            numberOfDifferentPoints++;
            isBijective = false;
        }
    }
    return isBijective;
}


std::vector<kln::plane> setOfBijectiveReflectionsFromSetOfPlanes(const Z3Grid& grid, const std::vector<kln::plane>& reflectionPlanes){
    
    std::vector<kln::plane> bijectiveReflections;
    std::cout << "number of grid points that are tested =" << grid.size() << std::endl;
    
    // loop over all input digitized reflections
    for(auto plane : reflectionPlanes){
        bool isBijective = true;
        int numberOfDifferentPoints=0;
        GADigitizedReflection digitizedRef(plane);

        // loop over all points in the grid
        for (auto pt1 : grid) {
            kln::point pt1_reflected = digitizedRef(pt1);
            kln::point pt1_reflected_twice = digitizedRef(pt1_reflected);

            if (pt1_reflected_twice.x() != pt1.x() || pt1_reflected_twice.y() != pt1.y() || pt1_reflected_twice.z() != pt1.z() ) { // components are integers
                numberOfDifferentPoints++;
                isBijective = false;
            }
        }

        if(isBijective){
            bijectiveReflections.push_back(plane);
        }

    }
    return bijectiveReflections;
}


bool isDigitizedReflectionBijective_withLineCondition(Z3Grid grid, kln::plane reflectionPlane){
    bool isBijective = true;
    int numberOfDifferentPoints=0;
    GADigitizedReflection digitizedRef(reflectionPlane);

    std::cout << "number of grid points that are tested =" << grid.size() << std::endl;

//    kln::point ptOriginCell1 = kln::point( -0.5, -0.5 ,0.5);
//    kln::point ptOriginCell2 = kln::point( -0.5, 0.5 ,0.5);
//    kln::point ptOriginCell3 = kln::point( 0.5, 0.5 ,0.5);


    for (auto pt1 : grid) {
        kln::point pt1_reflected = digitizedRef(pt1);
        kln::point pt1_reflected_twice = digitizedRef(pt1_reflected);

        if (pt1_reflected_twice.x() != pt1.x() || pt1_reflected_twice.y() != pt1.y() || pt1_reflected_twice.z() != pt1.z() ) { // components are integers
            numberOfDifferentPoints++;
            isBijective = false;
        }
    }
    return isBijective;
}




#endif //GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H
