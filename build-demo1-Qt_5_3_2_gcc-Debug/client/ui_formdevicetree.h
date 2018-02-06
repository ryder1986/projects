/********************************************************************************
** Form generated from reading UI file 'formdevicetree.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDEVICETREE_H
#define UI_FORMDEVICETREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_device_detail
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *Form_device_detail)
    {
        if (Form_device_detail->objectName().isEmpty())
            Form_device_detail->setObjectName(QStringLiteral("Form_device_detail"));
        Form_device_detail->resize(400, 300);
        Form_device_detail->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(Form_device_detail);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(Form_device_detail);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        retranslateUi(Form_device_detail);

        QMetaObject::connectSlotsByName(Form_device_detail);
    } // setupUi

    void retranslateUi(QWidget *Form_device_detail)
    {
        Form_device_detail->setWindowTitle(QApplication::translate("Form_device_detail", "Form", 0));
        groupBox->setTitle(QApplication::translate("Form_device_detail", "device", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_device_detail: public Ui_Form_device_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDEVICETREE_H
