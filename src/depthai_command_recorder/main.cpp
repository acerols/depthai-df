#include <iostream>
#include <time.h>
#include <depthai/depthai.hpp>
#include <opencv2/opencv.hpp>
#include <QApplication>
#include <QMainWindow>
#include <qt5/QtGui/QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

#include <monocam.hpp>
#include <gui.hpp>

int main(int argc, char *argv[])
{
    using namespace std;

    int left_frame_count = 0;
    int right_frame_count = 0;

    MonoCam monocam(30.0f, Resolution::THE_400_P);

    int fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V');

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now(), end;

    vector<cv::Mat> images;
    vector<cv::Mat> images_right;

    QApplication app(argc, argv);
    MainWindow main_window;

    //print start recording
    cout << "Recording started" << endl;

    while(true){
        if(monocam.tryGetLeftImgFrame()){
            cv::Mat img = monocam.getLeftImage();
            images.push_back(img);
            cv::imshow("left", img);
            left_frame_count++;
            cv::Mat imgRGB;
            cv::cvtColor(img, imgRGB, cv::COLOR_GRAY2BGR);
            main_window.setImage(imgRGB);
        }
        if(monocam.tryGetRightImgFrame()){
            cv::Mat img = monocam.getRightImage();
            images_right.push_back(img);
            right_frame_count++;
        }
    
        if(cv::waitKey(1) == 'q'){
            end = std::chrono::steady_clock::now();
            break;
        }
    }


    double fps = (double)(images.size() / (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0));
    std::cout << "FPS: " << fps << std::endl;

    //print time
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::cout << "Frame Count: " << images.size() << endl;

    //print left fps
    std::cout << "Left FPS: " << left_frame_count / (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0) << std::endl;
    //print right fps
    std::cout << "Right FPS: " << right_frame_count / (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0) << std::endl;

    cv::VideoWriter writer("output.mp4", fourcc, fps, cv::Size(images[0].cols*2, images[0].rows), true);

    for(auto left_image_itr = images.begin(), right_image_itr = images_right.begin(); left_image_itr != images.end() and right_image_itr != images_right.end(); left_image_itr++, right_image_itr++){
        cv::Mat image;
        cv::hconcat(*left_image_itr, *right_image_itr, image);
        cv::cvtColor(image, image, cv::COLOR_GRAY2RGB);
        writer.write(image);
    }

    writer.release();
    return 0;


}