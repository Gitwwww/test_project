#include "widget.h"
#include <QApplication>
#include <chat.h>
#include <search.h>
#include <chat.h>
#include <Login.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    chat *widget = new chat(0,"","");
//    widget->show();

    Form *widget = new Form();
    widget->show();
    //关闭时将对应的IsShow变为false;
//    connect(widget,&chat::closeWidget,this,[=](){
//        IsShow[FriendName] = false;
    return a.exec();
}
