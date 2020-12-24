
#include "GADigitizedTransformationImage.h"

void digitizedRotationImage(const std::vector<GATriplet>& pixels, std::vector<GATriplet>& transformedpixels, double angle){

    // define the transformation functor, here a digitized rotation
    GAPixelTransformation gaPixelRotor(angle);

    // could use std::transform instead
    for(unsigned int i=0 ;i<pixels.size() ; ++i ){
        transformedpixels.push_back(gaPixelRotor(pixels[i]));
    }
}