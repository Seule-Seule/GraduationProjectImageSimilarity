#include "imagealgorithm.hpp"

#include <QDebug>

ImageAlgorithm::ImageAlgorithm(QObject *parent) :
    QObject(parent)
{
}

// 计算图像直方图
void CompImageHist(const Mat &src, Mat &b_hist, Mat &g_hist, Mat &r_hist)
{
    // 分割成3个单通道图像(bgr)
    std::vector<Mat> rgb_planes;
    split(src, rgb_planes);

    // 设定bin数目及取值范围
    int histSize = 255;
    float range[] = { 0, 255 };
    const float* histRange = { range };

    // 计算直方图
    bool uniform = true;
    bool accumulate = false;
    calcHist(&rgb_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgb_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // 直方图归一化>>范围为[0, 1]
    normalize(r_hist, r_hist, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
    normalize(g_hist, g_hist, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
    normalize(b_hist, b_hist, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
}

// 计算图像直方图 只计算 HS 通道， 不计算 v 通道
void CompImageHistHSV(const Mat &src, Mat &h_hist, Mat &s_hist)
{
    // 分割成3个单通道图像(HSV)
    std::vector<Mat> HSV_planes;
    split(src, HSV_planes);

    // 设定bin数目及取值范围
    int histSize = 255;
    float range[] = { 0, 255 };
    const float* histRange = { range };

    // 计算直方图
    bool uniform = true;
    bool accumulate = false;
    calcHist(&HSV_planes[0], 1, 0, Mat(), h_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&HSV_planes[1], 1, 0, Mat(), s_hist, 1, &histSize, &histRange, uniform, accumulate);

    // 直方图归一化>>范围为[0, 1]
    normalize(h_hist, h_hist, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
    normalize(s_hist, s_hist, 0, 1, NORM_MINMAX, -1/*, Mat()*/);
}

void ImageAlgorithm::histogramImagesSimilarity(const Mat &leftImage,const Mat &rightImage)
{
    if (leftImage.empty() || rightImage.empty()){
        return;
    }
    DetectShowMessage(("Histogram Images Similarity: "));
    statusBurShowMessage(tr("Histogram images similarity begin."), 3000);
    Mat hist0[3], hist1[3];

    // 计算图像直方图
    CompImageHist(leftImage, hist0[0], hist0[1], hist0[2]);
    CompImageHist(rightImage, hist1[0], hist1[1], hist1[2]);

    double sum[4] = { 0.0 };
    double results[3][4] = { 0.0 };
    QString channelName[] = {  "Blue " ,  "Green " ,  "Red "  };

    // 比较直方图
    for (int i = 0; i < 3; i++)
    {
        // 相关: CV_COMP_CORREL,卡方: CV_COMP_CHISQR,相交: CV_COMP_INTERSECT,巴氏: CV_COMP_BHATTACHARYYA
        // https://docs.opencv.org/4.5.1/d8/dc8/tutorial_histogram_comparison.html
        // 相关: CV_COMP_CORREL,卡方: CV_COMP_CHISQR,相交: CV_COMP_INTERSECT,巴氏: CV_COMP_BHATTACHARYYA
        //相关性比较     (method=cv.HISTCMP_CORREL) 值越大，相关度越高，最大值为1，最小值为0
        //卡方比较      (method=cv.HISTCMP_CHISQR 值越小，相关度越高，最大值无上界，最小值0
        //相交比较      (method=CV_COMP_INTERSECT)值越大，相关度越高，最大值为9.455319，最小值为0  ?? 最大值不是9.4
        //巴氏距离比较   (method=cv.HISTCMP_BHATTACHARYYA) 值越小，相关度越高，最大值为1，最小值为0
        results[i][0] = compareHist(hist0[i], hist1[i], CV_COMP_CORREL);
        results[i][1] = compareHist(hist0[i], hist1[i], CV_COMP_BHATTACHARYYA);

        // 计算相似度并归一化到[0, 1]  1为100%相似  0为0%相似
        results[i][0] = fabs(results[i][0]);
        results[i][1] = 1 - results[i][1];

        sum[0] += results[i][0];
        sum[1] += results[i][1];

        QString messageCorrel(QString("  ->Channels ") + channelName[i] + QString("Correl Similarity: ") + QString::number(results[i][0]*100)  + QString("%."));
        QString messageBhattacharyya(QString("  ->Channels ") + channelName[i] + QString("Bhattacharyya Similarity: ") + QString::number(results[i][1]*100)  + QString("%."));
        DetectShowMessage(messageCorrel);
        DetectShowMessage(messageBhattacharyya);
    }

    QString messageCorrelResult(QString("  ->Average ") + QString("Correl Similarity: ") + QString::number(sum[0]/3*100)  + QString("%."));
    QString messageBhattacharyyaResult(QString("  ->Average ") + QString("Bhattacharyya Similarity: ") + QString::number(sum[1]/3*100)  + QString("%."));
    DetectShowMessage(messageCorrelResult);
    DetectShowMessage(messageBhattacharyyaResult);

    statusBurShowMessage(tr("Histogram images similarity complete."), 3000);


    // TODO: HSV 空间每次点击结果不一样？？ 很迷
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

void ImageAlgorithm::aptiveHistogramEqualization(Mat &leftImage, Mat &rightImage)
{

}

void ImageAlgorithm::scaleInvariantFeatureTransform(Mat &leftImage, Mat &rightImage)
{

}

void ImageAlgorithm::histogramEequalization(const Mat &src, imageColorSpace colorSpace)
{
    if (src.empty()){
        return;
    }
    Mat dst, gray;
    namedWindow(tr("HistogramEequalization").toStdString(), WINDOW_AUTOSIZE);

    // 单通道
    if (src.channels() == 3 && colorSpace == ImageAlgorithm::GRAY){
        cvtColor(src, gray, CV_RGB2GRAY);
        equalizeHist(gray, dst);
        imshow(tr("HistogramEequalization").toStdString(), dst);
    }

    // 多通道 采用通道拆分 分别均衡化 合并通道 完成均衡化
    if(src.channels() == 3 && colorSpace == ImageAlgorithm::RGB){
        Mat  dstBGR;
        Mat  srcB, srcG, srcR;
        std::vector<Mat> pSrcBGR;
        std::vector<Mat> pDstBGR;

        split(src, pSrcBGR);
        medianBlur(src, src, 5);

        equalizeHist(pSrcBGR[0], srcB);
        equalizeHist(pSrcBGR[1], srcG);
        equalizeHist(pSrcBGR[2], srcR);

        pSrcBGR[0]  = srcB;
        pSrcBGR[1]  = srcG;
        pSrcBGR[2]  = srcR;

        merge(pSrcBGR, dstBGR);

        imshow(tr("HistogramEequalization").toStdString(), dstBGR);
    }

    // YUV 直方图均衡化
    if(src.channels() == 3 && colorSpace == ImageAlgorithm::YUV){
        Mat srcYUV;
        std::vector<Mat> pSrcYUV;
        Mat srcY, dstYUV;

        cvtColor(src, srcYUV, CV_RGB2YCrCb);
        split(srcYUV, pSrcYUV);
        equalizeHist(pSrcYUV[0], srcY);

        pSrcYUV[0]  = srcY;
        merge(pSrcYUV, dstYUV);
        cvtColor(dstYUV, dstYUV, CV_YCrCb2BGR);

        imshow(tr("HistogramEequalization").toStdString(), dstYUV);
    }
}

// 直方图构建
void ImageAlgorithm::histogramBuild(const Mat &src)
{
    if (src.empty()){
        return;
    }

    namedWindow(tr("histogram").toStdString(), WINDOW_AUTOSIZE);
    Mat histImage;

    if (src.channels() == 3){
        //分割成三通道图像
        std::vector<Mat> channels;
        split(src, channels);

        //设定bin数目
        int histBinNum = 255;

        //设定取值范围
        float range[] = {0, 255};
        const float* histRange = {range};

        bool uniform = true;
        bool accumulate = false;

        //声明三个通道的hist数组
        Mat bHist, gHist, rHist;

        calcHist(&channels[0], 1, 0, Mat(), bHist, 1, &histBinNum, &histRange, uniform, accumulate);
        calcHist(&channels[1], 1, 0, Mat(), gHist, 1, &histBinNum, &histRange, uniform, accumulate);
        calcHist(&channels[2], 1, 0, Mat(), rHist, 1, &histBinNum, &histRange, uniform, accumulate);

        //创建直方图窗口  留5像素边框
        //int hist_w = src.cols;
        //int hist_h = src.rows;
        int hist_w = 400;
        int hist_h = 300;
        int bin_w = cvRound((double)(hist_w-10)/histBinNum);

        histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

        //将直方图归一化到范围[0, histImage.rows]
        normalize(bHist, bHist, 5, (hist_h- 5), NORM_MINMAX, -1, Mat());
        normalize(gHist, gHist, 5, (hist_h- 5), NORM_MINMAX, -1, Mat());
        normalize(rHist, rHist, 5, (hist_h- 5), NORM_MINMAX, -1, Mat());

        //循环绘制直方图
        for(int i = 1; i < histBinNum; i++)
        {
            line(histImage, Point(5+bin_w*(i-1), hist_h - cvRound(rHist.at<float>(i-1))),
                Point(5+bin_w*(i), hist_h - cvRound(rHist.at<float>(i))), Scalar(0, 0, 255), 1, LINE_AA, 0);
            line(histImage, Point(5+bin_w*(i-1), hist_h - cvRound(gHist.at<float>(i-1))),
                Point(5+bin_w*(i), hist_h - cvRound(gHist.at<float>(i))), Scalar(0, 255, 0), 1, LINE_AA, 0);
            line(histImage, Point(5+bin_w*(i-1), hist_h - cvRound(bHist.at<float>(i-1))),
                Point(5+bin_w*(i), hist_h - cvRound(bHist.at<float>(i))), Scalar(255, 0, 0), 1, LINE_AA, 0);
        }
    }

    if (src.channels() == 1){
        //设定bin数目
        int histBinNum = 255;

        //设定取值范围
        float range[] = {0, 255};
        const float* histRange = {range};

        bool uniform = true;
        bool accumulate = false;

        //声明hist数组
        Mat hist;

        calcHist(&src, 1, 0, Mat(), hist, 1, &histBinNum, &histRange, uniform, accumulate);

        //创建直方图窗口  留5像素边框
        //int hist_w = src.cols;
        //int hist_h = src.rows;
        int hist_w = 400;
        int hist_h = 300;
        int bin_w = cvRound((double)(hist_w-10)/histBinNum);

        histImage = Mat(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

        //将直方图归一化到范围[0, histImage.rows]
        normalize(hist, hist, 5, (hist_h- 5), NORM_MINMAX, -1, Mat());

        //循环绘制直方图
        for(int i = 1; i < histBinNum; i++)
        {
            line(histImage, Point(5+bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1))),
                Point(5+bin_w*(i), hist_h - cvRound(hist.at<float>(i))), Scalar(255, 255, 255), 1, LINE_AA, 0);
        }
    }

    imshow(tr("histogram").toStdString(), histImage);
}

void ImageAlgorithm::debugShowMessage(QString message)
{
    emit(sendDebugMessageSig(message));
}

void ImageAlgorithm::DetectShowMessage(QString message)
{
    emit(sendDetectMessageSig(message));
}

void ImageAlgorithm::statusBurShowMessage(QString message, int timeout)
{
    debugShowMessage(message);

    emit(sendStatusBarMessageSig(message, 3000));
}


