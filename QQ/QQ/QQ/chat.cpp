#include "chat.h"
#include "ui_chat.h"

chat::chat(QWidget *parent,QString name,QString fname) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    myname = name;
    friendname = fname;
    this->port = 5050;
    this->ServerPort = 6060;
    this->TcpPort = 7070;
    this->udpSocket = new QUdpSocket(this);

    myip = "192.168.43.48";

    //udp设置
    //采用ShareAddress模式（即允许其他的服务连接到相同的地址和端口）
    //特别是用在多客户端监听同一个服务器端口等待是特别有效
    udpSocket->bind(port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    //监听信号
    connect(udpSocket,&QUdpSocket::readyRead,this,[&]{ReceiveMessage();});

    //连接发送按钮
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        sendMsg(MyInclue::SendMsg);
    });

    connect(ui->exitBtn,&QPushButton::clicked,[=](){
        this->close();
    });
    //颜色
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font){
        ui->msgTxtEdit->setFontFamily(font.toString());
        ui->msgTxtEdit->setFocus();
    });
    //颜色选择框
    connect(ui->colorBtn,&QToolButton::clicked,[=](){
       QColor color = QColorDialog::getColor(color,this);
       ui->msgTxtEdit->setTextColor(color);
    });
    //尺寸
    void (QComboBox:: *sizebtn)(const QString &text) = &QComboBox::currentIndexChanged;
    connect(ui->sizeBox,sizebtn,[=](const QString &text){
        ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();
    });
    //加粗
    connect(ui->boldBtn,&QToolButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->msgTxtEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTxtEdit->setFontWeight(QFont::Normal);
        }
    });
    //倾斜
    connect(ui->italicTbtn,&QToolButton::clicked,[=](bool checked){
        ui->msgTxtEdit->setFontItalic(checked);
        ui->msgTxtEdit->setFocus();
    });
    //下划线
    connect(ui->underlineTbtn,&QToolButton::clicked,[=](bool checked){
        ui->msgTxtEdit->setFontUnderline(checked);
        ui->msgTxtEdit->setFocus();
    });
    //发送文件
    connect(ui->sendfileBtn,&QToolButton::clicked,[=](){
        FileName = QFileDialog::getOpenFileName(this);
        qDebug()<<FileName;
        sendMsg(MyInclue::SendFile);
    });

    //获取好友IP地址
    this->FriendIp = "127.0.0.1";

}

void chat::sendMsg(int type)
{
    switch (type) {
    case MyInclue::SendMsg:
    {
        QByteArray array;
        QDataStream stream(&array,QIODevice::WriteOnly);
        stream << type << friendname << myname;
        if(ui->msgTxtEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,"警告","发送的聊天内容不能为空!");
            return;
        }
        QString message = ui->msgTxtEdit->toHtml();
        stream << message;
        ui->msgTxtEdit->clear();
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //对话框列表
        QListWidgetItem *item = new QListWidgetItem();//每一行
        ui->msgBrowser->addItem(item);
        item->setSizeHint(QSize(80,30));//行的尺寸

        QLabel *label1 = new QLabel("[" +myname+"]");//聊天内容
        label1->setStyleSheet(QString("color:red"));
        QLabel *label = new QLabel(message);//聊天内容
        QHBoxLayout *hlayout = new QHBoxLayout();//水平布局
        hlayout->addWidget(label);
        hlayout->addWidget(label1);
        hlayout->setAlignment(Qt::AlignRight);
        QWidget *widget = new QWidget();
        widget->setLayout(hlayout);//将布局添加至widget中
        ui->msgBrowser->setItemWidget(item,widget);//将widget加入至listwidget中
        udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);
        break;
    }
    case MyInclue::SendFile:
    {
        //发送文件请求-> 对方接收到后创建TCP服务端
        QByteArray array;
        QDataStream stream(&array,QIODevice::WriteOnly);
        stream << type << friendname << myname;
        qDebug()<<myname<<"请求发送文件给"<<friendname;
        udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);
        break;
    }
    case MyInclue::StartListen:
    {
        QByteArray array;
        QDataStream stream(&array,QIODevice::WriteOnly);
        stream << type << friendname << myname;
        udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);
        break;
    }
    }
}

void chat::ReceiveMessage()
{
    qint64 size = udpSocket->pendingDatagramSize();
    int mysize = static_cast<int>(size);
    QByteArray *array = new QByteArray(mysize,0);
    udpSocket->readDatagram((*array).data(),size);
    QDataStream stream(array,QIODevice::ReadOnly);
    int mytype;
    stream >> mytype;
    QString name,fname;
    //接收者的名字 发送者的名字
    stream >> name >> fname;
    qDebug()<<"接收到udp消息  我的名字是"<<name << "朋友的名字是"<<fname;
    if(name != myname || fname != friendname)
    {
        qDebug()<<"不是xx发给我的消息";
        return;//不是xx发给我的消息
    }

    switch (mytype) {
    case MyInclue::SendMsg:
    {
        QString text;
        stream >> text;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //对话框列表
        QListWidgetItem *item = new QListWidgetItem();//每一行
        ui->msgBrowser->addItem(item);
        item->setSizeHint(QSize(80,30));//行的尺寸

        QLabel *label1 = new QLabel("["+friendname+"]");//聊天内容
        label1->setStyleSheet(QString("color:blue"));
        QLabel *label = new QLabel(text);//聊天内容
        QHBoxLayout *hlayout = new QHBoxLayout();//水平布局
        hlayout->addWidget(label1);
        hlayout->addWidget(label);
        hlayout->setAlignment(Qt::AlignLeft);
        QWidget *widget = new QWidget();
        widget->setLayout(hlayout);//将布局添加至widget中
        ui->msgBrowser->setItemWidget(item,widget);//将widget加入至listwidget中
        break;
    }
    case MyInclue::SendFile:
    {
        rf = new ReceiveFile(this,FriendIp,7070,myname);
        rf->show();

        connect(rf,&ReceiveFile::fileover,[=](){
           // delete rf;
        });
        qDebug()<<"同意"<<fname<<"发送文件给我，已经创建TCP server 等到他发送";
        sendMsg(MyInclue::StartListen);
        break;
    }
    case MyInclue::StartListen:
    {
         qDebug()<<"创建TCP client 开始发送文件....";
        sf = new SendFile(this,FileName,FriendIp,7070);
        sf->show();
        connect(sf,&SendFile::fileover,[=](){
           // delete sf;
        });
        break;
    }
    }
}


void chat::closeEvent(QCloseEvent *)
{
    emit closeWidget();
    udpSocket->close();
    udpSocket->destroyed();
}

chat::~chat()
{
    delete ui;
}

