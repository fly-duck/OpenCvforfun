#pragma once 


#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>


namespace CV_Processor
{

void Sizeofthemat(const cv::Mat & picture) 
{

    std::cout << "picture.dims = " << picture.dims << "\tpicture.size = [";
    for(int i = 0; i < picture.dims; ++i)
    {
    if(i) std::cout << " X ";
    std::cout << picture.size[i];
    }
    std::cout << "] \t picture.channels = " << picture.channels() << "\n";
}


// void Repalcing(cv::Mat& )


// // create temporary image that will hold the mask
// Mat mask_image( your_image.size(), CV_8U, Scalar(0));
// // draw your contour in mask
// drawContours(mask_image, contours, ind, Scalar(255), CV_FILLED);
// // copy only non-zero pixels from your image to original image
// your_image.copyTo(original_image, mask_image);

}