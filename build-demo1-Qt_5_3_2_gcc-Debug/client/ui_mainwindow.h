/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "formcameragra.h"
#include "formcameratext.h"
#include "formdevicedetail.h"
#include "formdevicetree.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_device;
    QVBoxLayout *verticalLayout_2;
    FormDeviceTree *widget_device_tree;
    FormDeviceDetail *widget_device_detail;
    QWidget *widget_camera;
    QVBoxLayout *verticalLayout;
    FormCameraText *widget_camera_text;
    FormCameraGra *widget_camera_gra;
    QMenuBar *menuBar;
    QMenu *menuZenith;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(915, 565);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_device = new QWidget(centralWidget);
        widget_device->setObjectName(QStringLiteral("widget_device"));
        widget_device->setMaximumSize(QSize(300, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_device);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_device_tree = new FormDeviceTree(widget_device);
        widget_device_tree->setObjectName(QStringLiteral("widget_device_tree"));
        widget_device_tree->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(widget_device_tree);

        widget_device_detail = new FormDeviceDetail(widget_device);
        widget_device_detail->setObjectName(QStringLiteral("widget_device_detail"));

        verticalLayout_2->addWidget(widget_device_detail);


        horizontalLayout->addWidget(widget_device);

        widget_camera = new QWidget(centralWidget);
        widget_camera->setObjectName(QStringLiteral("widget_camera"));
        verticalLayout = new QVBoxLayout(widget_camera);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_camera_text = new FormCameraText(widget_camera);
        widget_camera_text->setObjectName(QStringLiteral("widget_camera_text"));
        widget_camera_text->setMaximumSize(QSize(16777215, 70));

        verticalLayout->addWidget(widget_camera_text);

        widget_camera_gra = new FormCameraGra(widget_camera);
        widget_camera_gra->setObjectName(QStringLiteral("widget_camera_gra"));
        widget_camera_gra->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(widget_camera_gra);


        horizontalLayout->addWidget(widget_camera);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 915, 19));
        menuZenith = new QMenu(menuBar);
        menuZenith->setObjectName(QStringLiteral("menuZenith"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuZenith->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        menuZenith->setTitle(QApplication::translate("MainWindow", "zenith", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
