/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_m;
    QSlider *slider_m;
    QLineEdit *input_m;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_r;
    QSlider *slider_r;
    QLineEdit *input_r;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_vy;
    QSlider *slider_vy;
    QLineEdit *input_vy;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_vx;
    QSlider *slider_vx;
    QLineEdit *input_vx;
    QPushButton *start_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_m = new QLabel(centralwidget);
        label_m->setObjectName("label_m");

        horizontalLayout->addWidget(label_m);

        slider_m = new QSlider(centralwidget);
        slider_m->setObjectName("slider_m");
        slider_m->setMinimum(1);
        slider_m->setMaximum(100);
        slider_m->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(slider_m);

        input_m = new QLineEdit(centralwidget);
        input_m->setObjectName("input_m");

        horizontalLayout->addWidget(input_m);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_r = new QLabel(centralwidget);
        label_r->setObjectName("label_r");

        horizontalLayout_2->addWidget(label_r);

        slider_r = new QSlider(centralwidget);
        slider_r->setObjectName("slider_r");
        slider_r->setMinimum(1);
        slider_r->setMaximum(100);
        slider_r->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(slider_r);

        input_r = new QLineEdit(centralwidget);
        input_r->setObjectName("input_r");

        horizontalLayout_2->addWidget(input_r);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_vy = new QLabel(centralwidget);
        label_vy->setObjectName("label_vy");

        horizontalLayout_4->addWidget(label_vy);

        slider_vy = new QSlider(centralwidget);
        slider_vy->setObjectName("slider_vy");
        slider_vy->setMinimum(-5000);
        slider_vy->setMaximum(5000);
        slider_vy->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_4->addWidget(slider_vy);

        input_vy = new QLineEdit(centralwidget);
        input_vy->setObjectName("input_vy");

        horizontalLayout_4->addWidget(input_vy);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_vx = new QLabel(centralwidget);
        label_vx->setObjectName("label_vx");

        horizontalLayout_3->addWidget(label_vx);

        slider_vx = new QSlider(centralwidget);
        slider_vx->setObjectName("slider_vx");
        slider_vx->setMinimum(-5000);
        slider_vx->setMaximum(5000);
        slider_vx->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(slider_vx);

        input_vx = new QLineEdit(centralwidget);
        input_vx->setObjectName("input_vx");

        horizontalLayout_3->addWidget(input_vx);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(verticalLayout_2);

        start_button = new QPushButton(centralwidget);
        start_button->setObjectName("start_button");

        verticalLayout->addWidget(start_button);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_m->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        label_r->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_vy->setText(QCoreApplication::translate("MainWindow", "Vy", nullptr));
        label_vx->setText(QCoreApplication::translate("MainWindow", "Vx", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
