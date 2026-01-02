/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout_1;
    QPushButton *btn1_1;
    QPushButton *btn1_2;
    QPushButton *btn1_3;
    QPushButton *btn1_4;
    QWidget *tab2;
    QGridLayout *gridLayout_2;
    QPushButton *btn2_1;
    QPushButton *btn2_2;
    QPushButton *btn2_3;
    QPushButton *btn2_4;
    QWidget *tab3;
    QGridLayout *gridLayout_3;
    QPushButton *btn3_1;
    QPushButton *btn3_2;
    QPushButton *btn3_3;
    QPushButton *btn3_4;
    QWidget *tab4;
    QGridLayout *gridLayout_4;
    QPushButton *btn4_1;
    QPushButton *btn4_2;
    QPushButton *btn4_3;
    QPushButton *btn4_4;
    QWidget *tabGraph;
    QVBoxLayout *verticalLayout_2;
    QWidget *chartWidget;
    QWidget *serialWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPort;
    QComboBox *comboBoxPort;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(988, 0));
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        gridLayout_1 = new QGridLayout(tab1);
        gridLayout_1->setObjectName("gridLayout_1");
        btn1_1 = new QPushButton(tab1);
        btn1_1->setObjectName("btn1_1");

        gridLayout_1->addWidget(btn1_1, 0, 0, 1, 1);

        btn1_2 = new QPushButton(tab1);
        btn1_2->setObjectName("btn1_2");

        gridLayout_1->addWidget(btn1_2, 0, 1, 1, 1);

        btn1_3 = new QPushButton(tab1);
        btn1_3->setObjectName("btn1_3");

        gridLayout_1->addWidget(btn1_3, 1, 0, 1, 1);

        btn1_4 = new QPushButton(tab1);
        btn1_4->setObjectName("btn1_4");

        gridLayout_1->addWidget(btn1_4, 1, 1, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        gridLayout_2 = new QGridLayout(tab2);
        gridLayout_2->setObjectName("gridLayout_2");
        btn2_1 = new QPushButton(tab2);
        btn2_1->setObjectName("btn2_1");

        gridLayout_2->addWidget(btn2_1, 0, 0, 1, 1);

        btn2_2 = new QPushButton(tab2);
        btn2_2->setObjectName("btn2_2");

        gridLayout_2->addWidget(btn2_2, 0, 1, 1, 1);

        btn2_3 = new QPushButton(tab2);
        btn2_3->setObjectName("btn2_3");

        gridLayout_2->addWidget(btn2_3, 1, 0, 1, 1);

        btn2_4 = new QPushButton(tab2);
        btn2_4->setObjectName("btn2_4");

        gridLayout_2->addWidget(btn2_4, 1, 1, 1, 1);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName("tab3");
        gridLayout_3 = new QGridLayout(tab3);
        gridLayout_3->setObjectName("gridLayout_3");
        btn3_1 = new QPushButton(tab3);
        btn3_1->setObjectName("btn3_1");

        gridLayout_3->addWidget(btn3_1, 0, 0, 1, 1);

        btn3_2 = new QPushButton(tab3);
        btn3_2->setObjectName("btn3_2");

        gridLayout_3->addWidget(btn3_2, 0, 1, 1, 1);

        btn3_3 = new QPushButton(tab3);
        btn3_3->setObjectName("btn3_3");

        gridLayout_3->addWidget(btn3_3, 1, 0, 1, 1);

        btn3_4 = new QPushButton(tab3);
        btn3_4->setObjectName("btn3_4");

        gridLayout_3->addWidget(btn3_4, 1, 1, 1, 1);

        tabWidget->addTab(tab3, QString());
        tab4 = new QWidget();
        tab4->setObjectName("tab4");
        gridLayout_4 = new QGridLayout(tab4);
        gridLayout_4->setObjectName("gridLayout_4");
        btn4_1 = new QPushButton(tab4);
        btn4_1->setObjectName("btn4_1");
        btn4_1->setMinimumSize(QSize(484, 0));

        gridLayout_4->addWidget(btn4_1, 0, 0, 1, 1);

        btn4_2 = new QPushButton(tab4);
        btn4_2->setObjectName("btn4_2");
        btn4_2->setMinimumSize(QSize(484, 0));

        gridLayout_4->addWidget(btn4_2, 0, 1, 1, 1);

        btn4_3 = new QPushButton(tab4);
        btn4_3->setObjectName("btn4_3");
        btn4_3->setMinimumSize(QSize(484, 0));

        gridLayout_4->addWidget(btn4_3, 1, 0, 1, 1);

        btn4_4 = new QPushButton(tab4);
        btn4_4->setObjectName("btn4_4");
        btn4_4->setMinimumSize(QSize(484, 0));

        gridLayout_4->addWidget(btn4_4, 1, 1, 1, 1);

        tabWidget->addTab(tab4, QString());
        tabGraph = new QWidget();
        tabGraph->setObjectName("tabGraph");
        verticalLayout_2 = new QVBoxLayout(tabGraph);
        verticalLayout_2->setObjectName("verticalLayout_2");
        chartWidget = new QWidget(tabGraph);
        chartWidget->setObjectName("chartWidget");

        verticalLayout_2->addWidget(chartWidget);

        tabWidget->addTab(tabGraph, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        serialWidget = new QWidget(centralwidget);
        serialWidget->setObjectName("serialWidget");
        serialWidget->setMinimumSize(QSize(988, 0));
        horizontalLayout = new QHBoxLayout(serialWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        labelPort = new QLabel(serialWidget);
        labelPort->setObjectName("labelPort");
        labelPort->setMinimumSize(QSize(29, 0));

        horizontalLayout->addWidget(labelPort);

        comboBoxPort = new QComboBox(serialWidget);
        comboBoxPort->setObjectName("comboBoxPort");
        comboBoxPort->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(comboBoxPort);

        btnConnect = new QPushButton(serialWidget);
        btnConnect->setObjectName("btnConnect");
        btnConnect->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(btnConnect);

        btnDisconnect = new QPushButton(serialWidget);
        btnDisconnect->setObjectName("btnDisconnect");
        btnDisconnect->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(btnDisconnect);

        btnRefresh = new QPushButton(serialWidget);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(btnRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(serialWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Germini Control Panel", nullptr));
        btn1_1->setText(QCoreApplication::translate("MainWindow", "Button 1", nullptr));
        btn1_2->setText(QCoreApplication::translate("MainWindow", "Button 2", nullptr));
        btn1_3->setText(QCoreApplication::translate("MainWindow", "Button 3", nullptr));
        btn1_4->setText(QCoreApplication::translate("MainWindow", "Button 4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        btn2_1->setText(QCoreApplication::translate("MainWindow", "Button 1", nullptr));
        btn2_2->setText(QCoreApplication::translate("MainWindow", "Button 2", nullptr));
        btn2_3->setText(QCoreApplication::translate("MainWindow", "Button 3", nullptr));
        btn2_4->setText(QCoreApplication::translate("MainWindow", "Button 4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        btn3_1->setText(QCoreApplication::translate("MainWindow", "Button 1", nullptr));
        btn3_2->setText(QCoreApplication::translate("MainWindow", "Button 2", nullptr));
        btn3_3->setText(QCoreApplication::translate("MainWindow", "Button 3", nullptr));
        btn3_4->setText(QCoreApplication::translate("MainWindow", "Button 4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QCoreApplication::translate("MainWindow", "Tab 3", nullptr));
        btn4_1->setText(QCoreApplication::translate("MainWindow", "Button 1", nullptr));
        btn4_2->setText(QCoreApplication::translate("MainWindow", "Button 2", nullptr));
        btn4_3->setText(QCoreApplication::translate("MainWindow", "Button 3", nullptr));
        btn4_4->setText(QCoreApplication::translate("MainWindow", "Button 4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab4), QCoreApplication::translate("MainWindow", "Tab 4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGraph), QCoreApplication::translate("MainWindow", "Graph", nullptr));
        labelPort->setText(QCoreApplication::translate("MainWindow", "Puerto:", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Desconectar", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "Actualizar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
