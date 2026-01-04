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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QLabel *labelConfigTitle;
    QGroupBox *groupBoxConfig;
    QGridLayout *gridLayout_config;
    QLabel *labelBaudRate;
    QComboBox *comboBoxBaudRate;
    QLabel *labelUpdateInterval;
    QSpinBox *spinBoxUpdateInterval;
    QSpacerItem *verticalSpacer_config;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_tab2;
    QLabel *labelSensors;
    QGridLayout *gridLayout_sensors;
    QLabel *labelTemp;
    QLabel *labelTempValue;
    QLabel *labelHum;
    QLabel *labelHumValue;
    QLabel *labelLight;
    QLabel *labelLightValue;
    QLabel *labelMotorsControl;
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
    QSpacerItem *verticalSpacer_tab2;
    QWidget *tab3;
    QVBoxLayout *verticalLayout_tab3;
    QLabel *labelPIDTitle;
    QGridLayout *gridLayout_PID;
    QLabel *labelSetpoint;
    QDoubleSpinBox *spinBoxSetpoint;
    QPushButton *btnSetSetpoint;
    QLabel *labelKP;
    QDoubleSpinBox *spinBoxKP;
    QPushButton *btnSetKP;
    QLabel *labelKI;
    QDoubleSpinBox *spinBoxKI;
    QPushButton *btnSetKI;
    QLabel *labelKD;
    QDoubleSpinBox *spinBoxKD;
    QPushButton *btnSetKD;
    QPushButton *btnEnablePID;
    QPushButton *btnDisablePID;
    QLabel *labelPIDStatus;
    QLabel *labelPIDOutput;
    QSpacerItem *verticalSpacer_tab3;
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
        labelConfigTitle = new QLabel(tab1);
        labelConfigTitle->setObjectName("labelConfigTitle");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelConfigTitle->setFont(font);

        verticalLayout_tab1->addWidget(labelConfigTitle);

        groupBoxConfig = new QGroupBox(tab1);
        groupBoxConfig->setObjectName("groupBoxConfig");
        gridLayout_config = new QGridLayout(groupBoxConfig);
        gridLayout_config->setObjectName("gridLayout_config");
        labelBaudRate = new QLabel(groupBoxConfig);
        labelBaudRate->setObjectName("labelBaudRate");

        gridLayout_config->addWidget(labelBaudRate, 0, 0, 1, 1);

        comboBoxBaudRate = new QComboBox(groupBoxConfig);
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->setObjectName("comboBoxBaudRate");

        gridLayout_config->addWidget(comboBoxBaudRate, 0, 1, 1, 1);

        labelUpdateInterval = new QLabel(groupBoxConfig);
        labelUpdateInterval->setObjectName("labelUpdateInterval");

        gridLayout_config->addWidget(labelUpdateInterval, 1, 0, 1, 1);

        spinBoxUpdateInterval = new QSpinBox(groupBoxConfig);
        spinBoxUpdateInterval->setObjectName("spinBoxUpdateInterval");
        spinBoxUpdateInterval->setMinimum(100);
        spinBoxUpdateInterval->setMaximum(5000);
        spinBoxUpdateInterval->setSingleStep(100);
        spinBoxUpdateInterval->setValue(1000);

        gridLayout_config->addWidget(spinBoxUpdateInterval, 1, 1, 1, 1);


        verticalLayout_tab1->addWidget(groupBoxConfig);

        verticalSpacer_config = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_tab1->addItem(verticalSpacer_config);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        verticalLayout_tab2 = new QVBoxLayout(tab2);
        verticalLayout_tab2->setObjectName("verticalLayout_tab2");
        labelSensors = new QLabel(tab2);
        labelSensors->setObjectName("labelSensors");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        labelSensors->setFont(font1);

        verticalLayout_tab2->addWidget(labelSensors);

        gridLayout_sensors = new QGridLayout();
        gridLayout_sensors->setObjectName("gridLayout_sensors");
        labelTemp = new QLabel(tab2);
        labelTemp->setObjectName("labelTemp");

        gridLayout_sensors->addWidget(labelTemp, 0, 0, 1, 1);

        labelTempValue = new QLabel(tab2);
        labelTempValue->setObjectName("labelTempValue");
        labelTempValue->setFont(font);

        gridLayout_sensors->addWidget(labelTempValue, 0, 1, 1, 1);

        labelHum = new QLabel(tab2);
        labelHum->setObjectName("labelHum");

        gridLayout_sensors->addWidget(labelHum, 1, 0, 1, 1);

        labelHumValue = new QLabel(tab2);
        labelHumValue->setObjectName("labelHumValue");
        labelHumValue->setFont(font);

        gridLayout_sensors->addWidget(labelHumValue, 1, 1, 1, 1);

        labelLight = new QLabel(tab2);
        labelLight->setObjectName("labelLight");

        gridLayout_sensors->addWidget(labelLight, 2, 0, 1, 1);

        labelLightValue = new QLabel(tab2);
        labelLightValue->setObjectName("labelLightValue");
        labelLightValue->setFont(font);

        gridLayout_sensors->addWidget(labelLightValue, 2, 1, 1, 1);


        verticalLayout_tab2->addLayout(gridLayout_sensors);

        labelMotorsControl = new QLabel(tab2);
        labelMotorsControl->setObjectName("labelMotorsControl");
        labelMotorsControl->setFont(font1);

        verticalLayout_tab2->addWidget(labelMotorsControl);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        btn1_1 = new QPushButton(tab2);
        btn1_1->setObjectName("btn1_1");

        gridLayout_4->addWidget(btn1_1, 0, 0, 1, 1);

        btn1_2 = new QPushButton(tab2);
        btn1_2->setObjectName("btn1_2");

        gridLayout_4->addWidget(btn1_2, 0, 1, 1, 1);

        btn1_3 = new QPushButton(tab2);
        btn1_3->setObjectName("btn1_3");

        gridLayout_4->addWidget(btn1_3, 1, 0, 1, 1);

        btn1_4 = new QPushButton(tab2);
        btn1_4->setObjectName("btn1_4");

        gridLayout_4->addWidget(btn1_4, 1, 1, 1, 1);


        verticalLayout_tab2->addLayout(gridLayout_4);

        labelMotors = new QLabel(tab2);
        labelMotors->setObjectName("labelMotors");

        verticalLayout_tab2->addWidget(labelMotors);

        gridLayout_motors = new QGridLayout();
        gridLayout_motors->setObjectName("gridLayout_motors");
        labelMotor1 = new QLabel(tab2);
        labelMotor1->setObjectName("labelMotor1");

        gridLayout_motors->addWidget(labelMotor1, 0, 0, 1, 1);

        sliderMotor1 = new QSlider(tab2);
        sliderMotor1->setObjectName("sliderMotor1");
        sliderMotor1->setMinimum(0);
        sliderMotor1->setMaximum(255);
        sliderMotor1->setValue(0);
        sliderMotor1->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor1, 0, 1, 1, 1);

        spinBoxMotor1 = new QSpinBox(tab2);
        spinBoxMotor1->setObjectName("spinBoxMotor1");
        spinBoxMotor1->setMinimum(0);
        spinBoxMotor1->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor1, 0, 2, 1, 1);

        labelMotor2 = new QLabel(tab2);
        labelMotor2->setObjectName("labelMotor2");

        gridLayout_motors->addWidget(labelMotor2, 1, 0, 1, 1);

        sliderMotor2 = new QSlider(tab2);
        sliderMotor2->setObjectName("sliderMotor2");
        sliderMotor2->setMinimum(0);
        sliderMotor2->setMaximum(255);
        sliderMotor2->setValue(0);
        sliderMotor2->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor2, 1, 1, 1, 1);

        spinBoxMotor2 = new QSpinBox(tab2);
        spinBoxMotor2->setObjectName("spinBoxMotor2");
        spinBoxMotor2->setMinimum(0);
        spinBoxMotor2->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor2, 1, 2, 1, 1);

        labelMotor3 = new QLabel(tab2);
        labelMotor3->setObjectName("labelMotor3");

        gridLayout_motors->addWidget(labelMotor3, 2, 0, 1, 1);

        sliderMotor3 = new QSlider(tab2);
        sliderMotor3->setObjectName("sliderMotor3");
        sliderMotor3->setMinimum(0);
        sliderMotor3->setMaximum(255);
        sliderMotor3->setValue(0);
        sliderMotor3->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_motors->addWidget(sliderMotor3, 2, 1, 1, 1);

        spinBoxMotor3 = new QSpinBox(tab2);
        spinBoxMotor3->setObjectName("spinBoxMotor3");
        spinBoxMotor3->setMinimum(0);
        spinBoxMotor3->setMaximum(255);

        gridLayout_motors->addWidget(spinBoxMotor3, 2, 2, 1, 1);


        verticalLayout_tab2->addLayout(gridLayout_motors);

        verticalSpacer_tab2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_tab2->addItem(verticalSpacer_tab2);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName("tab3");
        verticalLayout_tab3 = new QVBoxLayout(tab3);
        verticalLayout_tab3->setObjectName("verticalLayout_tab3");
        labelPIDTitle = new QLabel(tab3);
        labelPIDTitle->setObjectName("labelPIDTitle");
        labelPIDTitle->setFont(font);

        verticalLayout_tab3->addWidget(labelPIDTitle);

        gridLayout_PID = new QGridLayout();
        gridLayout_PID->setObjectName("gridLayout_PID");
        labelSetpoint = new QLabel(tab3);
        labelSetpoint->setObjectName("labelSetpoint");

        gridLayout_PID->addWidget(labelSetpoint, 0, 0, 1, 1);

        spinBoxSetpoint = new QDoubleSpinBox(tab3);
        spinBoxSetpoint->setObjectName("spinBoxSetpoint");
        spinBoxSetpoint->setDecimals(1);
        spinBoxSetpoint->setMinimum(0.000000000000000);
        spinBoxSetpoint->setMaximum(50.000000000000000);
        spinBoxSetpoint->setValue(25.000000000000000);

        gridLayout_PID->addWidget(spinBoxSetpoint, 0, 1, 1, 1);

        btnSetSetpoint = new QPushButton(tab3);
        btnSetSetpoint->setObjectName("btnSetSetpoint");

        gridLayout_PID->addWidget(btnSetSetpoint, 0, 2, 1, 1);

        labelKP = new QLabel(tab3);
        labelKP->setObjectName("labelKP");

        gridLayout_PID->addWidget(labelKP, 1, 0, 1, 1);

        spinBoxKP = new QDoubleSpinBox(tab3);
        spinBoxKP->setObjectName("spinBoxKP");
        spinBoxKP->setDecimals(2);
        spinBoxKP->setMinimum(0.000000000000000);
        spinBoxKP->setMaximum(100.000000000000000);
        spinBoxKP->setValue(2.000000000000000);

        gridLayout_PID->addWidget(spinBoxKP, 1, 1, 1, 1);

        btnSetKP = new QPushButton(tab3);
        btnSetKP->setObjectName("btnSetKP");

        gridLayout_PID->addWidget(btnSetKP, 1, 2, 1, 1);

        labelKI = new QLabel(tab3);
        labelKI->setObjectName("labelKI");

        gridLayout_PID->addWidget(labelKI, 2, 0, 1, 1);

        spinBoxKI = new QDoubleSpinBox(tab3);
        spinBoxKI->setObjectName("spinBoxKI");
        spinBoxKI->setDecimals(2);
        spinBoxKI->setMinimum(0.000000000000000);
        spinBoxKI->setMaximum(100.000000000000000);
        spinBoxKI->setValue(0.500000000000000);

        gridLayout_PID->addWidget(spinBoxKI, 2, 1, 1, 1);

        btnSetKI = new QPushButton(tab3);
        btnSetKI->setObjectName("btnSetKI");

        gridLayout_PID->addWidget(btnSetKI, 2, 2, 1, 1);

        labelKD = new QLabel(tab3);
        labelKD->setObjectName("labelKD");

        gridLayout_PID->addWidget(labelKD, 3, 0, 1, 1);

        spinBoxKD = new QDoubleSpinBox(tab3);
        spinBoxKD->setObjectName("spinBoxKD");
        spinBoxKD->setDecimals(2);
        spinBoxKD->setMinimum(0.000000000000000);
        spinBoxKD->setMaximum(100.000000000000000);
        spinBoxKD->setValue(1.000000000000000);

        gridLayout_PID->addWidget(spinBoxKD, 3, 1, 1, 1);

        btnSetKD = new QPushButton(tab3);
        btnSetKD->setObjectName("btnSetKD");

        gridLayout_PID->addWidget(btnSetKD, 3, 2, 1, 1);

        btnEnablePID = new QPushButton(tab3);
        btnEnablePID->setObjectName("btnEnablePID");

        gridLayout_PID->addWidget(btnEnablePID, 4, 0, 1, 1);

        btnDisablePID = new QPushButton(tab3);
        btnDisablePID->setObjectName("btnDisablePID");

        gridLayout_PID->addWidget(btnDisablePID, 4, 1, 1, 1);


        verticalLayout_tab3->addLayout(gridLayout_PID);

        labelPIDStatus = new QLabel(tab3);
        labelPIDStatus->setObjectName("labelPIDStatus");
        QFont font2;
        font2.setPointSize(10);
        labelPIDStatus->setFont(font2);

        verticalLayout_tab3->addWidget(labelPIDStatus);

        labelPIDOutput = new QLabel(tab3);
        labelPIDOutput->setObjectName("labelPIDOutput");
        labelPIDOutput->setFont(font2);

        verticalLayout_tab3->addWidget(labelPIDOutput);

        verticalSpacer_tab3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_tab3->addItem(verticalSpacer_tab3);

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
        QFont font3;
        font3.setFamilies({QString::fromUtf8("monospace")});
        font3.setPointSize(9);
        consoleTextEdit->setFont(font3);
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
        labelConfigTitle->setText(QCoreApplication::translate("MainWindow", "Configuraci\303\263n del Microcontrolador", nullptr));
        groupBoxConfig->setTitle(QCoreApplication::translate("MainWindow", "Par\303\241metros Generales", nullptr));
        labelBaudRate->setText(QCoreApplication::translate("MainWindow", "Velocidad Serial:", nullptr));
        comboBoxBaudRate->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBoxBaudRate->setItemText(1, QCoreApplication::translate("MainWindow", "19200", nullptr));
        comboBoxBaudRate->setItemText(2, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBoxBaudRate->setItemText(3, QCoreApplication::translate("MainWindow", "57600", nullptr));
        comboBoxBaudRate->setItemText(4, QCoreApplication::translate("MainWindow", "115200", nullptr));

        labelUpdateInterval->setText(QCoreApplication::translate("MainWindow", "Intervalo de Actualizaci\303\263n (ms):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
        labelSensors->setText(QCoreApplication::translate("MainWindow", "M\303\251tricas de Sensores:", nullptr));
        labelTemp->setText(QCoreApplication::translate("MainWindow", "Temperatura:", nullptr));
        labelTempValue->setText(QCoreApplication::translate("MainWindow", "-- \302\260C", nullptr));
        labelHum->setText(QCoreApplication::translate("MainWindow", "Humedad:", nullptr));
        labelHumValue->setText(QCoreApplication::translate("MainWindow", "-- %", nullptr));
        labelLight->setText(QCoreApplication::translate("MainWindow", "Luz:", nullptr));
        labelLightValue->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        labelMotorsControl->setText(QCoreApplication::translate("MainWindow", "Control de Motores:", nullptr));
        btn1_1->setText(QCoreApplication::translate("MainWindow", "Iniciar/Detener Motores (Auto)", nullptr));
        btn1_2->setText(QCoreApplication::translate("MainWindow", "Control Manual", nullptr));
        btn1_3->setText(QCoreApplication::translate("MainWindow", "Aumentar intervalo", nullptr));
        btn1_4->setText(QCoreApplication::translate("MainWindow", "Disminuir Intervalo", nullptr));
        labelMotors->setText(QCoreApplication::translate("MainWindow", "Control Individual de Motores:", nullptr));
        labelMotor1->setText(QCoreApplication::translate("MainWindow", "Motor 1 (Pin 4):", nullptr));
        labelMotor2->setText(QCoreApplication::translate("MainWindow", "Motor 2 (Pin 16):", nullptr));
        labelMotor3->setText(QCoreApplication::translate("MainWindow", "Motor 3 (Pin 17):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "Control", nullptr));
        labelPIDTitle->setText(QCoreApplication::translate("MainWindow", "Controlador PID de Temperatura", nullptr));
        labelSetpoint->setText(QCoreApplication::translate("MainWindow", "Setpoint de Temperatura:", nullptr));
        spinBoxSetpoint->setSuffix(QCoreApplication::translate("MainWindow", " \302\260C", nullptr));
        btnSetSetpoint->setText(QCoreApplication::translate("MainWindow", "Establecer", nullptr));
        labelKP->setText(QCoreApplication::translate("MainWindow", "Kp (Proporcional):", nullptr));
        btnSetKP->setText(QCoreApplication::translate("MainWindow", "Establecer", nullptr));
        labelKI->setText(QCoreApplication::translate("MainWindow", "Ki (Integral):", nullptr));
        btnSetKI->setText(QCoreApplication::translate("MainWindow", "Establecer", nullptr));
        labelKD->setText(QCoreApplication::translate("MainWindow", "Kd (Derivativo):", nullptr));
        btnSetKD->setText(QCoreApplication::translate("MainWindow", "Establecer", nullptr));
        btnEnablePID->setText(QCoreApplication::translate("MainWindow", "Activar PID", nullptr));
        btnDisablePID->setText(QCoreApplication::translate("MainWindow", "Desactivar PID", nullptr));
        labelPIDStatus->setText(QCoreApplication::translate("MainWindow", "Estado del PID: Desactivado", nullptr));
        labelPIDOutput->setText(QCoreApplication::translate("MainWindow", "Salida PID: --", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QCoreApplication::translate("MainWindow", "Control PID", nullptr));
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
