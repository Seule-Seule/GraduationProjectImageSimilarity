#include "filesave.hpp"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QStandardPaths>
#include <QDateTime>
#include <QSqlRecord>

FileSave::FileSave(QObject *parent) : QObject(parent)
{
    m_fileSave = false;
}

void FileSave::initFileSave()
{
    if (!m_filePath.isEmpty()){
        debugShowMessage(m_filePath + QString(" is not empty ! "));
        return;
    }
    QFileDialog file_dialog;
    file_dialog.setAcceptMode(QFileDialog::AcceptSave);
    file_dialog.setWindowTitle(tr("Choose PDF Save Path."));
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.setOption(QFileDialog::DontResolveSymlinks);
    file_dialog.setNameFilters(QStringList()<< "PDF File (*.pdf)");
    file_dialog.setDefaultSuffix("pdf");
    QString _documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    file_dialog.setDirectory(_documentsPath);
    if (!file_dialog.exec() || file_dialog.selectedFiles().size() == 0) {
        statusBurShowMessage(tr("No choose file path !"), 5000);
        return ;
    }
    m_filePath = file_dialog.selectedFiles()[0];

    statusBurShowMessage(tr("Choose file path ok !"), 5000);
}

void FileSave::save(const QSqlQueryModel &model, const QPixmap &leftPixmap, const QPixmap &rightPixmap)
{
    if (model.rowCount() == 0){
        statusBurShowMessage(tr("Model not have data, file save fail!"), 3000);
        return;
    }
    if (leftPixmap.size() == QSize(0,0)){
        statusBurShowMessage(tr("Left image is empty, file save fail !"), 3000);
        return;
    }
    if (rightPixmap.size() == QSize(0,0)){
        statusBurShowMessage(tr("Right image is empty, file save fail !"), 3000);
        return;
    }
    debugShowMessage(("File save begin !"));
    initFileSave();

    m_pPdfWriter = new QPdfWriter(m_filePath);
    m_pPdfWriter->setPageSize(QPagedPaintDevice::A4);
    // 设置纸张的分辨率为300,因此其像素为3508X2479
    m_pPdfWriter->setResolution(300);
    m_pPdfWriter->setPageMargins(QMargins(60, 60, 60, 60));

    m_pPdfPainter = new QPainter(m_pPdfWriter);   // qt绘制工具

    m_iTop = 0;
    m_iContentWidth = m_pPdfWriter->width() - 40;

    // 标题,22号字
    writeText(22, Qt::AlignHCenter, QString("Image Similarity Test Report"));

    QString _currentDateTime =QDateTime::currentDateTime().toString(" yyyy-MM-dd hh:mm:ss");
    QString dataInfo  = QString("Report save at : ")  + _currentDateTime;
    writeText(12, Qt::AlignHCenter, dataInfo);

    // 绘制图片
    writeImage(leftPixmap, rightPixmap);

    // 正文写入
    for (int index = 0; index < model.rowCount(); index++){
        QString writeText = (model.record(index).value("algorithm").toString() + QString(": ") + \
                            model.record(index).value("result").toString() + QString(": ") + \
                            model.record(index).value("time").toString() );
        this->writeText(16, Qt::AlignLeft, writeText);
    }

    m_pPdfPainter->end();
    statusBurShowMessage(tr("File save ok !"), 5000);

}

void FileSave::writeText(int fontSize, Qt::Alignment flags, QString message)
{
    QTextOption option(flags | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);
    static QFont font;
    font.setPointSize(fontSize);
    m_pPdfPainter->setFont(font);

    QFontMetrics fm = m_pPdfPainter->fontMetrics();
    size_t width = fm.width(message);
    size_t height = fm.descent()+fm.ascent();
    if (m_iContentWidth < width){
        height = height *2 ;
    }

    m_pPdfPainter->drawText(QRect(0, m_iTop, m_iContentWidth, height), message, option);

    m_iTop += height;
}

void FileSave::writeImage( const QPixmap &leftPixmap, const QPixmap &rightPixmap)
{
    // TODO  图片上显示图片信息 例如 路径 分辨率之类
    QSize _pixmapSize(m_pPdfWriter->width() / 2 - 10,m_pPdfWriter->width() / 2 - 10);
    m_pPdfPainter->drawPixmap(0, m_iTop, _pixmapSize.width(), _pixmapSize.height(), leftPixmap.scaled(_pixmapSize));
    m_pPdfPainter->drawPixmap(_pixmapSize.width() + 10, m_iTop, _pixmapSize.width(), _pixmapSize.height(), rightPixmap.scaled(_pixmapSize));
    m_iTop += m_pPdfWriter->width() / 2 - 10;
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

