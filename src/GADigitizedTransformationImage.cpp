
#include "GADigitizedTransformationImage.h"

void digitizedRotationImage(const std::vector<GATriplet>& pixels, std::vector<GATriplet>& transformedpixels, double angle){

    // define the transformation functor, here a digitized rotation
    GADigitizedRotation digTransfo(angle);

    GAPixelTransformation* gaPixelTransfo = new GADigitizedRotationCreator(angle);

    // could use std::transform instead
    for(unsigned int i=0 ;i<pixels.size() ; ++i ){
        transformedpixels.push_back((*gaPixelTransfo)(pixels[i]));
    }
}