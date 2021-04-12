
#include "GADigitizedTransformationImage.h"

void digitizedRotationImage(const std::vector<GATriplet>& pixels, std::vector<GATriplet>& transformedpixels, double angle){

    GAPixelTransformation* gaPixelTransfo = new GADigitizedRotationCreator(angle);

    // \todo use std::transform instead
    for(const auto & pixel : pixels){
        transformedpixels.push_back((*gaPixelTransfo)(pixel));
    }
}