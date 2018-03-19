/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QWidget *widget_device;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit_config;
    QWidget *widget_cmd_area;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_loadfile;
    QPushButton *pushButton_savefile;
    QPushButton *pushButton_save;
    QPushButton *pushButton_reboot;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_picture;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1584, 1144);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(300, 0));
        groupBox->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        QPalette palette;
        QBrush brush(QColor(85, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        widget->setPalette(palette);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_device = new QWidget(groupBox);
        widget_device->setObjectName(QStringLiteral("widget_device"));
        widget_device->setMinimumSize(QSize(0, 200));
        gridLayout_2 = new QGridLayout(widget_device);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit_config = new QTextEdit(widget_device);
        textEdit_config->setObjectName(QStringLiteral("textEdit_config"));

        gridLayout_2->addWidget(textEdit_config, 0, 0, 1, 1);


        gridLayout->addWidget(widget_device, 2, 0, 1, 1);

        widget_cmd_area = new QWidget(groupBox);
        widget_cmd_area->setObjectName(QStringLiteral("widget_cmd_area"));
        widget_cmd_area->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(widget_cmd_area);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_loadfile = new QPushButton(widget_cmd_area);
        pushButton_loadfile->setObjectName(QStringLiteral("pushButton_loadfile"));

        gridLayout_3->addWidget(pushButton_loadfile, 0, 0, 1, 1);

        pushButton_savefile = new QPushButton(widget_cmd_area);
        pushButton_savefile->setObjectName(QStringLiteral("pushButton_savefile"));

        gridLayout_3->addWidget(pushButton_savefile, 0, 1, 1, 1);

        pushButton_save = new QPushButton(widget_cmd_area);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        gridLayout_3->addWidget(pushButton_save, 1, 0, 1, 1);

        pushButton_reboot = new QPushButton(widget_cmd_area);
        pushButton_reboot->setObjectName(QStringLiteral("pushButton_reboot"));

        gridLayout_3->addWidget(pushButton_reboot, 1, 1, 1, 1);


        gridLayout->addWidget(widget_cmd_area, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_picture = new QGroupBox(centralWidget);
        groupBox_picture->setObjectName(QStringLiteral("groupBox_picture"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_picture);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        textEdit = new QTextEdit(groupBox_picture);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout_3->addWidget(textEdit);

        textEdit_2 = new QTextEdit(groupBox_picture);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        horizontalLayout_3->addWidget(textEdit_2);


        horizontalLayout_2->addWidget(groupBox_picture);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1584, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "qiaoxianglu ", 0)
         << QApplication::translate("MainWindow", "nonglinlu", 0)
        );
        pushButton->setText(QApplication::translate("MainWindow", "search", 0));
        pushButton_loadfile->setText(QApplication::translate("MainWindow", "load file", 0));
        pushButton_savefile->setText(QApplication::translate("MainWindow", "savefile", 0));
        pushButton_save->setText(QApplication::translate("MainWindow", "save", 0));
        pushButton_reboot->setText(QApplication::translate("MainWindow", "reboot", 0));
        groupBox_picture->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
