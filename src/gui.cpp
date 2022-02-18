#include <gui.hpp>

MainWindow::MainWindow(std::string title)
:title(title), left(10), top(10), 
width(600), height(400), frame_pos(0), moviePlayFlag(false)
{
    initUI();
    show();
}

void MainWindow::initUI()
{
    this->setWindowTitle(QString::fromStdString(title));
    this->setGeometry(left, top, width, height);
    QWidget *widget = new QWidget(this);
    this->setCentralWidget(widget);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    QLabel *label = new QLabel(widget);
    layout->addWidget(label);
    QPushButton *openFileDialog = new QPushButton("openFileDialog", widget);
    layout->addWidget(openFileDialog);
    QPushButton *moviePlay = new QPushButton("moviePlay", widget);
    layout->addWidget(moviePlay);
    QPushButton *movieStop = new QPushButton("movieStop", widget);
    layout->addWidget(movieStop);
    QPushButton *showNextFrame = new QPushButton("showNextFrame", widget);
    layout->addWidget(showNextFrame);
    QObject::connect(openFileDialog, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    QObject::connect(moviePlay, SIGNAL(clicked()), this, SLOT(moviePlay()));
    QObject::connect(movieStop, SIGNAL(clicked()), this, SLOT(movieStop()));
    QObject::connect(showNextFrame, SIGNAL(clicked()), this, SLOT(showNextFrame()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::moviePlay()
{
    moviePlayFlag = true;
}

void MainWindow::movieStop()
{
    moviePlayFlag = false;
}

void MainWindow::showNextFrame()
{
    if(moviePlayFlag)
    {
        frame_pos++;
        if(frame_pos >= image.size().width())
        {
            frame_pos = 0;
        }
        this->update();
    }
}

void MainWindow::openFileDialog()
{

}

void MainWindow::setImage(const cv::Mat &image)
{
    this->image = Cv2QImage(image);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);
    // print debug info
    std::cout << "frame_pos: " << frame_pos << std::endl;
    
    std::cout << "image.size().width(): " << image.size().width() << std::endl;

    if(!image.isNull())
    {
        std::cout << "show image" << std::endl;
        painter.drawImage(QPoint(0, 0), image);
        painter.end();
    }
}

QImage MainWindow::Cv2QImage(const cv::Mat& mat)
{
    int channel = mat.channels();
    int widht = mat.cols;
    int height = mat.rows;

    cv::Mat cvImageRGB;
    cv::cvtColor(mat, cvImageRGB, cv::COLOR_BGR2RGB);
    image = QImage(cvImageRGB.data, widht, height, channel * widht, QImage::Format_RGB888).copy();
    return image;
}