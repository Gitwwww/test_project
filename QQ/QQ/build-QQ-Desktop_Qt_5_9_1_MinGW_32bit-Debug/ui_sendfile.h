/********************************************************************************
** Form generated from reading UI file 'sendfile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILE_H
#define UI_SENDFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendFile
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QProgressBar *progressBar;

    void setupUi(QWidget *SendFile)
    {
        if (SendFile->objectName().isEmpty())
            SendFile->setObjectName(QStringLiteral("SendFile"));
        SendFile->resize(417, 146);
        verticalLayout = new QVBoxLayout(SendFile);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SendFile);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton = new QToolButton(SendFile);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/WJ.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);

        horizontalLayout->addWidget(toolButton);

        progressBar = new QProgressBar(SendFile);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SendFile);

        QMetaObject::connectSlotsByName(SendFile);
    } // setupUi

    void retranslateUi(QWidget *SendFile)
    {
        SendFile->setWindowTitle(QApplication::translate("SendFile", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("SendFile", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
        toolButton->setText(QApplication::translate("SendFile", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SendFile: public Ui_SendFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILE_H
