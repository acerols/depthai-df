#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QAction>
#include <QStyle>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QTimer>

#include <opencv2/opencv.hpp>

class MainWindow : public QMainWindow
{
public:
    MainWindow(std::string title="stream viewer for depthai");
    ~MainWindow();
    void initUI();
    void openFileDialog();
    void recVideo();
    void moviePlay();
    void movieStop();
    void showNextFrame();
    void setImage(const cv::Mat &image);
    void paintEvent(QPaintEvent *event);
    void Update();

    QImage Cv2QImage(const cv::Mat& mat);

private:
    std::string title;
    int left;
    int top;
    int width;
    int height;

    int frame_pos;
    int fps;
    QImage image;
    QLabel *label;
    bool moviePlayFlag;

};