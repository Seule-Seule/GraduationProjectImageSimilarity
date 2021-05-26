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
        }
    }
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, hist_mage);
    debugMessage(QString(window_name.c_str()) + QString(" histogram draw ok !"));
}

void ImageAlgorithmView::CompImageHist(const Mat &srcIn,WorkSpace ws, int id)
{
    if (srcIn.empty()){
        debugMessage("CompImageHist src_in is empty !");
        return;
    }

    Mat src_in;
    srcIn.copyTo(src_in);
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

void ImageAlgorithmView::ColorHistogram(const Mat &leftImageIn,const Mat &rightImageIn)
{
    debugMessage("ColorHistogram begin !");

    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);

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

    // 计算相似性
    double results = { 0.0 };
    results = compareHist(histLeft, histRight, CV_COMP_CORREL);
    QString messageCorrel = QString(QString("ColorHistogram Images Similarity::") + QString::number(results));
    detectMessage(messageCorrel);
    debugMessage("ColorHistogram end !");
}

double ImageAlgorithmView::NormalizedColorHistogram(const Mat &leftImageIn,const Mat &rightImageIn, bool sengMessage)
{
    if(sengMessage)
    {
        debugMessage("NormalizedColorHistogram begin !");
    }

    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);

    Mat leftSrc, rightSrc;
    cvtColor(leftImage, leftSrc, CV_RGB2HSV);
    cvtColor(rightImage, rightSrc, CV_RGB2HSV);

    // 计算直方图
    Mat histLeft, histRight;
    int h_bins = 50, s_bins = 60;
    int histsize[] = { h_bins,s_bins };
    float h_ranges[] = { 0,180 };
    float s_ranges[] = { 0,256 };
    const float *ranges[] = { h_ranges,s_ranges };
    int channels3[] = { 0,1 };
    calcHist(&leftSrc, 1, channels3, Mat(), histLeft, 1, histsize, ranges, true, false);
    calcHist(&rightSrc, 1, channels3, Mat(), histRight, 1, histsize, ranges, true, false);

    // 全局归一化
    normalize(histLeft, histLeft, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(histRight, histRight, 0, 1, NORM_MINMAX, -1, Mat());

    // 计算相似性
    double result =  0.0 ;
    result = compareHist(histLeft, histRight, CV_COMP_CORREL);

    // 发送消息
    if(sengMessage)
    {
        QString messageCorrel = QString(QString("NormalizedColorHistogram Images Similarity::") + QString::number(result));
        detectMessage(messageCorrel);
        debugMessage("NormalizedColorHistogram end !");
    }
    return result;
}

double ImageAlgorithmView::SubNormalizedColorHistogram(const Mat &leftImageIn,const Mat &rightImageIn, int scale, bool sengMessage)
{
    debugMessage("SubNormalizedColorHistogram begin !");

    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);

    size_t subImageNumber = scale*scale;
    QVector<double> subImageResult;

    // 生成子图
    QVector<Mat> leftImageCeil(subImageNumber);
    QVector<Mat> rightImageCeil(subImageNumber);
    splitMat(leftImage, scale, scale, leftImageCeil);
    splitMat(rightImage, scale, scale, rightImageCeil);

    // 计算相似性
    double resultSum = 0.0;
    for (size_t index =0; index < subImageNumber; index++)
    {
        subImageResult.push_back(NormalizedColorHistogram(leftImageCeil[index], rightImageCeil[index], false));
        resultSum = subImageResult[index]+resultSum;
    }

    if(subImageNumber == 0){
        return -1;
    }
    double result = resultSum / subImageNumber;
    if(sengMessage)
    {
        QString messageCorrel = QString(QString("SubNormalizedColorHistogram Images Similarity::") + QString::number(result));
        detectMessage(messageCorrel);
    }

    debugMessage("SubNormalizedColorHistogram end !");

    return result;
}

//剪切图片为m * n 块
void ImageAlgorithmView::splitMat(const Mat &srcIn,int m,int n, QVector<Mat> &ceilImg)
{
    if(m == 0 || n ==0)
    {
        return;
    }
    Mat srcImg;
    srcIn.copyTo(srcImg);
    int ceilHeight = (srcImg.rows-m)/m;
    int ceilWidth  = (srcImg.cols-n)/n;
    Mat roiImg;
    int index = 0;
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            Rect rect(i*ceilWidth, j*ceilHeight, ceilWidth, ceilHeight);
            roiImg = srcImg(rect);
            ceilImg[index] = roiImg;
            index++;
            roiImg.release();
        }
    }
}

double ImageAlgorithmView::SIFT(const Mat &leftImageIn, const Mat &rightImageIn, bool sengMessage)
{
    debugMessage("SIFT begin !");

    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);

    float Rate = 0.3;
    Mat imageL;
    Mat imageR;
    leftImage.copyTo(imageL);
    rightImage.copyTo(imageR);

    //提取特征点方法 SIFT
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    //单独提取特征点
    std::vector<cv::KeyPoint> keyPointL, keyPointR;
    sift->detect(imageL, keyPointL);
    sift->detect(imageR, keyPointR);

    //提取特征点并计算特征描述子
    cv::Mat despL, despR;
    sift->detectAndCompute(imageL, cv::Mat(), keyPointL, despL);
    sift->detectAndCompute(imageR, cv::Mat(), keyPointR, despR);

    std::vector<cv::DMatch> matches;

    //如果采用flannBased方法 那么 desp通过orb的到的类型不同需要先转换类型
    if (despL.type() != CV_32F || despR.type() != CV_32F)
    {
        despL.convertTo(despL, CV_32F);
        despR.convertTo(despR, CV_32F);
    }

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
    matcher->match(despL, despR, matches);

    // 特征点排序  从小到大
    sort(matches.begin(), matches.end());

    //按比例挑选匹配度高的特征点 计算欧氏距离平均值
    std::vector< cv::DMatch > good_matches;
    double sumRateDistance = 0;
    if (matches.size() > 2)
    {
        for (size_t i = 0; i < matches.size()*Rate; i++)
        {
            good_matches.push_back(matches[i]);
            sumRateDistance += good_matches[i].distance;
        }
    }

    // 计算结果
    double result = 0.0;
    if(matches.size()-1 >= 0)
    {
        double maxDistance = matches[matches.size()-1].distance;
        double meanRateDistance = sumRateDistance/(matches.size()*Rate);
        if (0 == maxDistance){
            result = 1.0;
        }

        if(maxDistance == 0){
            maxDistance = 0.0001;
        }
        result = 1-meanRateDistance/maxDistance;
    }
    if(sengMessage)
    {
        QString messageCorrel = QString(QString("SIFT Images Similarity::") + QString::number(result));
        detectMessage(messageCorrel);
    }

    debugMessage("SIFT end !");
    return result;
}

double ImageAlgorithmView::HASH(HashType type, const Mat &leftImageIn, const Mat &rightImageIn, bool sengMessage)
{
    debugMessage("HASH begin !");
    QString leftStr, rightStr, strNotice;


    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);


    switch(type)
    {
    case HashType::eAHASH:
        leftStr = aHashValue(leftImage);
        rightStr = aHashValue(rightImage);
        strNotice = "aHash";
        break;
    case HashType::ePHASH:
        leftStr = pHashValue(leftImage);
        rightStr = pHashValue(rightImage);
        strNotice = "pHash";
        break;
    case HashType::eDHASH:
        leftStr = dHashValue(leftImage);
        rightStr = dHashValue(rightImage);
        strNotice = "dHash";
        break;
    default:
        return -1;
    }

    // 结果归一化
    int hanmingDistance = HanmingDistance(leftStr, rightStr);
    double result = 1.0-hanmingDistance/64.0;

    if(sengMessage)
    {
        QString messageCorrel = QString(strNotice + QString(" Images Similarity::") + QString::number(result));
        detectMessage(messageCorrel);
    }

    debugMessage("HASH end !");

    return result;
}

//汉明距离计算
int ImageAlgorithmView::HanmingDistance(QString &str1, QString &str2)
{
    if((str1.size()!=64)||(str2.size()!=64))
        return -1;
    int difference = 0;
    for(int i=0;i<64;i++)
    {
        if(str1[i]!=str2[i])
            difference++;
    }
    return difference;
}

//均值aHash算法
QString ImageAlgorithmView::aHashValue(const Mat &srcIn)
{
    Mat src;
    srcIn.copyTo(src);
    QString rst(64,'\0');
    Mat img;
    if(src.channels()==3)
        cvtColor(src,img,CV_BGR2GRAY);
    else
        img=src.clone();

    /*第一步，缩小尺寸。将图片缩小到8x8的尺寸，总共64个像素,去除图片的细节*/
    resize(img,img,Size(8,8));

    /* 第二步，简化色彩(Color Reduce)。将缩小后的图片，转为64级灰度。*/
    uchar *pData;
    for(int i=0;i<img.rows;i++)
    {
        pData = img.ptr<uchar>(i);
        for(int j=0;j<img.cols;j++)
        {
            pData[j]=pData[j]/4;
        }
    }

    /* 第三步，计算平均值。计算所有64个像素的灰度平均值。*/
    int average = mean(img).val[0];

    /* 第四步，比较像素的灰度。将每个像素的灰度，与平均值进行比较。大于或等于平均值记为1,小于平均值记为0*/
    Mat mask= (img>=(uchar)average);

    /* 第五步，计算哈希值。*/
    int index = 0;
    for(int i=0;i<mask.rows;i++)
    {
        pData = mask.ptr<uchar>(i);
        for(int j=0;j<mask.cols;j++)
        {
            if(pData[j]==0)
                rst[index++]='0';
            else
                rst[index++]='1';
        }
    }
    return rst;
}

//pHash 感知算法
QString ImageAlgorithmView::pHashValue(const Mat &srcIn)
{
    Mat src;
    srcIn.copyTo(src);
    Mat img,  dst;
    QString rst(64,'\0');
    double dIdex[64];
    double mean = 0.0;
    int k = 0;
    if(src.channels()==3){
        cvtColor(src,img,CV_BGR2GRAY);
        img = Mat_<double>(img);
    }
    else{
        img=Mat_<double>(src.clone());
    }

    /* 第一步，缩放尺寸*/
    resize(img, img, Size(8,8));

    /* 第二步，离散余弦变换，DCT系数求取*/
    dct(img, dst);

    /* 第三步，求取DCT系数均值（左上角8*8区块的DCT系数）*/
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j)
        {
            dIdex[k] = dst.at<double>(i, j);
            mean += dst.at<double>(i, j)/64;
            ++k;
        }
    }

    /* 第四步，计算哈希值。*/
    for (int i =0;i<64;++i)
    {
        if (dIdex[i]>=mean)
        {
            rst[i]='1';
        }
        else
        {
            rst[i]='0';
        }
    }
    return rst;
}

//dHash 差异值哈希算法
QString ImageAlgorithmView::dHashValue(const Mat& srcIn)
{
    Mat src;
    srcIn.copyTo(src);

    Mat img ;
    QString dhash(64,'\0');

    // 图片进行灰度化
    if(src.channels()==3){
        cvtColor(src,img,CV_BGR2GRAY);
        img = Mat_<double>(img);
    }
    else{
        img=Mat_<double>(src.clone());
    }

    // 将图片缩放为8*9
    resize(img, img, Size(9, 8));

    for (int i = 0; i < 8;i++)
    {
        int pos = i * 8;
        for (int j =0; j < 8;j++)
        {
            dhash[pos + j] = (img.at<double>(i, j) > img.at<double>(i, j+1)) ? '1' : '0';
        }
    }

    return dhash;
}


double ImageAlgorithmView::Calculate(const Mat &leftImageIn, const Mat &rightImageIn, bool sengMessage)
{
    debugMessage("Calculate begin !");

    Mat leftImage, rightImage;
    leftImageIn.copyTo(leftImage);
    rightImageIn.copyTo(rightImage);

    // 获取两张图片分辨率 使用图像长宽比中较大的一边
    int leftSizt = (leftImage.rows > leftImage.cols) ? leftImage.rows : leftImage.cols;
    int rightSizt =  (rightImage.rows > rightImage.cols) ? rightImage.rows : rightImage.cols;

    // 分辨率分析 算法调用
    double result = 0.0;
    bool bChooseAl = false;
    QVector<float>  vecAlph;
    if(leftSizt == rightSizt && !bChooseAl)
    {
        // 所有算法平均值
        vecAlph.push_back(0.333);
        vecAlph.push_back(0.333);
        vecAlph.push_back(0.333);
        bChooseAl = true;
    }
    // 10%
    else if((leftSizt*0.1 <= rightSizt || rightSizt*0.1 <= leftSizt)&& !bChooseAl)
    {
        // SIFT 40%  hist 30% hash 30%
        vecAlph.push_back(0.4);
        vecAlph.push_back(0.3);
        vecAlph.push_back(0.3);
        bChooseAl = true;
    }
    // 30%
    else if((leftSizt*0.3 <= rightSizt || rightSizt*0.3 <= leftSizt)&& !bChooseAl)
    {
        // SIFT 50%  hist 30% hash 20%
        vecAlph.push_back(0.5);
        vecAlph.push_back(0.3);
        vecAlph.push_back(0.2);
        bChooseAl = true;
    }
    // 50%
    else if((leftSizt*0.5 <= rightSizt || rightSizt*0.5 <= leftSizt)&& !bChooseAl)
    {
        // SIFT 60%  hist 20% hash 20%
        vecAlph.push_back(0.6);
        vecAlph.push_back(0.2);
        vecAlph.push_back(0.2);
        bChooseAl = true;
    }
    // 差异超过50%
    else
    {
        // SIFT 70%  hist 15% hash 15%
        vecAlph.push_back(0.7);
        vecAlph.push_back(0.15);
        vecAlph.push_back(0.15);
        bChooseAl = true;
    }

    // 计算分级相似性
    QVector<double> vecResultTemp;
    if(bChooseAl)
    {
        vecResultTemp.push_back(SIFT(leftImage, rightImage, false));
        vecResultTemp.push_back(SubNormalizedColorHistogram(leftImage, rightImage, 4, false));
        vecResultTemp.push_back(HASH(HashType::ePHASH, leftImage, rightImage, false));
    }

    if(vecResultTemp.size() == 3 && vecAlph.size() == 3)
    {
        result = vecResultTemp[0] * vecAlph[0]+vecResultTemp[1] * vecAlph[1] + vecResultTemp[2] * vecAlph[2];
    }

    if(sengMessage)
    {
        QString messageCorrel = QString(QString("Calculate Images Similarity::") + QString::number(result));
        detectMessage(messageCorrel);
    }

    debugMessage("Calculate end !");
    return result;
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
