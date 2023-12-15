// https://docs.opencv.org/4.x/d1/dc5/tutorial_background_subtraction.html
#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui/highgui.hpp>

int globalWidth = 640;
int globalHeight = 480;
int iterations = 0;
cv::Mat frame, fgMask,fgMaskThresh,framesize,fgMaskErod,hstacked,hstackedImage1, fgMaskdilate,hstackedImage,foregroundPart,frameCopy2;
int main() {
    // Open a video capture object
    cv::VideoCapture cap("E:\\c++\\parkingmanagement\\video\\carsvid.mp4");

    // Check if the video is opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the video file." << std::endl;
        return -1;
    }

    // Get the frames per second (fps) of the video
    double fps = cap.get(cv::CAP_PROP_FPS);

    // Create a VideoWriter object to save the resized video
    cv::VideoWriter outputVideo("path/to/output/video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(globalWidth, globalHeight));

    // Create a background subtractor using MOG2 method
    cv::Ptr<cv::BackgroundSubtractorMOG2> bgSubtractor = cv::createBackgroundSubtractorMOG2();
       // Set specific parameters
    bgSubtractor->setHistory(2);
    bgSubtractor->setVarThreshold(16.0);
    bgSubtractor->setDetectShadows(true);
    while (cap.read(frame)) {
        if (frame.empty()) {
            break;
        }
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT , cv::Size(5, 5));
        
        // cv::resize(frame, frame, cv::Size(desiredWidth, desiredHeight));
        // std::cout << "Size of framesize: " << frame.size() << std::endl;
        // std::cout << "Channel of framesize: " << frame.channels() << std::endl;
        // std::cout << "data of framesize: " << frame.type() << std::endl;
        // Apply the background subtractor to obtain a foreground mask
        bgSubtractor->apply(frame, fgMask);
        // cv::GaussianBlur(fgMask, fgMask, cv::Size(5, 5), 1.5);
        // std::cout << "Size of framesize: " << fgMask.size() << std::endl;
        // std::cout << "channel of framesize: " << fgMask.channels() << std::endl;
        // std::cout << "data of framesize: " << fgMask.type() << std::endl;
        cv::threshold(fgMask,fgMaskThresh,250,255,cv::THRESH_BINARY);
        cv::erode(fgMaskThresh,fgMaskErod,element);
        // ,cv::Point(-1,-1),1);
            // cv::erode(inputImage, erodedImage, element);

        cv::erode(fgMaskErod,fgMaskdilate,element);
        // ,cv::Point(-1,-1),2);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours (fgMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::Mat frameCopy = frame.clone();
        // cv::drawContours(frame,contours,-1,(0,0,255),1) ;
        std::vector<std::vector<cv::Point>> filtered_contours;
        for (size_t i = 0; i < contours.size(); i++)
          {
        // Calculate the area of the contour
            double area = cv::contourArea(contours[i]);
            // <<std::endl;
            // std::cout << "Contour " << i + 1 << " Area: " << area << std::endl;
            

             // Check if the area is greater than 400
             if (area > 2000)
            // && area < 2500)
            {
                // Add the contour to the filtered vector
                filtered_contours.push_back(contours[i]);
            }
    }
    // Draw the bounding rectangles for the filtered contours
        for (size_t i = 0; i < filtered_contours.size (); i++)
    {   
        
        // Find the bounding rectangle for the contour
        cv::Rect rect = boundingRect (filtered_contours [i]);

        cv::rectangle(frameCopy, rect, cv::Scalar(0,0,255),3,8,0);
        // cv::circle(frameCopy,cv::Point(cx+cy),2,cv::Scalar(255,0,255),-1);

        // cv::putText(frameCopy, "Car", rect, cv::FONT_HERSHEY_COMPLEX_SMALL, 2, (0, 0, 255), 2);
        // cv::putText(frameCopy,"Car", rect.tl().x, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
        cv::String text = "Car";
        cv::Point position(50, 100);  // Use cv::Point for the third argument
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        double fontScale = 1.0;
        cv::Scalar color(255, 255, 255);  // White color
        int thickness = 2;
        int lineType = cv::LINE_AA;
        cv::putText(frameCopy, text, rect.tl(), fontFace, fontScale, color, thickness, lineType);
        // cv::circle(frameCopy, cv::Point center, 3, cv::Scalar(0, 255, 255), 3);

     // cv::putText(image, text, position, fontFace, fontScale, color, thickness, lineType);
 

        // Draw the rectangle on the original image
        // cv::rectangle (frameCopy,rect, (255, 255, 255), 2);
        // Calculate center point
        
       // Draw a circle at the center point
        // cv::circle(frameCopy, circle, 3, cv::Scalar(0, 255, 255), 3);
    }
    // foregroundPart
        cv::cvtColor(fgMask,fgMask,cv::COLOR_GRAY2RGB);
        cv::bitwise_and(frame, fgMask,foregroundPart);
        
        // std::cout << "frame size: " << frame.size() <<"Type"<<frame.type()<<"channel"<<frame.channels()<<std::endl;
        // std::cout << "fgMask size: " << foregroundPart.size() <<"Type"<<foregroundPart.type()<<"channel"<<foregroundPart.channels()<<std::endl;
        // std::cout << "frameCopy2 size: " << frameCopy.size() << "Type"<<frameCopy.type()<<"channel"<<frameCopy.channels()<<std::endl;
        cv::hconcat(frame,foregroundPart,hstacked);
        cv::hconcat(hstacked, frameCopy, hstackedImage);
        

        cv::resize(hstackedImage,hstackedImage1,cv::Size(1300,300));
        cv::imshow("All Three Results", hstackedImage1);

    // Further processing or visualization can be done with fgMask

        // Display the original frame and the foreground mask
        // cv::imshow("Original Frame", frameCopy2);
        // cv::imshow("Foreground Mask", hstacked);
        // cv::imshow("Rectangle",frameCopy);

        // Break the loop if the user presses 'Esc'
         // Break the loop if the user presses 'Esc'
        if (cv::waitKey(30) == 27) {
        break;
        }
    }

    // Release the video capture object
    cap.release();

    // Close all windows
    cv::destroyAllWindows();

    return 0;
}
