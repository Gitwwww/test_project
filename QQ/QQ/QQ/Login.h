﻿#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
};

#endif // LOGIN_H
