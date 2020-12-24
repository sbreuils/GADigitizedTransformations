
#include <iostream>
#include <algorithm>

#include <vector>

#include "../include/scene.h"

/// Create a rotor representing a pi/2 rotation about the z-axis
/// Normalization is done automatically
kln::rotor R{M_PI * 0.5f, 0.f, 0.f, 1.f};




/// Create a translator that represents a translation of 1 unit
/// in the yz-direction. Normalization is done automatically.
kln::translator t{1.f, 0.f, 1.f, 1.f};






int main(){
    // define the scene
    std::vector<GATriplet> inputGAPixels;
    int height;
    int width;
    std::string inputImagePath("../img/ellipse10-6.pgm");
    std::string outputImagePath("../img/ellipse10-6_transformed.pgm");

    std::cout << "load image and convert to a grid of GA points ..." << std::endl;
    loadSceneFromImage(inputImagePath, inputGAPixels, height, width);


    // apply the digitized transformation
    // todo





    // write the resulting pixels into an image
    std::cout << "write the transformed grid of GA points into an image ..." << std::endl;
    writeSceneInImage(outputImagePath, inputGAPixels, width, height);



	return 0;
}