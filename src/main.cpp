
#include <iostream>
#include <algorithm>
#include <vector>

#include "GADigitizedTransformationImage.h"
#include "GADigitizedTransformationProperties.h"

#define DISTRIBUTION 0

#if DISTRIBUTION
    #include <opencv2/viz.hpp>
    #include <opencv2/viz/widgets.hpp>
#endif


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[]){

    if(cmdOptionExists(argv, argv+argc, "-i"))
    {
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
    }
    else{
        // Z2Grid gaZ2Grid;
        // createZ2Grid(gaZ2Grid, 100, 100); // \todo adapt the size of the grid
        // std::cout << "test involution of bijective digitized reflections ..." << std::endl;
        // bool isInvolution = isBijectiveDigitizedReflectionAnInvolution(gaZ2Grid,100);

#if DISTRIBUTION
        cv::viz::Viz3d bijectiveDigitizedReflections_distribution("distribution");
        bijectiveDigitizedReflections_distribution.spin();
#endif

        std::cout << "load Z3 grid as a grid of GA points ..." << std::endl;
        Z3Grid gaZ3Grid;
        createZ3Grid(gaZ3Grid, 50, 50, 50); // \todo adapt the size of the grid

        std::cout << "test bijectivity of digitized reflections ..." << std::endl;
        // kln::point normalVectorReflectionLine = kln::point(-4.0, 3.0, 0.0);
        
        // Not bijective
        // kln::plane reflectionPlane = kln::plane(sqrt(2.0), 5.0, 7.0, 0.0);

        // bijective 
        kln::plane reflectionPlane = kln::plane(-3.0, 4.0, 7.0, 0.0);
        bool isBijective = isDigitizedReflectionBijective(gaZ3Grid, reflectionPlane);

        (isBijective) ? std::cout << "digizited reflection associated to plane ("<< reflectionPlane.x() 
                                                                            <<","<< reflectionPlane.y() 
                                                                            <<","<< reflectionPlane.z() <<",0) is bijective" << std::endl 
                                                                            : 
                        std::cout << "digizited reflection associated to plane ("<< reflectionPlane.x() 
                                                                            <<","<< reflectionPlane.y() 
                                                                            <<","<< reflectionPlane.z() <<",0) is NOT bijective" << std::endl;
    }

	return 0;
}