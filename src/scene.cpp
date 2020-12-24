

#include "../include/scene.h"


void loadSceneFromImage(std::string imagePath, std::vector<GATriplet>& pixels, int& height, int& width){
//     cv::Mat imageInt = cv::imread("../img/ellipse10-6.pgm", cv::IMREAD_UNCHANGED);

     cv::Mat imageInt = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

     const int increaseAreaOfInterest = imageInt.cols/2; // before 10
     cv::Mat image = cv::Mat::ones(increaseAreaOfInterest, imageInt.cols, CV_8U);
     image.push_back(imageInt);
     cv::Mat rowEnd = cv::Mat::ones(increaseAreaOfInterest, image.cols, CV_8U);
     image.push_back(rowEnd);

     // let us convert pixel into the triplet kln points and gray level
     // we center
    for(int i=0; i<image.rows; i++)
        for(int j=0; j<image.cols; j++){
            pixels.at<uchar>(i,j) = 0;
            GATriplet currentPix = {kln::point(i-((int)input.rows/2),j-((int)input.cols/2),0.0),input.at<uchar>(i,j)};//
            pixels.push_back(currentPix);
            }
        }


}


void writeSceneInImage(std::string imagePath, const std::vector<GATriplet> pixels, cv::Mat& output, const int width,
                       const int height){
//     cv::Mat imageInt = cv::imread("../img/ellipse10-6.pgm", cv::IMREAD_UNCHANGED);

    cv::Mat imageInt = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

    for(unsigned int i=0;i<pixels.size();++i){
        GATriplet currPixel = pixels[i];
        output.at<uchar>(currPixel.klnPt.x()+((int)width/2),currPixel.klnPt.y()+((int)height/2)) = currPixel.val;
    }


}