#ifndef MYINCLUE_H
#define MYINCLUE_H


#include <QWidget>
#include <QUdpSocket>
#include <QHash>
#include <QToolButton>
#include <QPoint>
#include <QMouseEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QToolButton>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>
#include <QColor>
#include <QColorDialog>
#include <QSettings>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QSpacerItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QSqlRecord>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QTimer>
#include <QBuffer>
#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>

class MyInclue
{
public:
    enum MsgType{
        Login,//登录
        Updata,//信息更新
        SendMsg,//发送信息
        Exit,//下线
        SendFile,//发送文件
        StartListen,//开始监听 表明已建立tcp服务器
     };
    MyInclue();

};

#endif // MYINCLUE_H
