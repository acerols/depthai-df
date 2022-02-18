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
    label = new QLabel(widget);
    layout->addWidget(label);
    QPushButton *recVideoButtion = new QPushButton("Record Video", widget);
    layout->addWidget(recVideoButtion);
    connect(recVideoButtion, SIGNAL(clicked()), this, SLOT(recVideo()));

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::Update);
    timer->start(1000/30);

}

MainWindow::~MainWindow()
{
}

void MainWindow::Update()
{
    if(!image.isNull())
    {
        std::cout << "update" << std::endl;
        QPixmap pixmap = QPixmap::fromImage(image);
        //pixmap = pixmap.scaled(QSize(30, 30));
        // print pixmap info
        std::cout << "pixmap.width() = " << pixmap.width() << std::endl;
        label->setPixmap(pixmap);
    }
}

void MainWindow::moviePlay()
{
    moviePlayFlag = true;
}

void MainWindow::movieStop()
{
    moviePlayFlag = false;
}

void MainWindow::recVideo()
{
    std::cout << "recVideo" << std::endl;
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
    /*
    // print debug info
    std::cout << "frame_pos: " << frame_pos << std::endl;
    
    std::cout << "image.size().width(): " << image.size().width() << std::endl;

    if(!image.isNull())
    {
        QPainter painter(this);
        std::cout << "show image" << std::endl;
        painter.drawImage(QPoint(0, 0), image);
        painter.end();
    }
    */    
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