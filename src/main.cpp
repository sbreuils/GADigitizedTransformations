
#include <iostream>
#include <algorithm>

#include <vector>

#include "GADigitizedTransformationImage.h"
#include "GADigitizedTransformationProperties.h"

#define IMAGE 0
#define GRID 1




int main(){

#if IMAGE
    // define the scene
    std::vector<GATriplet> inputGAPixels;
    std::vector<GATriplet> transformedGAPixels;
    int height;
    int width;
    std::string inputImagePath("../img/ellipse10-6.pgm");
    std::string outputImagePath("../img/ellipse10-6_transformed.pgm");

    std::cout << "load image and convert to a grid of GA points ..." << std::endl;
    loadSceneFromImage(inputImagePath, inputGAPixels, height, width);


    // apply the digitized transformation
    digitizedRotationImage(inputGAPixels, transformedGAPixels, M_PI_4);


    // apply the bijective digitized transformation


    // write the resulting pixels into an image
    std::cout << "write the transformed grid of GA points into an image ..." << std::endl;
    writeSceneInImage(outputImagePath, transformedGAPixels, width, height);
#endif

#if GRID
    std::cout << "load Z2 grid as a grid of GA points ..." << std::endl;
    Z2Grid gaZ2Grid;
    createZ2Grid(gaZ2Grid, 1000, 1000);


    std::cout << "test involution of bijective digitized reflections ..." << std::endl;
    bool isInvolution = isBijectiveDigitizedReflectionAnInvolution(gaZ2Grid,100);

    (isInvolution) ? std::cout << "bijective digizited reflection is an involution" << std::endl : std::cout << "bijective digizited reflection is NOT an involution" << std::endl;

#endif

	return 0;
}