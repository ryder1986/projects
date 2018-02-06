/********************************************************************************
** Form generated from reading UI file 'formcameratext.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCAMERATEXT_H
#define UI_FORMCAMERATEXT_H

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

QT_BEGIN_NAMESPACE

class Ui_FormCameraText
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *FormCameraText)
    {
        if (FormCameraText->objectName().isEmpty())
            FormCameraText->setObjectName(QStringLiteral("FormCameraText"));
        FormCameraText->resize(400, 300);
        gridLayout = new QGridLayout(FormCameraText);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(FormCameraText);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        lineEdit = new QLineEdit(FormCameraText);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(FormCameraText);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(FormCameraText);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(FormCameraText);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);


        retranslateUi(FormCameraText);

        QMetaObject::connectSlotsByName(FormCameraText);
    } // setupUi

    void retranslateUi(QWidget *FormCameraText)
    {
        FormCameraText->setWindowTitle(QApplication::translate("FormCameraText", "Form", 0));
        pushButton->setText(QApplication::translate("FormCameraText", "PushButton", 0));
        label->setText(QApplication::translate("FormCameraText", "url", 0));
        label_2->setText(QApplication::translate("FormCameraText", "area", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCameraText: public Ui_FormCameraText {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCAMERATEXT_H
