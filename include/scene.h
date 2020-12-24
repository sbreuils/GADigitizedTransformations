
#ifndef GADIGITALTRANSFO_SCENE_H
#define GADIGITALTRANSFO_SCENE_H


#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>


#include <Eigen/Eigenvalues>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iterator>
#include <random>
#include <cstring>

#include <klein/klein.hpp>


struct GATriplet
{
    kln::point klnPt;
    uchar val;
};

/// load scene from image and convert it to a triplet kln point with gray level
void loadSceneFromImage(std::string imagePath, std::vector<GATriplet>& pixels, int& height, int& width);

/// write the resulting pixels (kln points, gray levels) into an image
void writeSceneInImage(std::string imagePath, const std::vector<GATriplet> pixels, const int width,
                       const int height);

#endif //GADIGITALTRANSFO_SCENE_H
