#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <omp.h>

void gaussianBlur(const cv::Mat& src, int kernelSize, cv::Mat& dst, double sigma){
    cv::GaussianBlur(src, dst, cv::Size(kernelSize, kernelSize), sigma);
}

void medianFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize){
    cv::medianBlur(src, dst, kernelSize);
}

void sobelFilter(const cv::Mat& src, cv::Mat& dst, int ddepth, int dx, int dy, int kernelSize){
    cv::Sobel(src, dst, ddepth, dx, dy, kernelSize);
}

int main(){
    cv::Mat src = cv::imread("input.jpg", cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr << "Error opening image; the file is empty" << std::endl;
        return -1;
    }
    cv::Mat src2 = src.clone(); // Copy original image
    cv::Mat src3 = src.clone();
    cv::Mat dst;

    int kernelSize = 3;
    double sigma = 1.0;
    int iterations = 10000; // Number of iterations for testing

    // Timing variables
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> gaussianBlurDuration(0), medianFilterDuration(0), sobelFilterDuration(0);

    // Loop for testing Gaussian filter
    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < iterations; ++i) {
        cv::Mat tmp;
        gaussianBlur(src, kernelSize, tmp, sigma);
    }
    end = std::chrono::high_resolution_clock::now();
    gaussianBlurDuration = end - start;

    // Loop for testing Median filter
    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < iterations; ++i) {
        cv::Mat tmp;
        medianFilter(src2, tmp, kernelSize);
    }
    end = std::chrono::high_resolution_clock::now();
    medianFilterDuration = end - start;

    // Loop for testing Sobel filter
    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < iterations; ++i) {
        cv::Mat tmp;
        sobelFilter(src3, tmp, CV_16S, 1, 0, kernelSize);
    }
    end = std::chrono::high_resolution_clock::now();
    sobelFilterDuration = end - start;

    // Calculate average durations
    gaussianBlurDuration /= iterations;
    medianFilterDuration /= iterations;
    sobelFilterDuration /= iterations;

    std::cout << "Average Gaussian filter time: " << gaussianBlurDuration.count() * 1000 << " ms." << std::endl;
    std::cout << "Average Median filter time: " << medianFilterDuration.count() * 1000 << " ms." << std::endl;
    std::cout << "Average Sobel filter time: " << sobelFilterDuration.count() * 1000 << " ms." << std::endl;

    return 0;
}
