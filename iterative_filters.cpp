#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

void gaussianBLur(const cv::Mat& src,int kernelSize,cv::Mat& dst, double sigma){
    cv::GaussianBlur(src,dst,cv::Size(kernelSize,kernelSize),sigma);
}

void medianFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize){
    cv::medianBlur(src,dst,kernelSize);
}
void sobelFilter(const cv::Mat& src,cv::Mat& dst,int ddepth,int dx,int dy, int kernelSize){
    cv::Sobel(src,dst,ddepth,dx,dy,kernelSize);
} 

int main(){
    cv::Mat src = cv::imread("input.jpg",cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr<<"Error opening message; the file is empty"<<std::endl;
        return -1;
    }
    cv::Mat src2 = src; //Copy original image
    cv::Mat src3 = src;

    int iterations = 10000;

    //Gaussian time
    int kernelSize = 3;
    double sigma = 1.0;
    cv::Mat dst;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<=iterations;i++){
        gaussianBLur(src,kernelSize,dst,sigma);
    } //todo
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> gaussianBLurDuration = end - start;
    std::cout <<"Gauusian filter time: "<< gaussianBLurDuration.count()/10<<" ms."<<std::endl;
    //Median filter time
    start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<=iterations;i++){
        medianFilter(src2,dst,kernelSize);
    }
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> medianFilterDuration = end - start;
    std::cout <<"Median  filter time: "<< medianFilterDuration.count()/10<<" ms."<<std::endl;

    //SobelFilter time
    start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<=iterations;i++){
        sobelFilter(src3,dst,CV_16S,1,0,kernelSize); //todo
    }
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> sobelFilterDuration = end - start;
    std::cout <<"Sobel  filter time: "<< sobelFilterDuration.count()/10<<" ms"<<std::endl;


}