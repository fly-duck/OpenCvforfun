// PlayVideoFileCpp.sln
// main.cpp

#include "../include/CV.hpp"
// #include<conio.h>           // it may be necessary to change or remove this line if not using Windows

using Fps=double;
// using namespace cv;
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int, char**) {

    cv::VideoCapture capVideo;

    cv::Mat imgFrame;


    cv::Mat previous_selfie=cv::imread("../../res/Dog_sun.png");

    cv::Mat selfie;
    cv::resize(previous_selfie,selfie,cv::Size(previous_selfie.cols/4,previous_selfie.rows/4));    
    CV_Processor::Sizeofthemat(previous_selfie);
    CV_Processor::Sizeofthemat(selfie);


    // cv::resize
    capVideo.open("../../res/768x576.avi");
//     cv::putText(selfie,
// "This is a dog.",
// cv::Point(40,40),
// cv::FONT_HERSHEY_PLAIN,
// 2.0,
// 255,
// 2);
    

    

    if (!capVideo.isOpened()) {                                                 // if unable to open video file
        std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
        // _getch();                    // it may be necessary to change or remove this line if not using Windows
        return(0);                                                              // and exit program
    }
    Fps fps=capVideo.get(CV_CAP_PROP_FPS);
    std::cout<< "Frame per seconds :"<< fps << "\n";

    // capVideo.namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    // assert(capVideo.get(CV_CAP_PROP_FRAME_COUNT)==2);
    if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
        std::cout << "\nerror: video file must have at least one frame";
        // _getch();
        return(0);
    }

    capVideo.read(imgFrame);
    CV_Processor::Sizeofthemat(imgFrame);
    // cv::resize(imgFrame, selfie, cv::Size(), 0.05, 0.05);
   
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    std::vector<cv::Rect> found,filter;
    cvtColor(imgFrame, imgFrame, CV_RGB2GRAY);

    char chCheckForEscKey = 0;

    while (capVideo.isOpened() && chCheckForEscKey != 27) {


        cv::Mat image;
        hog.detectMultiScale(imgFrame,found,0,cv::Size(8,8),cv::Size(128,128),1.05,5);
        // cv::imshow("Dog_sun",selfie);
        

        size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            cv::Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                filter.push_back(r);
        }
        for ( i=0; i<filter.size(); i++)
        {
            cv::Rect r = filter[i];
            // std::cout<<r;
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.06);
            r.height = cvRound(r.height*0.9);
            cv::Mat imageROI(imgFrame,cv::Rect(r.x,r.y,selfie.cols,selfie.rows));
            selfie.copyTo(imageROI);
            cv::rectangle(imgFrame, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
            // cv::Mat truncated =selfie(cv::Rect(0,0,10,10)); 
            // truncated.copyTo(imgFrame(cv::Rect(0,0,10,10)));
        }
        if(!capVideo.read(image))
        {
            std::cout<<"can not read video into a matrix" <<"\n";
        }
        // std::vector<cv::Rect> found;
        cv::imshow("imgFrame", imgFrame);

                // now we prepare for the next iteration

        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {       // if there is at least one more frame
            capVideo.read(imgFrame);                            // read it
        }
        else {                                                  // else
            std::cout << "end of video\n";                      // show end of video message
            break;                                              // and jump out of while loop
        }

        chCheckForEscKey = cv::waitKey(1);      // get key press in case user pressed esc

    }

    if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
        cv::waitKey(0);                         // hold the windows open to allow the "end of video" message to show
    }
        // note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

    return(0);
}








