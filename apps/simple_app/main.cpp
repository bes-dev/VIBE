#include <iostream>
#include "vibe.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv) {
    if(argc < 2)
    {
        return 1;
    }
    std::string filename = std::string(argv[1]);
    cv::VideoCapture cap(filename);

    int channels = 3;
    vibe::VIBE vibe_(channels, 20, 1, 17, 2, 16);
    cv::Mat frame;
    cap>>frame;
    if(channels == 1)
    {
        cv::cvtColor(frame, frame, CV_BGR2GRAY);
    }
    else
    {
        cv::cvtColor(frame, frame, CV_BGR2HSV);
    }
    vibe_.init(frame);

    cv::Mat gray = frame.clone();
    while ( !frame.empty() )
    {
        vibe_.update(gray);
        cv::Mat foreground;
        frame.copyTo(foreground, vibe_.getMask());
        cv::imshow("frame", frame);
        cv::imshow("foreground", foreground);
        cap >> frame;
        if(channels == 1)
        {
            cv::cvtColor(frame, gray, CV_BGR2GRAY);
        }
        else
        {
            cv::cvtColor(frame, gray, CV_BGR2HSV);
        }


        char key = cv::waitKey(10);
        if (key == 27)
        {
            break;
        }
    }
    return 0;
}
