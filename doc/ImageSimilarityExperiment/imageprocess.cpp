#include "imageprocess.hpp"

void getFiles(string path, vector <string> & files)
{
    long hFile = 0;
    struct _finddata_t fileinfo;
    string pathp;
    if ((hFile = _findfirst(pathp.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    continue;
                }
            }
            else
            {
                string filestr = fileinfo.name;
                files.push_back(pathp.assign(path).append("/").append(filestr));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

vector<string> splitString(const std::string &str, const std::string &pattern)
{
    char * strc = new char[strlen(str.c_str())+1];
    strcpy(strc, str.c_str());   //string转换成C-string
    vector<string> res;
    char* temp = strtok(strc, pattern.c_str());
    while(temp != NULL)
    {
        res.push_back(string(temp));
        temp = strtok(NULL, pattern.c_str());
    }
    delete[] strc;
    return res;
}

void getInfo(std::string file, map<int, std::string> &info)
{
    ifstream fin(file);
    const int LINE_LENGTH = 200; // 缓冲区 字符数
    char str[LINE_LENGTH];
    vector<string> temp;
    int fileIndex = 0;
    while( fin.getline(str,LINE_LENGTH) )
    {
        temp = splitString(str, ":");
        if (temp.size() != 2)
            return;
        info[fileIndex] = temp[1];
        fileIndex++;
    }
}

// 随机给每张图像添加一些直线
void ImageProcess()
{
    std::string path("Z:/testImages/images");

    std::string logPath = path + string("/ImageProcessLog.txt");
    ofstream logFile;
    //ios::app指从文件尾开始输出
    logFile.open(logPath,ios::out|ios::app);
    if(!logFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }

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

        for (size_t index = 0; index < resolutions.size(); index++)
        {
            // 待写入图片
            string imageName = calendar+string("_")+fileName+string("_")+ resolutions[index]+string(".jpg");
            string imagePath = path + string("/") + resolutions[index] + string("/") + imageName;
            string imageSaveName = calendar+string("_")+fileName+string("_")+ resolutions[index]+string("_Similarity.jpg");
            string imageSavePath = path + string("/") + resolutions[index] + string("/") + imageSaveName;

            Mat image = imread(imagePath);
            RNG rng(21897517);

            for (int index = 0; index < rng.uniform(100, 500); index ++){
                Point rngLinep1 = Point(rng.uniform(0, image.cols),rng.uniform(0, image.rows));
                Point rngLinep2 = Point(rng.uniform(0, image.cols),rng.uniform(0, image.rows));
                Scalar rngLinecolor = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
                line(image, rngLinep1, rngLinep2, rngLinecolor, 2,LINE_AA, 0);
            }

            bool temp = imwrite(imageSavePath, image);
            if (temp){
                qDebug() << "Image " << imageSavePath.c_str() << " Save ok !";
                logFile << "Image " << imageSavePath.c_str() << " Save ok !" << endl;
            }else {
                qDebug() << "Image " << imageSavePath.c_str() << " Save fail !";
                logFile << "Image " << imageSavePath.c_str() << " Save fail !" << endl;
            }
        }
    }
}

void DrawHist(String window_name, int width, int height, QVector<Mat> &hist_in, string SavePath)
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

    if (_access(SavePath.c_str(), 0) == -1)
        imwrite(SavePath, hist_mage);
}

void CompImageHist(const Mat &src, string SavePath)
{
    if (src.empty()){
        return;
    }
    String position;

    int histSize = 255;
    float range[] = { 0, 255 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    std::vector<Mat> channels(3);
    split(src, channels);

    //声明H S通道的hist数组
    Mat hist_h, hist_s;
    calcHist(&channels[0], 1, 0, Mat(), hist_h, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&channels[1], 1, 0, Mat(), hist_s, 1, &histSize, &histRange, uniform, accumulate);

    QVector<Mat> temp_Draw;
    temp_Draw.push_back(hist_h);
    temp_Draw.push_back(hist_s);
    DrawHist(position + String("Histogram in HSV"),400, 300, temp_Draw, SavePath);
}


