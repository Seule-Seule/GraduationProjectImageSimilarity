#include "hash.hpp"

#include <QDebug>

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;


//汉明距离计算
int HanmingDistance(string &str1, string &str2)
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
string aHashValue(Mat &src)
{
    string rst(64,'\0');
    Mat img;
    if(src.channels()==3)
        cvtColor(src,img,CV_BGR2GRAY);
    else
        img=src.clone();
    /*第一步，缩小尺寸。
         将图片缩小到8x8的尺寸，总共64个像素,去除图片的细节*/

    resize(img,img,Size(8,8));
    /* 第二步，简化色彩(Color Reduce)。
       将缩小后的图片，转为64级灰度。*/

    uchar *pData;
    for(int i=0;i<img.rows;i++)
    {
        pData = img.ptr<uchar>(i);
        for(int j=0;j<img.cols;j++)
        {
            pData[j]=pData[j]/4;
        }
    }

    /* 第三步，计算平均值。
       计算所有64个像素的灰度平均值。*/
    int average = mean(img).val[0];

    /* 第四步，比较像素的灰度。
     将每个像素的灰度，与平均值进行比较。大于或等于平均值记为1,小于平均值记为0*/
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
string pHashValue(Mat &src)
{
    Mat img,  dst;
    string rst(64,'\0');
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
string dHashValue(Mat src)
{
    Mat img ;
    string dhash(64,'\0');


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

enum HashType
{
    AHASH,
    PHASH,
    DHASH
};

int Hash(HashType type, Mat &leftImage, Mat &rightImage, string *leftSavePath=nullptr, string *rightSavePath=nullptr)
{
    if (leftImage.empty() || rightImage.empty()){
        qDebug() << ("aHash image not load !");
        return -1;
    }
    string leftStr;
    string rightStr;

    switch(type)
    {
    case HashType::AHASH:
        leftStr = aHashValue(leftImage);
        rightStr = aHashValue(rightImage);
        break;
    case HashType::PHASH:
        leftStr = pHashValue(leftImage);
        rightStr = pHashValue(rightImage);
        break;
    case HashType::DHASH:
        leftStr = dHashValue(leftImage);
        rightStr = dHashValue(rightImage);
        break;
    default:
        return -1;
    }

    if (leftSavePath != nullptr )
        *leftSavePath = leftStr;
    if (rightSavePath != nullptr )
        *rightSavePath = rightStr;

    return HanmingDistance(leftStr, rightStr);
}

void test()
{
    Mat src1 = imread("Z:/testImages/images/240x320/2019-07-17_Narrenmuehle_ZH-CN5582540867_240x320.jpg");
    Mat src2 = imread("Z:/testImages/images/320x240/2019-07-17_Narrenmuehle_ZH-CN5582540867_320x240.jpg");

    string sr1;
    string sr2;
    qDebug() << "1->" << Hash(HashType::AHASH, src1, src2, &sr1, &sr2);
    qDebug() << sr1.c_str();
    qDebug() << sr2.c_str();

    qDebug() << "2->" << Hash(HashType::PHASH, src1, src2, &sr1, &sr2);
    qDebug() << sr1.c_str();
    qDebug() << sr2.c_str();

    qDebug() << "3->" << Hash(HashType::DHASH, src1, src2, &sr1, &sr2);
    qDebug() << sr1.c_str();
    qDebug() << sr2.c_str();
}


