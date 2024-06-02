#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <vector>

void gaussianBLur(const cv::Mat& src, int kernelSize, cv::Mat& dst, double sigma) {
    cv::GaussianBlur(src, dst, cv::Size(kernelSize, kernelSize), sigma);
}

void medianFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize) {
    cv::medianBlur(src, dst, kernelSize);
}

void sobelFilter(const cv::Mat& src, cv::Mat& dst, int ddepth, int dx, int dy, int kernelSize) {
    cv::Sobel(src, dst, ddepth, dx, dy, kernelSize);
}

int main() {
    std::vector<std::string> imageFiles = {"input1.jpg", "input2.jpg", "input3.jpg", "input4.jpg", "input5.jpg"};
    int iterations = 1000;
    int kernelSize = 3;
    double sigma = 1.0;

    for (const std::string& fileName : imageFiles) {
        cv::Mat src = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
        if (src.empty()) {
            std::cerr << "Error opening image: " << fileName << std::endl;
            continue;
        }
        cv::Mat dst;

        // Gaussian filter time
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            gaussianBLur(src, kernelSize, dst, sigma);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> gaussianBLurDuration = end - start;
        std::cout << "Gaussian filter time for " << fileName << ": " << (gaussianBLurDuration.count() / iterations * 1000) << " ms." << std::endl;

        // Median filter time
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            medianFilter(src, dst, kernelSize);
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> medianFilterDuration = end - start;
        std::cout << "Median filter time for " << fileName << ": " << (medianFilterDuration.count() / iterations * 1000) << " ms." << std::endl;

        // Sobel filter time
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            sobelFilter(src, dst, CV_16S, 1, 0, kernelSize);
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sobelFilterDuration = end - start;
        std::cout << "Sobel filter time for " << fileName << ": " << (sobelFilterDuration.count() / iterations * 1000) << " ms." << std::endl;
    }

    return 0;
}
