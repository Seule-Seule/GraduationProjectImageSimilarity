#include "colorhistsubequalization.hpp"
#include "colorhistogramequalization.hpp"

#include "imageprocess.hpp"


//剪切图片为m * n 块
void splitMat(Mat &srcImg,int m,int n,vector<Mat> &ceilImg){
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

double colorHistSubEqualization(Mat &leftImage, Mat &rightImage, string leftSavePath, string rightSavePath, size_t scale )
{
    if (leftImage.empty() || rightImage.empty() || leftSavePath.empty() || rightSavePath.empty()){
        qDebug() << "colorHistSubEqualization input error!";
        return -1;
    }
    size_t subImageNumber = scale*scale;
    vector<double> subImageResult;

    // 生成子图
    vector<Mat> leftImageCeil(subImageNumber);
    vector<Mat> rightImageCeil(subImageNumber);
    splitMat(leftImage, scale, scale, leftImageCeil);
    splitMat(rightImage, scale, scale, rightImageCeil);

    // 计算相似性
    double resultSum = 0;
    string rightSubSavePath;
    string leftSubSavePath;
    for (size_t index =0; index < subImageNumber; index++)
    {
        leftSubSavePath = (splitString(leftSavePath, ".")[0] + string("_subHist") +to_string(index) + string(".jpg"));
        rightSubSavePath = (splitString(rightSavePath, ".")[0] + string("_sub") + to_string(index) + string(".jpg"));
        subImageResult.push_back(ColorHistEqualization(leftImageCeil[index], rightImageCeil[index],leftSubSavePath, rightSubSavePath));

        resultSum = subImageResult[index]+resultSum;

        if (_access(leftSubSavePath.c_str(), 0) == -1)
            imwrite(leftSubSavePath, leftImageCeil[index]);
        if (_access(rightSubSavePath.c_str(), 0) == -1)
            imwrite(rightSubSavePath, rightImageCeil[index]);
    }

    double result = resultSum / subImageNumber;
    return result;
}

//同一幅图像，不同分辨率情况下相似度检验
void ColorHistSubEqualizationTest1()
{
    std::string path("Z:/testImages/images");

    std::string resultPath = path + string("/ColorHistSubEqualizationTest1");
    if (_access(resultPath.c_str(), 0) == -1)
        _mkdir(resultPath.c_str());

    // 存储结果： 名字1 分辨率1 分辨率2 检测结果
    std::string resultCsvPath = path + string("/ColorHistSubEqualizationTest1/result.csv");
    ofstream csvFile;
    //ios::app指从文件尾开始输出
    csvFile.open(resultCsvPath,ios::out|ios::app);
    if(!csvFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }
    csvFile << "图片名" << "," << "分辨率1" << "," << "分辨率2" << "," << "相似性检验结果" << "切割子图数量" << endl;

    vector<std::string> files;
    getFiles(path, files);

    map<int, std::string> info;
    string calendar;
    string fileName;
    vector<string> resolutions;
    for (string file : files)
    {
        getInfo(file, info);
        calendar = info[0];
        fileName = info[2];
        resolutions = splitString(info[4], ",");

        // 中间分辨率图片 作为基准图片
        string imageName0 = calendar+string("_")+fileName+string("_")+ resolutions[resolutions.size()/2 ]+string(".jpg");
        string imagePath0 = path + string("/") + resolutions[resolutions.size()/2 ] + string("/") + imageName0;

        string resultImagePath = path + string("/ColorHistSubEqualizationTest1/") + fileName;
        if (_access(resultImagePath.c_str(), 0) == -1)
            _mkdir(resultImagePath.c_str());

        string imageSavePath0 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[resolutions.size()/2 ]+string("_base.jpg");
        for (size_t index = 1; index < resolutions.size(); index++){
            // 待检验图片
            string imageName1 = calendar+string("_")+fileName+string("_")+ resolutions[index]+string(".jpg");
            string imagePath1 = path + string("/") + resolutions[index] + string("/") + imageName1;
            string imageSavePath1 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[index]+string("_test.jpg");

            Mat image0 = imread(imagePath0);
            Mat image1 = imread(imagePath1);
            double result = colorHistSubEqualization(image0, image1, imageSavePath0, imageSavePath1, 4);
            csvFile << fileName << "," << resolutions[resolutions.size()/2] << "," << resolutions[index] << "," << result << "," << 16 << endl;
        }
    }
    csvFile.close();
}
