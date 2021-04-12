
#ifndef GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H
#define GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H

#include "GADigitizedRotation.h"
#include "scene.h"

// test in 2D, and the grid has points defined in the plane
bool isBijectiveDigitizedReflectionAnInvolution(Z2Grid grid, int kmax){
    bool isInvolution = true;
    int numberOfDifferentPoints=0;
    for(int k = 0 ; k< kmax ; ++k) {
        GADigitizedReflection digitizedRef(-(k+1), k,0);

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


bool isDigitizedReflectionBijective(Z3Grid grid, kln::point normalVector){
    bool isBijective = true;
    int numberOfDifferentPoints=0;
    GADigitizedReflection digitizedRef(normalVector);

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





#endif //GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONPROPERTIES_H
