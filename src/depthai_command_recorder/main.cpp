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

int main(int argc, char *argv[])
{
    using namespace std;

    dai::Pipeline pipeline;
    auto monoLeft = pipeline.create<dai::node::MonoCamera>();
    auto monoRight = pipeline.create<dai::node::MonoCamera>();
    auto xoutLeft = pipeline.create<dai::node::XLinkOut>();
    auto xoutRight = pipeline.create<dai::node::XLinkOut>();

    xoutLeft->setStreamName("left");
    xoutRight->setStreamName("right");

    monoLeft->setBoardSocket(dai::CameraBoardSocket::LEFT);
    monoLeft->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);
    monoRight->setBoardSocket(dai::CameraBoardSocket::RIGHT);
    monoRight->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);

    monoRight->out.link(xoutRight->input);
    monoLeft->out.link(xoutLeft->input);

    dai::Device device(pipeline);

    auto qleft = device.getOutputQueue("left", 4, false);
    auto qright = device.getOutputQueue("right", 4, false);

    int fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V');
    

    QApplication test(argc, argv);
    QMainWindow w;
    QImage qimage;
    QLabel label;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now(), end;

    // set qt layout
    QVBoxLayout layout;
    layout.addWidget(&label);
    
    // add button to layout
    QPushButton button("Start");
    layout.addWidget(&button);
    w.setLayout(&layout);

    vector<cv::Mat> images;

    while(true){
        auto inLeft = qleft->tryGet<dai::ImgFrame>();
        auto inRight = qright->tryGet<dai::ImgFrame>();

        cv::Mat image_list[2];
        

        if(inLeft && inRight){
            cv::Mat Left = inLeft->getCvFrame();
            cv::Mat Right = inRight->getCvFrame();
            image_list[0] = Left;
            image_list[1] = Right;
            cv::Mat image = Left.clone();
            cv::hconcat(image_list, 2, image);
            cv::cvtColor(image, image, cv::COLOR_GRAY2RGB);
            cv::imshow("image", image);
            images.push_back(image);

        }
        
        if(cv::waitKey(1) == 'q'){
            end = std::chrono::steady_clock::now();
            break;
        }
    }


    int fps = (int)(images.size() / (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0));
    std::cout << "FPS: " << fps << std::endl;

    //print time
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::cout << "Frame Count: " << images.size() << endl;

    cv::VideoWriter writer("output.mp4", fourcc, fps, cv::Size(images[0].cols, images[0].rows), true);
    for(int i = 0; i < images.size(); i++){
        writer << images[i];
    }

    writer.release();
    return 0;


}