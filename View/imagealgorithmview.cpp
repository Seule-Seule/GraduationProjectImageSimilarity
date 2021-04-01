#include "imagealgorithmview.hpp"

#include <QDebug>

ImageAlgorithmView::ImageAlgorithmView(QObject *parent) : QObject(parent)
{

}

void ImageAlgorithmView::DrawHist(String window_name, int width, int height, QVector<Mat> &hist_in)
{
    int histBinNum = 255;
    int bin_w = cvRound((double)(width-10)/histBinNum);
    int hist_size = hist_in.size();
    Mat hist_mage(height, width, CV_8UC3, Scalar(0, 0, 0));
    QVector<Scalar> color = {Scalar(255, 0, 0) /*b*/, Scalar(0, 255, 0) /*g*/, Scalar(0, 0, 255) /*r*/};

    // 映射到宽高空间
    for (int number= 0; number<hist_size; number++){
        normalize(hist_in[number], hist_in[number], 5, (height- 5), NORM_MINMAX, -1, Mat());
    }
    //循环绘制直方图
    for(int i = 1; i < histBinNum; i++)
    {
        for (int line_index = 0; line_index < hist_size; line_index++){
            line(hist_mage, Point(5+bin_w*(i-1), height - cvRound(hist_in[line_index].at<float>(i-1))),
                 Point(5+bin_w*(i), height - cvRound(hist_in[line_index].at<float>(i))),
                 color[line_index], 1, LINE_AA, 0);
            // 画竖线 填满直方图区域
//            line(hist_mage, Point(5+bin_w*(i-1), height - 5),
//                 Point(5+bin_w*(i-1), height - cvRound(hist_in[line_index].at<float>(i-1))),
//                 color[line_index], 1, LINE_AA, 0);
        }
    }
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, hist_mage);
    debugMessage(QString(window_name.c_str()) + QString(" draw ok !"));
}

void ImageAlgorithmView::CompImageHist(const Mat &src_in,WorkSpace ws, int id)
{
    if (src_in.empty()){
        debugMessage("CompImageHist src_in is empty !");
        return;
    }
    String position;
    if (id){
        position = String("Left ");
    }else{
        position = String("Right ");
    }
    Mat src;
    int histSize = 255;
    float range[] = { 0, 255 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    if (ws == WorkSpace::GRAY)
    {
        Mat dst;
        cvtColor(src_in, src, CV_RGB2GRAY);
        calcHist(&src, 1, 0, Mat(), dst, 1, &histSize, &histRange, uniform, accumulate);

        QVector<Mat> temp = {dst};
        DrawHist(position + String("Histogram in GRAY"), 400, 300, temp);
    }
    else if (ws == WorkSpace::RGB)
    {
        src = src_in;
        std::vector<Mat> channels(3);
        split(src, channels);

        //声明三个通道的hist数组
        Mat hist_b, hist_g, hist_r;

        calcHist(&channels[0], 1, 0, Mat(), hist_b, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&channels[1], 1, 0, Mat(), hist_g, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&channels[2], 1, 0, Mat(), hist_r, 1, &histSize, &histRange, uniform, accumulate);

        QVector<Mat> temp;
        temp.push_back(hist_b);
        temp.push_back(hist_g);
        temp.push_back(hist_r);
        DrawHist(position + String("Histogram in RGB"),400, 300, temp);
    }
    else if (ws == WorkSpace::HSV)
    {
        cvtColor(src_in, src, CV_RGB2HSV);
        std::vector<Mat> channels(3);
        split(src, channels);

        //声明H S通道的hist数组
        Mat hist_h, hist_s;
        calcHist(&channels[0], 1, 0, Mat(), hist_h, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&channels[1], 1, 0, Mat(), hist_s, 1, &histSize, &histRange, uniform, accumulate);

        QVector<Mat> temp_Draw;
        temp_Draw.push_back(hist_h);
        temp_Draw.push_back(hist_s);
        DrawHist(position + String("Histogram in HSV"),400, 300, temp_Draw);
    }
}

void ImageAlgorithmView::HistogramEqualization(const Mat &leftImage,const Mat &rightImage)
{
    if (leftImage.empty() || rightImage.empty()){
        debugMessage("histogramImagesSimilarity image not load !");
        return;
    }
    debugMessage("histogramImagesSimilarity begin !");

    Mat leftSrc, rightSrc;
    cvtColor(leftImage, leftSrc, CV_RGB2HSV);
    cvtColor(rightImage, rightSrc, CV_RGB2HSV);

    int h_bins = 50, s_bins = 60;
    int histsize[] = { h_bins,s_bins };
    float h_ranges[] = { 0,180 };
    float s_ranges[] = { 0,256 };
    const float *ranges[] = { h_ranges,s_ranges };
    int channels1[] = { 0,1 };

    // 计算直方图
    Mat histLeft, histRight;
    calcHist(&leftSrc, 1, channels1, Mat(), histLeft, 2, histsize, ranges, true, false);
    calcHist(&rightSrc, 1, channels1, Mat(), histRight, 2, histsize, ranges, true, false);

    double results = { 0.0 };

    // 全局归一化
    normalize(histLeft, histLeft, 0, 1, NORM_MINMAX, -1, Mat());

    // 计算相似性
    results = compareHist(histLeft, histRight, CV_COMP_CORREL);
    QString messageCorrel = QString(QString("Histogram Images Similarity::") + QString::number(results));
    detectMessage(messageCorrel);
    debugMessage("histogramImagesSimilarity end !");
}

void ImageAlgorithmView::AptiveHistogramEqualization(const Mat &leftImage,const Mat &rightImage)
{

}

void ImageAlgorithmView::update()
{

}

void ImageAlgorithmView::debugMessage(QString message)
{
    message = QString("ImageAlgorithmView") + QString("::") + message;
    emit(debugMessageSig(message));
}

void ImageAlgorithmView::detectMessage(QString message)
{
     emit(detectMessageSig(message));
}
