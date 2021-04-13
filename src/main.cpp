
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

#include "GADigitizedTransformationImage.h"
#include "GADigitizedTransformationProperties.h"
#include "ExternalFilesUtilities.h"

#define DISTRIBUTION 0

#if DISTRIBUTION
    #include <opencv2/viz.hpp>
    #include <opencv2/viz/widgets.hpp>
    #include <opencv2/core/mat.hpp> // for displaying cloud of points
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

    // add the file containing bijective digitized reflections in the space
    std::string dataBijectiveDigitizedTransformation;

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



        std::cout << "load Z3 grid as a grid of GA points ..." << std::endl;
        Z3Grid gaZ3Grid;
        createZ3Grid(gaZ3Grid, 50, 50, 50); // \todo adapt the size of the grid

        std::cout << "test bijectivity of digitized reflections ..." << std::endl;
        // kln::point normalVectorReflectionLine = kln::point(-4.0, 3.0, 0.0);


        // Generate digital reflections through definitions of planes in a domain
        // std::vector<kln::plane> gaPlanes = gaPlanesGeneration(10, 0.0f, pi/4.0, 0.0, pi/4.0);
        const int lenDomain = 20;
        TransformationDomain digitizedReflectionDomain = std::make_tuple(0.0,pi/4.0, 0.0, pi/4.0); 
        GAPlanesGeneration gaPlanesGenerator;
        std::vector<kln::plane> gaPlanes = gaPlanesGenerator(lenDomain,digitizedReflectionDomain);

        // Not bijective
        // kln::plane reflectionPlane = kln::plane(sqrt(2.0), 5.0, 7.0, 0.0);

        // numerically characterize bijective digitized reflections


        // bijective 
        // kln::plane reflectionPlane = kln::plane(-3.0, 4.0, 7.0, 0.0);
        // bool isBijective = isDigitizedReflectionBijective(gaZ3Grid, gaPlanes[0]);

        std::vector<kln::plane> setBijectiveDigitizedReflections = setOfBijectiveReflectionsFromSetOfPlanes(gaZ3Grid, gaPlanes);

        // display
        for(auto gaBijectivePlane : setBijectiveDigitizedReflections){
            std::cout << "digizited reflection associated to plane ("<< gaBijectivePlane.x() 
                                                                            <<","<< gaBijectivePlane.y() 
                                                                            <<","<< gaBijectivePlane.z() <<",0) is bijective" << std::endl;
        }

        // write in file
        writeFile(bijectivePlanesToString(setBijectiveDigitizedReflections), "../listBijectiveDigitizedReflections/bijectiveDigitizedReflectionsSpace.txt");

        


#if DISTRIBUTION
        cv::viz::Viz3d bijectiveDigitizedReflections_distribution("distribution");
        bijectiveDigitizedReflections_distribution.setBackgroundColor(cv::viz::Color::white());
    
        cv::Point3d Orig(0.0, 0.0, 0.0);
        cv::viz::WSphere sphere(Orig, 1.0, 20, cv::viz::Color::blue());
        sphere.setRenderingProperty(cv::viz::LINE_WIDTH, 4.0);



        // display point cloud
        std::vector<cv::Point3f> pointVec; 
	    std::vector<cv::Vec3b> colorVec;   

        for(auto plane : setBijectiveDigitizedReflections){
            pointVec.push_back(cv::Point3f(plane.x(), plane.y(), plane.z()));
    	    colorVec.push_back(cv::Vec3b(0, 2, 128));
        }
    
        // bijectiveDigitizedReflections_distribution.showWidget("Axis widget", cv::viz::WCoordinateSystem());
        // bijectiveDigitizedReflections_distribution.showWidget("sphere widget", sphere);

    	cv::viz::WCloud cloud_widget(pointVec, colorVec);
        cloud_widget.setRenderingProperty(cv::viz::POINT_SIZE,5.0);

        bijectiveDigitizedReflections_distribution.showWidget("cloud", cloud_widget);


        while(!bijectiveDigitizedReflections_distribution.wasStopped()) {
            bijectiveDigitizedReflections_distribution.spinOnce(1, true);
        }


#endif

    }

	return 0;
}