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
}

void ImageAlgorithmView::CompImageHist(const Mat &src_in,WorkSpace ws,
                  Mat *hist_out,bool display_flag, bool normalize_flag)
{
    if (src_in.empty()){
        debugMessage("CompImageHist src_in is empty !");
        return;
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

        if (normalize_flag){
            normalize(dst, dst, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
        }
        if (hist_out != nullptr){
            hist_out[0] = dst;
        }
        if(display_flag){
            QVector<Mat> temp = {dst};
            DrawHist("Histogram in GRAY", 400, 300, temp);
        }

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

        if (normalize_flag){
            normalize(hist_b, hist_b, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
            normalize(hist_g, hist_g, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
            normalize(hist_r, hist_r, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
        }
        if (hist_out != nullptr){
            hist_out[0] = hist_b;
            hist_out[1] = hist_g;
            hist_out[2] = hist_r;
        }
        if(display_flag){
            QVector<Mat> temp;
            temp.push_back(hist_b);
            temp.push_back(hist_g);
            temp.push_back(hist_r);
            DrawHist("Histogram in RGB",400, 300, temp);
        }
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

        if (hist_out != nullptr){
            int h_bins = 50, s_bins = 60;
            int histsize[] = { h_bins,s_bins };
            float h_ranges[] = { 0,180 };
            float s_ranges[] = { 0,256 };
            const float *ranges[] = { h_ranges,s_ranges };
            int channels1[] = { 0,1 };

            Mat hist_src;
            calcHist(&src, 1, channels1, Mat(), hist_src, 2, histsize, ranges, true, false);
            normalize(hist_src, hist_src, 0, 1, NORM_MINMAX, -1, Mat());
            hist_out[0] = hist_src;
        }
        if(display_flag){
            QVector<Mat> temp_Draw;
            temp_Draw.push_back(hist_h);
            temp_Draw.push_back(hist_s);
            DrawHist("Histogram in HSV",400, 300, temp_Draw);
        }
    }
}

void ImageAlgorithmView::histogramImagesSimilarity(const Mat &leftImage,const Mat &rightImage, WorkSpace ws)
{
    if (leftImage.empty() || rightImage.empty()){
        debugMessage("histogramImagesSimilarity image not load !");
        return;
    }
    debugMessage("histogramImagesSimilarity begin !");
    Mat histLeft[3], histRight[3];

    // 计算图像直方图
    CompImageHist(leftImage, ws, histLeft, false, true);
    CompImageHist(rightImage, ws, histRight, false, true);

    double sum[4] = { 0.0 };
    double results = { 0.0 };
    QString channelName[] = {  "H " ,  "S " };

    results = compareHist(histLeft[0], histRight[0], CV_COMP_CORREL);
    QString messageCorrel = QString(QString("correl similarity::") + QString::number(results*100) + QString("%"));
    detectMessage(messageCorrel);

    // 比较直方图
//    for (int i = 0; i < 2; i++)
//    {
//        // 相关: CV_COMP_CORREL,卡方: CV_COMP_CHISQR,相交: CV_COMP_INTERSECT,巴氏: CV_COMP_BHATTACHARYYA
//        // https://docs.opencv.org/4.5.1/d8/dc8/tutorial_histogram_comparison.html
//        // 相关: CV_COMP_CORREL,卡方: CV_COMP_CHISQR,相交: CV_COMP_INTERSECT,巴氏: CV_COMP_BHATTACHARYYA
//        //相关性比较     (method=cv.HISTCMP_CORREL) 值越大，相关度越高，最大值为1，最小值为0
//        //卡方比较      (method=cv.HISTCMP_CHISQR 值越小，相关度越高，最大值无上界，最小值0
//        //相交比较      (method=CV_COMP_INTERSECT)值越大，相关度越高，最大值为9.455319，最小值为0  ?? 最大值不是9.4
//        //巴氏距离比较   (method=cv.HISTCMP_BHATTACHARYYA) 值越小，相关度越高，最大值为1，最小值为0

//        results[i][0] = compareHist(histLeft[i], histRight[i], CV_COMP_CORREL);
////        results[i][1] = compareHist(histLeft[i], histRight[i], CV_COMP_BHATTACHARYYA);

//        // 计算相似度并归一化到[0, 1]  1为100%相似  0为0%相似
//        results[i][0] = fabs(results[i][0]);
////        results[i][1] = 1 - results[i][1];

//        sum[0] += results[i][0];
////        sum[1] += results[i][1];

//        QString messageCorrel = QString(QString("Channel ") + channelName[i] + QString("correl similarity::") + QString::number(results[i][0]*100)  + QString("%"));

////        QString messageBhattacharyya = QString(QString("Channel ") + channelName[i] + QString("bhattacharyya similarity::") +  QString::number(results[i][1]*100)  + QString("%"));

//        detectMessage(messageCorrel);
////        detectMessage(messageBhattacharyya);
//    }

//    QString messageCorrelResult = QString(QString("Average ") + QString("correl similarity::") + QString::number(sum[0]/3*100)  + QString("%"));
////    QString messageBhattacharyyaResult = QString(QString("Average ") + QString("bhattacharyya similarity::") + QString::number(sum[1]/3*100)  + QString("%"));
//    detectMessage(messageCorrelResult);
////    detectMessage(messageBhattacharyyaResult);

    debugMessage("histogramImagesSimilarity end !");

    // TODO: HSV 空间每次计算结果不一样，好像是每次计算结果偏大？？ 很迷
    //    Mat hist0[2], hist1[2];
    //    cvtColor(leftImage, leftImage, CV_BGR2HSV);
    //    cvtColor(rightImage, rightImage, CV_BGR2HSV);
    //    // 计算图像直方图 HSV
    //    CompImageHistHSV(leftImage, hist0[0], hist0[1]);
    //    CompImageHistHSV(rightImage, hist1[0], hist1[1]);

    //    double sum[4] = { 0.0 };
    //    double results[4] = { 0.0 };
    //    char channelName[][4] = { { "H" }, { "S" } };

    //    // 比较直方图
    //    for (int i = 0; i < 2; i++)
    //    {
    //        // 相关: CV_COMP_CORREL,卡方: CV_COMP_CHISQR,相交: CV_COMP_INTERSECT,巴氏: CV_COMP_BHATTACHARYYA
    //        //相关性比较     (method=cv.HISTCMP_CORREL) 值越大，相关度越高，最大值为1，最小值为0
    //        //卡方比较      (method=cv.HISTCMP_CHISQR 值越小，相关度越高，最大值无上界，最小值0
    //        //相交比较      (method=CV_COMP_INTERSECT)值越大，相关度越高，最大值为9.455319，最小值为0
    //        //巴氏距离比较   (method=cv.HISTCMP_BHATTACHARYYA) 值越小，相关度越高，最大值为1，最小值为0
    //        results[0] = compareHist(hist0[i], hist1[i], CV_COMP_CORREL);
    //        results[1] = compareHist(hist0[i], hist1[i], CV_COMP_CHISQR);
    //        results[2] = compareHist(hist0[i], hist1[i], CV_COMP_INTERSECT);
    //        results[3] = compareHist(hist0[i], hist1[i], CV_COMP_BHATTACHARYYA);

    //        // TAPD  同一尺度 归一化到【0-1】 否则均值无意义

    //        sum[0] += results[0];
    //        sum[1] += results[1];
    //        sum[2] += results[2];
    //        sum[3] += results[3];
    //        qDebug() << channelName[i] << "-->CORREL:" << results[0] << "CHISQR:" <<  results[1] << "INTERSECT:" << results[2] << "BHATTACHARYYA" << results[3] ;
    //    }
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
