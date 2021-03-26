#include "imagealgorithmview.hpp"

ImageAlgorithmView::ImageAlgorithmView(QObject *parent) : QObject(parent)
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


void ImageAlgorithmView::histogramImagesSimilarity(const Mat &leftImage,const Mat &rightImage)
{
    if (leftImage.empty() || rightImage.empty()){
        return;
    }

    Mat histLeft[3], histRight[3];

    // 计算图像直方图
    CompImageHist(leftImage, histLeft[0], histLeft[1], histLeft[2]);
    CompImageHist(rightImage, histRight[0], histRight[1], histRight[2]);

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
        results[i][0] = compareHist(histLeft[i], histRight[i], CV_COMP_CORREL);
        results[i][1] = compareHist(histLeft[i], histRight[i], CV_COMP_BHATTACHARYYA);

        // 计算相似度并归一化到[0, 1]  1为100%相似  0为0%相似
        results[i][0] = fabs(results[i][0]);
        results[i][1] = 1 - results[i][1];

        sum[0] += results[i][0];
        sum[1] += results[i][1];

        QString messageCorrel = QString(QString("Channel ") + channelName[i] + QString("correl similarity: ") + QString::number(results[i][0]*100)  + QString("%"));

        QString messageBhattacharyya = QString(QString("Channel ") + channelName[i] + QString("bhattacharyya similarity: ") +  QString::number(results[i][1]*100)  + QString("%"));

        debugMessage(messageCorrel);
        debugMessage(messageBhattacharyya);
    }

    QString messageCorrelResult = QString(QString("Average ") + QString("correl similarity:") + QString::number(sum[0]/3*100)  + QString("%"));
    QString messageBhattacharyyaResult = QString(QString("Average ") + QString("bhattacharyya similarity:") + QString::number(sum[1]/3*100)  + QString("%"));
    debugMessage(messageCorrelResult);
    debugMessage(messageBhattacharyyaResult);


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
    QString objName = this->objectName();
    message = objName + QString("::") + message;
    emit(debugMessageSig(message));
}
