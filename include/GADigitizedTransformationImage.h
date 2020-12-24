
#ifndef GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONIMAGE_H
#define GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONIMAGE_H

#include "scene.h"
#include "GAPixelTransformation.h"

/// transform pixels of an image through a non necessarely bijective digitized rotation
void digitizedRotationImage(const std::vector<GATriplet>& pixels, std::vector<GATriplet>& transformedpixels, double angle);

#endif //GADIGITALTRANSFO_GADIGITIZEDTRANSFORMATIONIMAGE_H
