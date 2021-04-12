

#include "../include/scene.h"


void loadSceneFromImage(std::string imagePath, std::vector<GATriplet>& pixels, int& height, int& width){
//     cv::Mat imageInt = cv::imread("../img/ellipse10-6.pgm", cv::IMREAD_UNCHANGED);

     cv::Mat imageInt = cv::imread(imagePath, cv::IMREAD_UNCHANGED);


     const int increaseAreaOfInterest = imageInt.cols/2; // before 10

     // add rows above and bellow
     cv::Mat image = cv::Mat::ones(increaseAreaOfInterest, imageInt.cols, CV_8U);
     image.push_back(imageInt);
     cv::Mat rowEnd = cv::Mat::ones(increaseAreaOfInterest, image.cols, CV_8U);
     image.push_back(rowEnd);


    // add cols above and bellow
     cv::Mat colAdd = cv::Mat::ones(image.rows,increaseAreaOfInterest, CV_8U);
     cv::Mat imageResiz1;
     cv::hconcat(image,colAdd,imageResiz1);

     cv::Mat colAddBeg = cv::Mat::ones(imageResiz1.rows,increaseAreaOfInterest, CV_8U);
     cv::Mat imageResiz;
     cv::hconcat(colAddBeg,imageResiz1,imageResiz);



    height = imageResiz.rows;
    width =  imageResiz.cols;

     // let us convert pixel into the triplet kln points and gray level
     // we center
    for(int i=0; i<imageResiz.rows; i++)
        for(int j=0; j<imageResiz.cols; j++){
            GATriplet currentPix = {kln::point(j-((int)imageResiz.cols/2),i-((int)imageResiz.rows/2),0.0),imageResiz.at<uchar>(i,j)};
            pixels.push_back(currentPix);
        }
}


void writeSceneInImage(std::string imagePath, const std::vector<GATriplet>& pixels, const int width,
                       const int height){
//     cv::imwrite("../img/input.pgm",imageResiz)
std::cout << "resulting height =" << height << ", width = "<< width << std::endl;
    cv::Mat output = cv::Mat::zeros(width,height, CV_8U);;

    for(unsigned int i=0;i<pixels.size();++i){
        GATriplet currPixel = pixels[i];
        output.ptr<uchar>((int)currPixel.klnPt.y()+((int)height/2))[(int)currPixel.klnPt.x()+((int)width/2)] = currPixel.val;
    }

    cv::imwrite(imagePath,output);

}


void createZ2Grid(Z2Grid& pts, const int width, const int height){

    for(int y =0 ; y< height ; ++y){
        for(int x=0 ; x<width ; ++x){
            pts.push_back(kln::point((int)x-((int)width/2),(int)y-((int)height/2),0));
        }
    }

}


/// create a grid of Z3 (with only integer coordinates)
void createZ3Grid(Z3Grid& pts, const int width, const int length, const int height){
    for(int z =0 ; z< height ; ++z){
        for(int y=0 ; y<width ; ++y){
            for(int x=0 ; x<length ; ++x){
                pts.push_back(kln::point((int)x-((int)length/2),(int)y-((int)width/2),(int)z-((int)height/2)));
            }
        }
    }

}
