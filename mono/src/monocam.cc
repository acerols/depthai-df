#include <opencv2/opencv.hpp>
#include <depthai/depthai.hpp>
#include "../include/monocam.hpp"

MonoCam::MonoCam(double fps, Resolution resolution)
:fps_(fps),  resolution_(resolution)
{
    pipeline_ = std::make_shared<dai::Pipeline>();
    mono_left_ = pipeline_->create<dai::node::MonoCamera>();
    mono_right_ = pipeline_->create<dai::node::MonoCamera>();
    xout_left_ = pipeline_->create<dai::node::XLinkOut>();
    xout_right_ = pipeline_->create<dai::node::XLinkOut>();

    xout_left_->setStreamName("left");
    xout_right_->setStreamName("right");
    mono_left_->setBoardSocket(dai::CameraBoardSocket::LEFT);
    mono_left_->setResolution(resolution_);
    mono_right_->setBoardSocket(dai::CameraBoardSocket::RIGHT);
    mono_right_->setResolution(resolution_);

    mono_left_->setFps(fps_);
    mono_right_->setFps(fps_);

    mono_left_->out.link(xout_left_->input);
    mono_right_->out.link(xout_right_->input);

    device_ = std::make_shared<dai::Device>(*pipeline_);

    left_queue_ = device_->getOutputQueue("left", 1024, false);
    right_queue_ = device_->getOutputQueue("right", 1024, false);

}


MonoCam::~MonoCam()
{

}

// try get left image frame
bool MonoCam::tryGetLeftImgFrame()
{
    left_data_ = left_queue_->tryGet<dai::ImgFrame>();
    if(left_data_)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//try get right image frame
bool MonoCam::tryGetRightImgFrame()
{
    right_data_ = right_queue_->tryGet<dai::ImgFrame>();
    if(right_data_)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// get left image frame
cv::Mat MonoCam::getLeftImage()
{
    return left_data_->getCvFrame();
}

// get right image frame
cv::Mat MonoCam::getRightImage()
{
    cv::Mat right_img = right_data_->getCvFrame();
    return right_img;
}



