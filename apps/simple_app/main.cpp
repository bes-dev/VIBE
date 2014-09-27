#include <iostream>
#include "vibe.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
    cv::VideoCapture cap("/home/sergei/Downloads/pedestrians.mp4");

    vibe::VIBE vibe_;
    cv::Mat frame;
    cap>>frame;
    cv::cvtColor(frame, frame, CV_BGR2GRAY);
    vibe_.init(frame);

    cap >> frame;

    while ( !frame.empty() )
    {
        cap >> frame;
        cv::Mat gray;
        cv::cvtColor(frame, gray, CV_BGR2GRAY);
        vibe_.update(gray);
        cv::Mat foreground;
        frame.copyTo(foreground, vibe_.getMask());
        cv::imshow("mask", vibe_.getMask());
        cv::imshow("foreground", foreground);
        char key = cv::waitKey(10);
        if (key == 27)
        {
            break;
        }
    }
    return 0;
}
