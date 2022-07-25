#include "Login.h"
#include "ui_Login.h"
#include "widget.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    QString s =ui->lineEdit->text();
    Widget* p = new Widget(nullptr,s);
    p->show();
    this->hide();
}
