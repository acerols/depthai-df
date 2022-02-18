#include <opencv2/opencv.hpp>
#include <depthai/depthai.hpp>

using Resolution = dai::MonoCameraProperties::SensorResolution;

class MonoCam
{
public:
    MonoCam(double fps=30.0, Resolution resolution=Resolution::THE_720_P);
    ~MonoCam();
    cv::Mat getLeftImage();
    cv::Mat getRightImage();
    bool tryGetLeftImgFrame();
    bool tryGetRightImgFrame();


private:
    double fps_;
    Resolution resolution_;

    std::shared_ptr<dai::ImgFrame> right_data_;
    std::shared_ptr<dai::ImgFrame> left_data_;
    std::shared_ptr<dai::DataOutputQueue> left_queue_;
    std::shared_ptr<dai::DataOutputQueue> right_queue_;
    std::shared_ptr<dai::Pipeline> pipeline_;
    std::shared_ptr<dai::node::MonoCamera> mono_left_;
    std::shared_ptr<dai::node::MonoCamera> mono_right_;
    std::shared_ptr<dai::node::XLinkOut> xout_left_;
    std::shared_ptr<dai::node::XLinkOut> xout_right_;
    std::shared_ptr<dai::node::IMU> imu_;
    std::shared_ptr<dai::Device> device_;

};