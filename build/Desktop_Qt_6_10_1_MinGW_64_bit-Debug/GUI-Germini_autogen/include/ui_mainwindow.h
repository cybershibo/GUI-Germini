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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QWidget *serialWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPort;
    QComboBox *comboBoxPort;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QPushButton *btnRefresh;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *verticalLayout_tab1;
    QGridLayout *gridLayout_4;
    QPushButton *btn1_1;
    QPushButton *btn1_2;
    QPushButton *btn1_3;
    QPushButton *btn1_4;
    QLabel *labelMotors;
    QGridLayout *gridLayout_motors;
    QLabel *labelMotor1;
    QSlider *sliderMotor1;
    QSpinBox *spinBoxMotor1;
    QLabel *labelMotor2;
    QSlider *sliderMotor2;
    QSpinBox *spinBoxMotor2;
    QLabel *labelMotor3;
    QSlider *sliderMotor3;
    QSpinBox *spinBoxMotor3;
    QSpacerItem *verticalSpacer;
    QWidget *tab2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *btn2_1;
    QPushButton *btn2_2;
    QPushButton *btn2_3;
    QPushButton *btn2_4;
    QWidget *tab3;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QPushButton *btn3_1;
    QPushButton *btn3_2;
    QPushButton *btn3_3;
    QPushButton *btn3_4;
    QWidget *tabGraph;
    QVBoxLayout *verticalLayout_2;
    QWidget *chartWidget;
    QWidget *tabConsole;
    QVBoxLayout *verticalLayout_console;
    QPlainTextEdit *consoleTextEdit;
    QHBoxLayout *horizontalLayout_console;
    QPushButton *btnClearConsole;
    QCheckBox *checkBoxAutoScroll;
    QSpacerItem *horizontalSpacer_console;
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


        gridLayout->addWidget(serialWidget, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(988, 0));
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        verticalLayout_tab1 = new QVBoxLayout(tab1);
        verticalLayout_tab1->setObjectName("verticalLayout_tab1");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        btn1_1 = new QPushButton(tab1);
        btn1_1->setObjectName("btn1_1");

        gridLayout_4->addWidget(btn1_1, 0, 0, 1, 1);

        btn1_2 = new QPushButton(tab1);
        btn1_2->setObjectName("btn1_2");

        gridLayout_4->addWidget(btn1_2, 0, 1, 1, 1);

        btn1_3 = new QPushButton(tab1);
        btn1_3->setObjectName("btn1_3");

        gridLayout_4->addWidget(btn1_3, 1, 0, 1, 1);

        btn1_4 = new QPushButton(tab1);
        btn1_4->setObjectName("btn1_4");

        gridLayout_4->addWidget(btn1_4, 1, 1, 1, 1);


        verticalLayout_tab1->addLayout(gridLayout_4);

        labelMotors = new QLabel(tab1);
        labelMotors->setObjectName("labelMotors");

        verticalLayout_tab1->addWidget(labelMotors);

        gridLayout_motors = new QGridLayout();
        gridLayout_motors->setObjectName("gridLayout_motors");
        labelMotor1 = new QLabel(tab1);
        labelMotor1->setObjectName("labelMotor1");

        gridLayout_motors->addWidget(labelMotor1, 0, 0, 1, 1);

        sliderMotor1 = new QSlider(tab1);
        sliderMotor1->setObjectName("sliderMotor1");
        sliderMotor1->setMinimum(0);
        sliderMotor1->setMaximum(255);
        sliderMotor1->setValue(0);
        sliderMotor1->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor1, 0, 1, 1, 1);

        spinBoxMotor1 = new QSpinBox(tab1);
        spinBoxMotor1->setObjectName("spinBoxMotor1");
        spinBoxMotor1->setMinimum(0);
        spinBoxMotor1->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor1, 0, 2, 1, 1);

        labelMotor2 = new QLabel(tab1);
        labelMotor2->setObjectName("labelMotor2");

        gridLayout_motors->addWidget(labelMotor2, 1, 0, 1, 1);

        sliderMotor2 = new QSlider(tab1);
        sliderMotor2->setObjectName("sliderMotor2");
        sliderMotor2->setMinimum(0);
        sliderMotor2->setMaximum(255);
        sliderMotor2->setValue(0);
        sliderMotor2->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor2, 1, 1, 1, 1);

        spinBoxMotor2 = new QSpinBox(tab1);
        spinBoxMotor2->setObjectName("spinBoxMotor2");
        spinBoxMotor2->setMinimum(0);
        spinBoxMotor2->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor2, 1, 2, 1, 1);

        labelMotor3 = new QLabel(tab1);
        labelMotor3->setObjectName("labelMotor3");

        gridLayout_motors->addWidget(labelMotor3, 2, 0, 1, 1);

        sliderMotor3 = new QSlider(tab1);
        sliderMotor3->setObjectName("sliderMotor3");
        sliderMotor3->setMinimum(0);
        sliderMotor3->setMaximum(255);
        sliderMotor3->setValue(0);
        sliderMotor3->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor3, 2, 1, 1, 1);

        spinBoxMotor3 = new QSpinBox(tab1);
        spinBoxMotor3->setObjectName("spinBoxMotor3");
        spinBoxMotor3->setMinimum(0);
        spinBoxMotor3->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor3, 2, 2, 1, 1);


        verticalLayout_tab1->addLayout(gridLayout_motors);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_tab1->addItem(verticalSpacer);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        layoutWidget = new QWidget(tab2);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(200, 100, 166, 42));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        btn2_1 = new QPushButton(layoutWidget);
        btn2_1->setObjectName("btn2_1");

        gridLayout_2->addWidget(btn2_1, 0, 0, 1, 1);

        btn2_2 = new QPushButton(layoutWidget);
        btn2_2->setObjectName("btn2_2");

        gridLayout_2->addWidget(btn2_2, 0, 1, 1, 1);

        btn2_3 = new QPushButton(layoutWidget);
        btn2_3->setObjectName("btn2_3");

        gridLayout_2->addWidget(btn2_3, 1, 0, 1, 1);

        btn2_4 = new QPushButton(layoutWidget);
        btn2_4->setObjectName("btn2_4");

        gridLayout_2->addWidget(btn2_4, 1, 1, 1, 1);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName("tab3");
        layoutWidget1 = new QWidget(tab3);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(230, 100, 166, 42));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        btn3_1 = new QPushButton(layoutWidget1);
        btn3_1->setObjectName("btn3_1");

        gridLayout_3->addWidget(btn3_1, 0, 0, 1, 1);

        btn3_2 = new QPushButton(layoutWidget1);
        btn3_2->setObjectName("btn3_2");

        gridLayout_3->addWidget(btn3_2, 0, 1, 1, 1);

        btn3_3 = new QPushButton(layoutWidget1);
        btn3_3->setObjectName("btn3_3");

        gridLayout_3->addWidget(btn3_3, 1, 0, 1, 1);

        btn3_4 = new QPushButton(layoutWidget1);
        btn3_4->setObjectName("btn3_4");

        gridLayout_3->addWidget(btn3_4, 1, 1, 1, 1);

        tabWidget->addTab(tab3, QString());
        tabGraph = new QWidget();
        tabGraph->setObjectName("tabGraph");
        verticalLayout_2 = new QVBoxLayout(tabGraph);
        verticalLayout_2->setObjectName("verticalLayout_2");
        chartWidget = new QWidget(tabGraph);
        chartWidget->setObjectName("chartWidget");

        verticalLayout_2->addWidget(chartWidget);

        tabWidget->addTab(tabGraph, QString());
        tabConsole = new QWidget();
        tabConsole->setObjectName("tabConsole");
        verticalLayout_console = new QVBoxLayout(tabConsole);
        verticalLayout_console->setObjectName("verticalLayout_console");
        consoleTextEdit = new QPlainTextEdit(tabConsole);
        consoleTextEdit->setObjectName("consoleTextEdit");
        QFont font;
        font.setFamilies({QString::fromUtf8("monospace")});
        font.setPointSize(9);
        consoleTextEdit->setFont(font);
        consoleTextEdit->setReadOnly(true);

        verticalLayout_console->addWidget(consoleTextEdit);

        horizontalLayout_console = new QHBoxLayout();
        horizontalLayout_console->setObjectName("horizontalLayout_console");
        btnClearConsole = new QPushButton(tabConsole);
        btnClearConsole->setObjectName("btnClearConsole");

        horizontalLayout_console->addWidget(btnClearConsole);

        checkBoxAutoScroll = new QCheckBox(tabConsole);
        checkBoxAutoScroll->setObjectName("checkBoxAutoScroll");
        checkBoxAutoScroll->setChecked(true);

        horizontalLayout_console->addWidget(checkBoxAutoScroll);

        horizontalSpacer_console = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_console->addItem(horizontalSpacer_console);


        verticalLayout_console->addLayout(horizontalLayout_console);

        tabWidget->addTab(tabConsole, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Germini Control Panel", nullptr));
        labelPort->setText(QCoreApplication::translate("MainWindow", "Puerto:", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Desconectar", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "Actualizar", nullptr));
        btn1_1->setText(QCoreApplication::translate("MainWindow", "Iniciar/Detener Motores (Auto)", nullptr));
        btn1_2->setText(QCoreApplication::translate("MainWindow", "Control Manual", nullptr));
        btn1_3->setText(QCoreApplication::translate("MainWindow", "Aumentar intervalo", nullptr));
        btn1_4->setText(QCoreApplication::translate("MainWindow", "Disminuir Intervalo", nullptr));
        labelMotors->setText(QCoreApplication::translate("MainWindow", "Control Individual de Motores:", nullptr));
        labelMotor1->setText(QCoreApplication::translate("MainWindow", "Motor 1 (Pin 4):", nullptr));
        labelMotor2->setText(QCoreApplication::translate("MainWindow", "Motor 2 (Pin 16):", nullptr));
        labelMotor3->setText(QCoreApplication::translate("MainWindow", "Motor 3 (Pin 17):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Control de motores", nullptr));
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
        tabWidget->setTabText(tabWidget->indexOf(tabGraph), QCoreApplication::translate("MainWindow", "Graph", nullptr));
        btnClearConsole->setText(QCoreApplication::translate("MainWindow", "Limpiar Consola", nullptr));
        checkBoxAutoScroll->setText(QCoreApplication::translate("MainWindow", "Auto-scroll", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabConsole), QCoreApplication::translate("MainWindow", "Consola", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
