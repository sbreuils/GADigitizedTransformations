
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

constexpr float epsilon = 1e-2;

struct GATriplet
{
    kln::point klnPt;
    uchar val;
};


typedef std::vector<kln::point> Z2Grid;

typedef std::vector<kln::point> Z3Grid;

/// load scene from image and convert it to a triplet kln point with gray level
void loadSceneFromImage(std::string imagePath, std::vector<GATriplet>& pixels, int& height, int& width);

/// write the resulting pixels (kln points, gray levels) into an image
void writeSceneInImage(std::string imagePath, const std::vector<GATriplet>& pixels, const int width,
                       const int height);




/// create a grid of Z2 (with only integer coordinates)
void createZ2Grid(Z2Grid& pts, const int width, const int height);

/// create a grid of Z3 (with only integer coordinates)
void createZ3Grid(Z3Grid& pts, const int width, const int length, const int height);



#endif //GADIGITALTRANSFO_SCENE_H
