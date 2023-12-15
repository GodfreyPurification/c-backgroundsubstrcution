#include <opencv2/opencv.hpp>

// Set global width and height values
int globalWidth = 640;
int globalHeight = 480;

int main() {
    // Open a video capture object
    cv::VideoCapture cap("E:\\c++\\parkingmanagement\\video\\carsvid2.mp4");

    // Check if the video is opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the video file." << std::endl;
        return -1;
    }

    // Get the frames per second (fps) of the video
    double fps = cap.get(cv::CAP_PROP_FPS);

    // Create a VideoWriter object to save the resized video
    cv::VideoWriter outputVideo("path/to/output/video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(globalWidth, globalHeight));

    // Loop through each frame of the video
    while (true) {
        cv::Mat frame;

        // Read the next frame from the video
        cap >> frame;

        // Break the loop if the video is finished
        if (frame.empty()) {
            break;
        }

        // Resize the frame to the globally set width and height
        cv::resize(frame, frame, cv::Size(globalWidth, globalHeight));

        // Display or process the resized frame as needed

        // Write the resized frame to the output video
        outputVideo << frame;

        // You can also perform other operations on the resized frame here

        // Display the resized frame
        cv::imshow("Resized Frame", frame);

        // Break the loop if the 'Esc' key is pressed
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // Release the VideoCapture and VideoWriter objects
    cap.release();
    outputVideo.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
