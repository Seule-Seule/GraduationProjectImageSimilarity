#include "filesave.hpp"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QStandardPaths>

FileSave::FileSave(QObject *parent) : QObject(parent)
{
    m_fileSave = false;
    m_sizeX = 0;  // 光标x
    m_sizeY = 0;  // 光标y
}

QVector<QString> splitQString(const QString &str, const QString &pattern)
{
    char * strc = new char[strlen(str.toStdString().c_str())+1];
    strcpy(strc, str.toStdString().c_str());   //string转换成C-string
    QVector<QString> res;
    char* temp = strtok(strc, pattern.toStdString().c_str());
    while(temp != NULL)
    {
        res.push_back(QString(temp));
        temp = strtok(NULL, pattern.toStdString().c_str());
    }
    delete[] strc;
    return res;
}

void FileSave::initFileSave()
{
    if (!m_filePath.isEmpty()){
        debugShowMessage(m_filePath + QString("is not empty ! "));
        return;
    }
    QFileDialog file_dialog;
    file_dialog.setAcceptMode(QFileDialog::AcceptSave);
    file_dialog.setWindowTitle(tr("Choose PDF Save Path."));
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.setOption(QFileDialog::DontResolveSymlinks);
    file_dialog.setNameFilters(QStringList()<< "PDF File (*.pdf)" << "CSV File(*.csv)");
    file_dialog.setDefaultSuffix("pdf");
    QString _documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    file_dialog.setDirectory(_documentsPath);
    if (!file_dialog.exec() || file_dialog.selectedFiles().size() == 0) {
        statusBurShowMessage(tr("No choose file path !"), 5000);
        return ;
    }
    m_filePath = file_dialog.selectedFiles()[0];
    QVector<QString> _filePathVector = splitQString(m_filePath, "/");
    m_fileName = _filePathVector.back();
    QVector<QString> _fileNameVector = splitQString(m_fileName, ".");
    QString _fileType = _fileNameVector.back();
    if (_fileType == QString("pdf")){
        m_fileType = FileSave::PDF;
    }
    else if (_fileType == QString("csv")){
        m_fileType = FileSave::CSV;
    }

    statusBurShowMessage(tr("Choose file path ok !"), 5000);
}

void FileSave::save(const QStringListModel &model, const QPixmap &leftPixmap, const QPixmap &rightPixmap)
{
    debugShowMessage(tr("File save begin !"));
    initFileSave();
    if (m_fileType == FileSave::PDF){

        m_pPdfWriter = new QPdfWriter(m_filePath);
        m_pPdfWriter->setPageSize(QPagedPaintDevice::A4);
        // 设置纸张的分辨率为300,因此其像素为3508X2479
        m_pPdfWriter->setResolution(300);
        m_pPdfWriter->setPageMargins(QMargins(60, 60, 60, 60));

        QPainter* pPdfPainter = new QPainter(m_pPdfWriter);   // qt绘制工具

        // 标题上边留白
        int iTop = 0;

        // 文本宽度2100
        int iContentWidth = m_pPdfWriter->width() - 40;

        // 标题,22号字
        QFont font;
        font.setFamily("simhei.ttf");
        font.setPointSize(20);
        pPdfPainter->setFont(font);
        pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 110), Qt::AlignCenter,QString("Image Similarity Test Report"));
        iTop += 120;

        // 绘制图片
        QSize _pixmapSize(m_pPdfWriter->width() / 2 - 10,m_pPdfWriter->width() / 2 - 10);
        pPdfPainter->drawPixmap(0, iTop, _pixmapSize.width(), _pixmapSize.height(), leftPixmap.scaled(_pixmapSize));
        pPdfPainter->drawPixmap(_pixmapSize.width() + 10, iTop, _pixmapSize.width(), _pixmapSize.height(), rightPixmap.scaled(_pixmapSize));
        iTop += m_pPdfWriter->width() / 2 - 10;

        // 正文写入
        QString  modelString();
        QStringList modelList = model.stringList();
        font.setPointSize(16);
        pPdfPainter->setFont(font);
        for (size_t index = 0; index < modelList.size(); index++){
            iTop += 100;
            pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 110), Qt::AlignLeft,modelList[index]);
        }





        pPdfPainter->end();

    }
    if (m_fileType == FileSave::CSV){

    }

}

void FileSave::debugShowMessage(QString message)
{
    emit(sendDebugMessageSig(message));
}

void FileSave::DetectShowMessage(QString message)
{
    emit(sendDetectMessageSig(message));
}

void FileSave::statusBurShowMessage(QString message, int timeout)
{
    debugShowMessage(message);
    emit(sendStatusBarMessageSig(message, timeout));
}

