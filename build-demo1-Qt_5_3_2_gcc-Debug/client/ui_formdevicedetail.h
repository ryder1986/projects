/********************************************************************************
** Form generated from reading UI file 'formdevicedetail.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDEVICEDETAIL_H
#define UI_FORMDEVICEDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormDeviceDetail
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_get_config;
    QPushButton *pushButton_add_cam;
    QLineEdit *lineEdit_get_config;
    QLineEdit *lineEdit_connect;
    QLineEdit *lineEdit_del_cam;
    QLineEdit *lineEdit_add_cam;
    QPushButton *pushButton_del_cam;
    QLineEdit *lineEdit_set_config;
    QPushButton *pushButton_set_config;
    QTreeWidget *treeWidget_device;

    void setupUi(QWidget *FormDeviceDetail)
    {
        if (FormDeviceDetail->objectName().isEmpty())
            FormDeviceDetail->setObjectName(QStringLiteral("FormDeviceDetail"));
        FormDeviceDetail->resize(400, 300);
        gridLayout = new QGridLayout(FormDeviceDetail);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(FormDeviceDetail);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));

        gridLayout_2->addWidget(pushButton_connect, 1, 1, 1, 1);

        pushButton_get_config = new QPushButton(groupBox);
        pushButton_get_config->setObjectName(QStringLiteral("pushButton_get_config"));

        gridLayout_2->addWidget(pushButton_get_config, 2, 1, 1, 1);

        pushButton_add_cam = new QPushButton(groupBox);
        pushButton_add_cam->setObjectName(QStringLiteral("pushButton_add_cam"));

        gridLayout_2->addWidget(pushButton_add_cam, 4, 1, 1, 1);

        lineEdit_get_config = new QLineEdit(groupBox);
        lineEdit_get_config->setObjectName(QStringLiteral("lineEdit_get_config"));

        gridLayout_2->addWidget(lineEdit_get_config, 2, 0, 1, 1);

        lineEdit_connect = new QLineEdit(groupBox);
        lineEdit_connect->setObjectName(QStringLiteral("lineEdit_connect"));

        gridLayout_2->addWidget(lineEdit_connect, 1, 0, 1, 1);

        lineEdit_del_cam = new QLineEdit(groupBox);
        lineEdit_del_cam->setObjectName(QStringLiteral("lineEdit_del_cam"));

        gridLayout_2->addWidget(lineEdit_del_cam, 5, 0, 1, 1);

        lineEdit_add_cam = new QLineEdit(groupBox);
        lineEdit_add_cam->setObjectName(QStringLiteral("lineEdit_add_cam"));

        gridLayout_2->addWidget(lineEdit_add_cam, 4, 0, 1, 1);

        pushButton_del_cam = new QPushButton(groupBox);
        pushButton_del_cam->setObjectName(QStringLiteral("pushButton_del_cam"));

        gridLayout_2->addWidget(pushButton_del_cam, 5, 1, 1, 1);

        lineEdit_set_config = new QLineEdit(groupBox);
        lineEdit_set_config->setObjectName(QStringLiteral("lineEdit_set_config"));

        gridLayout_2->addWidget(lineEdit_set_config, 3, 0, 1, 1);

        pushButton_set_config = new QPushButton(groupBox);
        pushButton_set_config->setObjectName(QStringLiteral("pushButton_set_config"));

        gridLayout_2->addWidget(pushButton_set_config, 3, 1, 1, 1);

        treeWidget_device = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_device->setHeaderItem(__qtreewidgetitem);
        treeWidget_device->setObjectName(QStringLiteral("treeWidget_device"));

        gridLayout_2->addWidget(treeWidget_device, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(FormDeviceDetail);

        QMetaObject::connectSlotsByName(FormDeviceDetail);
    } // setupUi

    void retranslateUi(QWidget *FormDeviceDetail)
    {
        FormDeviceDetail->setWindowTitle(QApplication::translate("FormDeviceDetail", "Form", 0));
        groupBox->setTitle(QApplication::translate("FormDeviceDetail", "test", 0));
        pushButton_connect->setText(QApplication::translate("FormDeviceDetail", "connect", 0));
        pushButton_get_config->setText(QApplication::translate("FormDeviceDetail", "get_config", 0));
        pushButton_add_cam->setText(QApplication::translate("FormDeviceDetail", "add_cam", 0));
        lineEdit_connect->setText(QApplication::translate("FormDeviceDetail", "192.168.1.216", 0));
        pushButton_del_cam->setText(QApplication::translate("FormDeviceDetail", "del_cam", 0));
        pushButton_set_config->setText(QApplication::translate("FormDeviceDetail", "set_config", 0));
    } // retranslateUi

};

namespace Ui {
    class FormDeviceDetail: public Ui_FormDeviceDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDEVICEDETAIL_H
