/********************************************************************************
** Form generated from reading UI file 'formcameragra.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCAMERAGRA_H
#define UI_FORMCAMERAGRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_FormCameraGra
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_url;
    QPushButton *pushButton_ok;
    QLabel *label_url;
    VideoWidget *openGLWidget;

    void setupUi(QWidget *FormCameraGra)
    {
        if (FormCameraGra->objectName().isEmpty())
            FormCameraGra->setObjectName(QStringLiteral("FormCameraGra"));
        FormCameraGra->resize(400, 300);
        gridLayout = new QGridLayout(FormCameraGra);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_url = new QLineEdit(FormCameraGra);
        lineEdit_url->setObjectName(QStringLiteral("lineEdit_url"));

        gridLayout->addWidget(lineEdit_url, 0, 1, 1, 1);

        pushButton_ok = new QPushButton(FormCameraGra);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        gridLayout->addWidget(pushButton_ok, 0, 2, 1, 1);

        label_url = new QLabel(FormCameraGra);
        label_url->setObjectName(QStringLiteral("label_url"));

        gridLayout->addWidget(label_url, 0, 0, 1, 1);

        openGLWidget = new VideoWidget(FormCameraGra);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 1, 0, 1, 3);


        retranslateUi(FormCameraGra);

        QMetaObject::connectSlotsByName(FormCameraGra);
    } // setupUi

    void retranslateUi(QWidget *FormCameraGra)
    {
        FormCameraGra->setWindowTitle(QApplication::translate("FormCameraGra", "Form", 0));
        pushButton_ok->setText(QApplication::translate("FormCameraGra", "ok", 0));
        label_url->setText(QApplication::translate("FormCameraGra", "url", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCameraGra: public Ui_FormCameraGra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCAMERAGRA_H
