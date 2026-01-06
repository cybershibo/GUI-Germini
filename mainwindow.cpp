#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QSlider>
#include <QSpinBox>
#include <QDateTime>
#include <QTextCursor>
#include <QRegularExpression>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialPort(nullptr)
    , chart(nullptr)
    , seriesTemperature1(nullptr)
    , seriesTemperature2(nullptr)
    , seriesTemperatureAvg(nullptr)
    , seriesHumidity1(nullptr)
    , seriesHumidity2(nullptr)
    , seriesHumidityAvg(nullptr)
    , seriesLight(nullptr)
    , axisX(nullptr)
    , axisY(nullptr)
    , graphTimer(nullptr)
    , currentTemperature1(0.0)
    , currentTemperature2(0.0)
    , currentTemperatureAvg(0.0)
    , currentHumidity1(0.0)
    , currentHumidity2(0.0)
    , currentHumidityAvg(0.0)
    , currentLight(0.0)
    , pointCount(0)
    , serialBuffer("")
{
    ui->setupUi(this);

    // Inicializar puerto serial
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);

    // Configurar gráfico
    setupChart();

    // Conectar botones de serial
    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &MainWindow::onRefreshPorts);

    // Conectar todos los botones de las pestañas
    connectAllButtons();
    
    // Conectar controles de motores
    connect(ui->sliderMotor1, &QSlider::valueChanged, this, [this](int value) {
        ui->spinBoxMotor1->setValue(value);
        onMotorSliderChanged(1, value);
    });
    connect(ui->sliderMotor2, &QSlider::valueChanged, this, [this](int value) {
        ui->spinBoxMotor2->setValue(value);
        onMotorSliderChanged(2, value);
    });
    connect(ui->sliderMotor3, &QSlider::valueChanged, this, [this](int value) {
        ui->spinBoxMotor3->setValue(value);
        onMotorSliderChanged(3, value);
    });
    
    connect(ui->spinBoxMotor1, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        ui->sliderMotor1->setValue(value);
        onMotorSpinBoxChanged(1, value);
    });
    connect(ui->spinBoxMotor2, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        ui->sliderMotor2->setValue(value);
        onMotorSpinBoxChanged(2, value);
    });
    connect(ui->spinBoxMotor3, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        ui->sliderMotor3->setValue(value);
        onMotorSpinBoxChanged(3, value);
    });
    
    // Conectar botón de limpiar consola
    connect(ui->btnClearConsole, &QPushButton::clicked, this, &MainWindow::onClearConsole);
    
    // Conectar checkboxes de variables del gráfico para selección dinámica
    connect(ui->checkBoxTemp1, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxTemp2, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxTempAvg, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxHum1, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxHum2, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxHumAvg, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    connect(ui->checkBoxLight, &QCheckBox::toggled, this, &MainWindow::onVariableCheckboxChanged);
    
    // Conectar botón de exportar CSV
    connect(ui->btnExportCSV, &QPushButton::clicked, this, &MainWindow::onExportCSV);
    
    // Conectar controles PID
    connect(ui->btnSetSetpoint, &QPushButton::clicked, this, &MainWindow::onSetSetpoint);
    connect(ui->btnSetKP, &QPushButton::clicked, this, &MainWindow::onSetKP);
    connect(ui->btnSetKI, &QPushButton::clicked, this, &MainWindow::onSetKI);
    connect(ui->btnSetKD, &QPushButton::clicked, this, &MainWindow::onSetKD);
    connect(ui->btnEnablePID, &QPushButton::clicked, this, &MainWindow::onEnablePID);
    connect(ui->btnDisablePID, &QPushButton::clicked, this, &MainWindow::onDisablePID);

    // Actualizar puertos disponibles
    refreshSerialPorts();
    
    // Establecer baudrate por defecto a 115200 (más común para ESP32)
    ui->comboBoxBaudRate->setCurrentText("115200");
    
    // Mensaje inicial en la consola
    appendToConsole("Sistema iniciado. Esperando conexión...", "INFO");

    // Inicializar estado de desconexión
    ui->btnDisconnect->setEnabled(false);
    
    // Deshabilitar todas las pestañas excepto Configuración al inicio
    setTabsEnabled(false);
}

MainWindow::~MainWindow()
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
    }
    delete ui;
}

void MainWindow::setupChart()
{
    chart = new QChart();
    
    // Crear series para temperatura (ambos sensores y promedio)
    seriesTemperature1 = new QLineSeries();
    seriesTemperature1->setName("Temp DHT22 #1 (°C)");
    seriesTemperature1->setColor(Qt::red);
    
    seriesTemperature2 = new QLineSeries();
    seriesTemperature2->setName("Temp DHT22 #2 (°C)");
    seriesTemperature2->setColor(Qt::magenta);
    
    seriesTemperatureAvg = new QLineSeries();
    seriesTemperatureAvg->setName("Temp Promedio (°C)");
    seriesTemperatureAvg->setColor(Qt::darkRed);
    
    // Crear series para humedad (ambos sensores y promedio)
    seriesHumidity1 = new QLineSeries();
    seriesHumidity1->setName("Hum DHT22 #1 (%)");
    seriesHumidity1->setColor(Qt::blue);
    
    seriesHumidity2 = new QLineSeries();
    seriesHumidity2->setName("Hum DHT22 #2 (%)");
    seriesHumidity2->setColor(Qt::cyan);
    
    seriesHumidityAvg = new QLineSeries();
    seriesHumidityAvg->setName("Hum Promedio (%)");
    seriesHumidityAvg->setColor(Qt::darkBlue);
    
    // Crear serie para luz
    seriesLight = new QLineSeries();
    seriesLight->setName("Luz");
    seriesLight->setColor(Qt::green);

    // Agregar todas las series al gráfico
    chart->addSeries(seriesTemperature1);
    chart->addSeries(seriesTemperature2);
    chart->addSeries(seriesTemperatureAvg);
    chart->addSeries(seriesHumidity1);
    chart->addSeries(seriesHumidity2);
    chart->addSeries(seriesHumidityAvg);
    chart->addSeries(seriesLight);
    chart->setTitle("Sensores DHT22 en Tiempo Real");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX = new QValueAxis();
    axisX->setTitleText("Tiempo (segundos)");
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesTemperature1->attachAxis(axisX);
    seriesTemperature2->attachAxis(axisX);
    seriesTemperatureAvg->attachAxis(axisX);
    seriesHumidity1->attachAxis(axisX);
    seriesHumidity2->attachAxis(axisX);
    seriesHumidityAvg->attachAxis(axisX);
    seriesLight->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Valor");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesTemperature1->attachAxis(axisY);
    seriesTemperature2->attachAxis(axisY);
    seriesTemperatureAvg->attachAxis(axisY);
    seriesHumidity1->attachAxis(axisY);
    seriesHumidity2->attachAxis(axisY);
    seriesHumidityAvg->attachAxis(axisY);
    seriesLight->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Crear QChartView y agregarlo al widget
    chartView = new QChartView(chart, ui->chartWidget);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    // Configurar layout para el widget del gráfico
    QVBoxLayout *chartLayout = new QVBoxLayout(ui->chartWidget);
    chartLayout->setContentsMargins(0, 0, 0, 0);
    chartLayout->addWidget(chartView);

    // Timer para actualizar el gráfico
    graphTimer = new QTimer(this);
    connect(graphTimer, &QTimer::timeout, this, &MainWindow::updateGraph);
    startTime = QDateTime::currentDateTime();
    
    // Establecer visibilidad inicial según checkboxes
    onVariableCheckboxChanged();
}

void MainWindow::connectAllButtons()
{
    // Tab 2 (Control) - Los botones btn1_1, btn1_2, btn1_3, btn1_4 están ahora en la pestaña de Control
    connect(ui->btn1_1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    
    // Nota: Los botones btn2_x y btn3_x fueron eliminados al reorganizar las pestañas
    // La pestaña 1 ahora es Configuración (sin botones)
    // La pestaña 2 es Control (con btn1_x)
    // La pestaña 3 es PID (con controles propios conectados en el constructor)
}

void MainWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString buttonName = button->objectName();
    QString command;

    // Generar comando basado en el botón presionado
    if (buttonName.startsWith("btn1_")) {
        command = "CMD1_" + buttonName.right(1);
    } else if (buttonName.startsWith("btn2_")) {
        command = "CMD2_" + buttonName.right(1);
    } else if (buttonName.startsWith("btn3_")) {
        command = "CMD3_" + buttonName.right(1);
    } else if (buttonName.startsWith("btn4_")) {
        command = "CMD4_" + buttonName.right(1);
    }

    sendCommand(command);
    ui->statusbar->showMessage("Comando enviado: " + command, 2000);
}

void MainWindow::onConnectClicked()
{
    // Obtener el nombre del puerto desde los datos del combo box
    QVariant portData = ui->comboBoxPort->currentData();
    QString portName;
    
    if (portData.isValid() && !portData.toString().isEmpty()) {
        portName = portData.toString();
    } else {
        // Fallback: extraer el nombre del puerto del texto (formato: "COM3 - USB Serial")
        QString fullText = ui->comboBoxPort->currentText();
        int spaceIndex = fullText.indexOf(" - ");
        if (spaceIndex > 0) {
            portName = fullText.left(spaceIndex).trimmed();
        } else {
            portName = fullText.trimmed();
        }
    }
    
    if (portName.isEmpty() || portName == "No hay puertos disponibles") {
        QMessageBox::warning(this, "Advertencia", "Por favor seleccione un puerto serial válido.");
        return;
    }

    // Verificar que el puerto existe antes de intentar abrirlo
    bool portExists = false;
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        if (port.portName() == portName) {
            portExists = true;
            break;
        }
    }
    
    if (!portExists) {
        QMessageBox::warning(this, "Error", 
            QString("El puerto %1 ya no está disponible. Por favor actualice la lista de puertos.").arg(portName));
        refreshSerialPorts();
        return;
    }

    // Cerrar el puerto si ya está abierto
    if (serialPort->isOpen()) {
        serialPort->close();
    }

    // Obtener el baudrate seleccionado del comboBox
    QString baudRateText = ui->comboBoxBaudRate->currentText();
    bool ok;
    int baudRateValue = baudRateText.toInt(&ok);
    
    // Convertir a QSerialPort::BaudRate
    QSerialPort::BaudRate baudRate = QSerialPort::Baud115200; // Valor por defecto
    if (ok) {
        switch (baudRateValue) {
            case 9600:
                baudRate = QSerialPort::Baud9600;
                break;
            case 19200:
                baudRate = QSerialPort::Baud19200;
                break;
            case 38400:
                baudRate = QSerialPort::Baud38400;
                break;
            case 57600:
                baudRate = QSerialPort::Baud57600;
                break;
            case 115200:
                baudRate = QSerialPort::Baud115200;
                break;
            default:
                baudRate = QSerialPort::Baud115200;
                break;
        }
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        ui->btnConnect->setEnabled(false);
        ui->btnDisconnect->setEnabled(true);
        ui->comboBoxPort->setEnabled(false);
        ui->comboBoxBaudRate->setEnabled(false); // Deshabilitar comboBox de baudrate cuando está conectado
        ui->statusbar->showMessage(QString("Conectado a %1 a %2 baudios").arg(portName).arg(baudRateText), 2000);
        graphTimer->start(100); // Actualizar gráfico cada 100ms
        appendToConsole(QString("Conectado a %1 a %2 baudios").arg(portName).arg(baudRateText), "INFO");
        
        // Habilitar todas las pestañas cuando se conecta
        setTabsEnabled(true);
    } else {
        QString errorMsg = QString("No se pudo abrir el puerto serial %1.\n\nError: %2\n\n"
                                   "Asegúrese de que:\n"
                                   "- El puerto no esté siendo usado por otra aplicación\n"
                                   "- El ESP32 esté correctamente conectado\n"
                                   "- Tenga permisos para acceder al puerto")
                          .arg(portName, serialPort->errorString());
        QMessageBox::critical(this, "Error de Conexión", errorMsg);
    }
}

void MainWindow::onDisconnectClicked()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->btnConnect->setEnabled(true);
        ui->btnDisconnect->setEnabled(false);
        ui->comboBoxPort->setEnabled(true);
        ui->comboBoxBaudRate->setEnabled(true); // Habilitar comboBox de baudrate cuando está desconectado
        ui->statusbar->showMessage("Desconectado", 2000);
        graphTimer->stop();
        appendToConsole("Desconectado del puerto serial", "INFO");
        
        // Deshabilitar todas las pestañas excepto Configuración cuando se desconecta
        setTabsEnabled(false);
        
        // Cambiar a la pestaña de Configuración si estaba en otra
        ui->tabWidget->setCurrentIndex(0);
    }
}

void MainWindow::onRefreshPorts()
{
    refreshSerialPorts();
}

void MainWindow::refreshSerialPorts()
{
    ui->comboBoxPort->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString portInfo = port.portName() + " - " + port.description();
        ui->comboBoxPort->addItem(portInfo, port.portName());
    }

    if (ui->comboBoxPort->count() == 0) {
        ui->comboBoxPort->addItem("No hay puertos disponibles");
    }
}

void MainWindow::onSerialDataReceived()
{
    if (!serialPort || !serialPort->isOpen()) return;

    QByteArray data = serialPort->readAll();
    QString newData = QString::fromUtf8(data);
    
    // Agregar nuevos datos al buffer (pueden llegar fragmentados)
    serialBuffer += newData;
    
    // Procesar líneas completas (terminadas con \n o \r\n)
    QStringList lines = serialBuffer.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);
    
    // Mantener la última línea incompleta en el buffer
    if (serialBuffer.endsWith('\n') || serialBuffer.endsWith('\r')) {
        serialBuffer.clear();
    } else if (lines.size() > 0) {
        // Guardar la última línea incompleta
        serialBuffer = lines.last();
        lines.removeLast();
    }
    
    // Procesar cada línea completa
    for (const QString &line : lines) {
        QString dataString = line.trimmed();
        
        if (dataString.isEmpty()) continue;
        
        // Mostrar en consola todos los datos recibidos
        appendToConsole(dataString, "RX");
        
        // Detectar errores de lectura de sensores
        if (dataString.contains("Error leyendo DHT22 #1", Qt::CaseInsensitive)) {
            // Error en sensor 1: establecer valores en 0
            currentTemperature1 = 0.0;
            currentHumidity1 = 0.0;
            // Si ambos sensores fallan, el promedio también es 0
            if (currentTemperature2 == 0.0 && currentHumidity2 == 0.0) {
                currentTemperatureAvg = 0.0;
                currentHumidityAvg = 0.0;
            } else {
                // Si solo el sensor 1 falla, usar el sensor 2 como promedio
                currentTemperatureAvg = currentTemperature2;
                currentHumidityAvg = currentHumidity2;
            }
            updateSensorMetrics();
            updateGraph();
            continue;
        }
        
        if (dataString.contains("Error leyendo DHT22 #2", Qt::CaseInsensitive)) {
            // Error en sensor 2: establecer valores en 0
            currentTemperature2 = 0.0;
            currentHumidity2 = 0.0;
            // Si ambos sensores fallan, el promedio también es 0
            if (currentTemperature1 == 0.0 && currentHumidity1 == 0.0) {
                currentTemperatureAvg = 0.0;
                currentHumidityAvg = 0.0;
            } else {
                // Si solo el sensor 2 falla, usar el sensor 1 como promedio
                currentTemperatureAvg = currentTemperature1;
                currentHumidityAvg = currentHumidity1;
            }
            updateSensorMetrics();
            updateGraph();
            continue;
        }
        
        // Procesar datos recibidos de ambos DHT22 y sensor de luz
        // Formato esperado: "DATA:TEMP1:XX.XX:TEMP2:XX.XX:TEMPAVG:XX.XX:HUM1:XX.XX:HUM2:XX.XX:HUMAVG:XX.XX:LIGHT:XXX"
        if (dataString.startsWith("DATA:TEMP1:")) {
            bool ok;
            // Extraer temperatura sensor 1
            int temp1Start = 11; // "DATA:TEMP1:" tiene 11 caracteres
            int temp1End = dataString.indexOf(":TEMP2:", temp1Start);
            if (temp1End > temp1Start) {
                QString temp1Str = dataString.mid(temp1Start, temp1End - temp1Start);
                double temp1 = temp1Str.toDouble(&ok);
                if (ok && temp1 > -50 && temp1 < 100 && !temp1Str.contains("nan", Qt::CaseInsensitive)) {
                    currentTemperature1 = temp1;
                } else {
                    // Error: establecer en 0
                    currentTemperature1 = 0.0;
                }
                
                // Extraer temperatura sensor 2
                int temp2Start = temp1End + 7; // ":TEMP2:" tiene 7 caracteres
                int temp2End = dataString.indexOf(":TEMPAVG:", temp2Start);
                if (temp2End > temp2Start) {
                    QString temp2Str = dataString.mid(temp2Start, temp2End - temp2Start);
                    double temp2 = temp2Str.toDouble(&ok);
                    if (ok && temp2 > -50 && temp2 < 100 && !temp2Str.contains("nan", Qt::CaseInsensitive)) {
                        currentTemperature2 = temp2;
                    } else {
                        // Error: establecer en 0
                        currentTemperature2 = 0.0;
                    }
                    
                    // Extraer temperatura promedio
                    int tempAvgStart = temp2End + 9; // ":TEMPAVG:" tiene 9 caracteres
                    int tempAvgEnd = dataString.indexOf(":HUM1:", tempAvgStart);
                    if (tempAvgEnd > tempAvgStart) {
                        QString tempAvgStr = dataString.mid(tempAvgStart, tempAvgEnd - tempAvgStart);
                        double tempAvg = tempAvgStr.toDouble(&ok);
                        if (ok && tempAvg > -50 && tempAvg < 100 && !tempAvgStr.contains("nan", Qt::CaseInsensitive)) {
                            currentTemperatureAvg = tempAvg;
                        } else {
                            // Error: establecer en 0
                            currentTemperatureAvg = 0.0;
                        }
                        
                        // Extraer humedad sensor 1
                        int hum1Start = tempAvgEnd + 6; // ":HUM1:" tiene 6 caracteres
                        int hum1End = dataString.indexOf(":HUM2:", hum1Start);
                        if (hum1End > hum1Start) {
                            QString hum1Str = dataString.mid(hum1Start, hum1End - hum1Start);
                            double hum1 = hum1Str.toDouble(&ok);
                            if (ok && hum1 >= 0 && hum1 <= 100 && !hum1Str.contains("nan", Qt::CaseInsensitive)) {
                                currentHumidity1 = hum1;
                            } else {
                                // Error: establecer en 0
                                currentHumidity1 = 0.0;
                            }
                            
                            // Extraer humedad sensor 2
                            int hum2Start = hum1End + 6; // ":HUM2:" tiene 6 caracteres
                            int hum2End = dataString.indexOf(":HUMAVG:", hum2Start);
                            if (hum2End > hum2Start) {
                                QString hum2Str = dataString.mid(hum2Start, hum2End - hum2Start);
                                double hum2 = hum2Str.toDouble(&ok);
                                if (ok && hum2 >= 0 && hum2 <= 100 && !hum2Str.contains("nan", Qt::CaseInsensitive)) {
                                    currentHumidity2 = hum2;
                                } else {
                                    // Error: establecer en 0
                                    currentHumidity2 = 0.0;
                                }
                                
                                // Extraer humedad promedio
                                int humAvgStart = hum2End + 8; // ":HUMAVG:" tiene 8 caracteres
                                int humAvgEnd = dataString.indexOf(":LIGHT:", humAvgStart);
                                if (humAvgEnd > humAvgStart) {
                                    QString humAvgStr = dataString.mid(humAvgStart, humAvgEnd - humAvgStart);
                                    double humAvg = humAvgStr.toDouble(&ok);
                                    if (ok && humAvg >= 0 && humAvg <= 100 && !humAvgStr.contains("nan", Qt::CaseInsensitive)) {
                                        currentHumidityAvg = humAvg;
                                    } else {
                                        // Error: establecer en 0
                                        currentHumidityAvg = 0.0;
                                    }
                                    
                                    // Extraer luz
                                    int lightStart = humAvgEnd + 7; // ":LIGHT:" tiene 7 caracteres
                                    QString lightStr = dataString.mid(lightStart);
                                    double light = lightStr.toDouble(&ok);
                                    if (ok && light >= 0) {
                                        currentLight = light;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            // Recalcular promedios basándose en valores válidos
            // Si ambos sensores tienen valores válidos (dentro del rango esperado), calcular promedio
            bool temp1Valid = (currentTemperature1 >= -50.0 && currentTemperature1 <= 100.0);
            bool temp2Valid = (currentTemperature2 >= -50.0 && currentTemperature2 <= 100.0);
            
            if (temp1Valid && temp2Valid) {
                currentTemperatureAvg = (currentTemperature1 + currentTemperature2) / 2.0;
            } else if (temp1Valid) {
                currentTemperatureAvg = currentTemperature1;
            } else if (temp2Valid) {
                currentTemperatureAvg = currentTemperature2;
            } else {
                // Ambos sensores fallaron o tienen valores inválidos
                currentTemperatureAvg = 0.0;
            }
            
            bool hum1Valid = (currentHumidity1 >= 0.0 && currentHumidity1 <= 100.0);
            bool hum2Valid = (currentHumidity2 >= 0.0 && currentHumidity2 <= 100.0);
            
            if (hum1Valid && hum2Valid) {
                currentHumidityAvg = (currentHumidity1 + currentHumidity2) / 2.0;
            } else if (hum1Valid) {
                currentHumidityAvg = currentHumidity1;
            } else if (hum2Valid) {
                currentHumidityAvg = currentHumidity2;
            } else {
                // Ambos sensores fallaron o tienen valores inválidos
                currentHumidityAvg = 0.0;
            }
            
            // Actualizar métricas de sensores
            updateSensorMetrics();
            
            ui->statusbar->showMessage(QString("Temp Avg: %1°C, Hum Avg: %2%, Luz: %3")
                .arg(currentTemperatureAvg, 0, 'f', 1)
                .arg(currentHumidityAvg, 0, 'f', 1)
                .arg(currentLight, 0, 'f', 0), 1000);
            
            // Actualizar gráfico inmediatamente cuando se reciben nuevos datos
            updateGraph();
        }
        // Formato legacy para compatibilidad (solo un sensor)
        else if (dataString.startsWith("DATA:TEMP:")) {
            int tempStart = 10;
            int tempEnd = dataString.indexOf(":HUM:");
            if (tempEnd > tempStart) {
                QString tempStr = dataString.mid(tempStart, tempEnd - tempStart);
                bool ok;
                double temp = tempStr.toDouble(&ok);
                if (ok && temp > -50 && temp < 100 && !tempStr.contains("nan", Qt::CaseInsensitive)) {
                    // Asignar a ambos sensores y promedio para compatibilidad
                    currentTemperature1 = temp;
                    currentTemperature2 = temp;
                    currentTemperatureAvg = temp;
                } else {
                    // Error: establecer en 0
                    currentTemperature1 = 0.0;
                    currentTemperature2 = 0.0;
                    currentTemperatureAvg = 0.0;
                }
                
                int humStart = tempEnd + 5;
                int humEnd = dataString.indexOf(":LIGHT:", humStart);
                if (humEnd > humStart) {
                    QString humStr = dataString.mid(humStart, humEnd - humStart);
                    double hum = humStr.toDouble(&ok);
                    if (ok && hum >= 0 && hum <= 100 && !humStr.contains("nan", Qt::CaseInsensitive)) {
                        currentHumidity1 = hum;
                        currentHumidity2 = hum;
                        currentHumidityAvg = hum;
                    } else {
                        // Error: establecer en 0
                        currentHumidity1 = 0.0;
                        currentHumidity2 = 0.0;
                        currentHumidityAvg = 0.0;
                    }
                    
                    int lightStart = humEnd + 7;
                    QString lightStr = dataString.mid(lightStart);
                    double light = lightStr.toDouble(&ok);
                    if (ok && light >= 0) {
                        currentLight = light;
                    }
                }
                
                updateSensorMetrics();
                updateGraph();
            }
        }
        // Procesar salida del PID
        else if (dataString.startsWith("PID_OUTPUT:")) {
            int outputStart = 11; // "PID_OUTPUT:" tiene 11 caracteres
            int outputEnd = dataString.indexOf(" ERROR:");
            if (outputEnd > outputStart) {
                QString outputStr = dataString.mid(outputStart, outputEnd - outputStart);
                bool ok;
                double output = outputStr.toDouble(&ok);
                if (ok) {
                    ui->labelPIDOutput->setText(QString("Salida PID: %1").arg(output, 0, 'f', 1));
                }
            }
        }
        // Procesar estado del PID
        else if (dataString == "PID ACTIVADO") {
            ui->labelPIDStatus->setText("Estado del PID: Activado");
        }
        else if (dataString == "PID DESACTIVADO") {
            ui->labelPIDStatus->setText("Estado del PID: Desactivado");
            ui->labelPIDOutput->setText("Salida PID: --");
        }
        // Formato legacy para compatibilidad
        else if (dataString.startsWith("DATA:")) {
            QString valueStr = dataString.mid(5);
            bool ok;
            double value = valueStr.toDouble(&ok);
            if (ok) {
                // Asignar a ambos sensores y promedio para compatibilidad
                currentTemperature1 = value;
                currentTemperature2 = value;
                currentTemperatureAvg = value;
            }
        }
    }
}

void MainWindow::updateGraph()
{
    if (seriesTemperature1 && seriesTemperature2 && seriesTemperatureAvg && 
        seriesHumidity1 && seriesHumidity2 && seriesHumidityAvg && 
        seriesLight && chart) {
        // Calcular tiempo transcurrido en segundos
        qint64 elapsed = startTime.msecsTo(QDateTime::currentDateTime());
        double timeSeconds = elapsed / 1000.0;

        // Verificar que los valores sean razonables antes de agregarlos
        bool validTemp1 = (currentTemperature1 > -50 && currentTemperature1 < 100);
        bool validTemp2 = (currentTemperature2 > -50 && currentTemperature2 < 100);
        bool validTempAvg = (currentTemperatureAvg > -50 && currentTemperatureAvg < 100);
        bool validHum1 = (currentHumidity1 >= 0 && currentHumidity1 <= 100);
        bool validHum2 = (currentHumidity2 >= 0 && currentHumidity2 <= 100);
        bool validHumAvg = (currentHumidityAvg >= 0 && currentHumidityAvg <= 100);
        bool validLight = (currentLight >= 0);
        
        // Guardar datos para exportación CSV
        GraphDataPoint dataPoint;
        dataPoint.time = timeSeconds;
        dataPoint.temperature1 = validTemp1 ? currentTemperature1 : 0;
        dataPoint.temperature2 = validTemp2 ? currentTemperature2 : 0;
        dataPoint.temperatureAvg = validTempAvg ? currentTemperatureAvg : 0;
        dataPoint.humidity1 = validHum1 ? currentHumidity1 : 0;
        dataPoint.humidity2 = validHum2 ? currentHumidity2 : 0;
        dataPoint.humidityAvg = validHumAvg ? currentHumidityAvg : 0;
        dataPoint.light = validLight ? currentLight : 0;
        graphData.append(dataPoint);
        
        // Limitar tamaño de datos guardados
        if (graphData.size() > MAX_POINTS) {
            graphData.removeFirst();
        }
        
        // Variables para rastrear si se agregaron nuevos puntos
        bool addedPoints = false;
        
        // Agregar puntos al gráfico solo si son válidos y están seleccionados
        if (validTemp1 && ui->checkBoxTemp1->isChecked()) {
            seriesTemperature1->append(timeSeconds, currentTemperature1);
            addedPoints = true;
        }
        if (validTemp2 && ui->checkBoxTemp2->isChecked()) {
            seriesTemperature2->append(timeSeconds, currentTemperature2);
            addedPoints = true;
        }
        if (validTempAvg && ui->checkBoxTempAvg->isChecked()) {
            seriesTemperatureAvg->append(timeSeconds, currentTemperatureAvg);
            addedPoints = true;
        }
        if (validHum1 && ui->checkBoxHum1->isChecked()) {
            seriesHumidity1->append(timeSeconds, currentHumidity1);
            addedPoints = true;
        }
        if (validHum2 && ui->checkBoxHum2->isChecked()) {
            seriesHumidity2->append(timeSeconds, currentHumidity2);
            addedPoints = true;
        }
        if (validHumAvg && ui->checkBoxHumAvg->isChecked()) {
            seriesHumidityAvg->append(timeSeconds, currentHumidityAvg);
            addedPoints = true;
        }
        if (validLight && ui->checkBoxLight->isChecked()) {
            seriesLight->append(timeSeconds, currentLight);
            addedPoints = true;
        }
        
        // Solo incrementar contador si agregamos al menos un punto válido
        if (addedPoints) {
            pointCount++;
        }

        // Limitar número de puntos para mejor rendimiento
        if (pointCount > MAX_POINTS) {
            int removeCount = pointCount - MAX_POINTS;
            if (seriesTemperature1->count() > removeCount) {
                seriesTemperature1->removePoints(0, removeCount);
            }
            if (seriesTemperature2->count() > removeCount) {
                seriesTemperature2->removePoints(0, removeCount);
            }
            if (seriesTemperatureAvg->count() > removeCount) {
                seriesTemperatureAvg->removePoints(0, removeCount);
            }
            if (seriesHumidity1->count() > removeCount) {
                seriesHumidity1->removePoints(0, removeCount);
            }
            if (seriesHumidity2->count() > removeCount) {
                seriesHumidity2->removePoints(0, removeCount);
            }
            if (seriesHumidityAvg->count() > removeCount) {
                seriesHumidityAvg->removePoints(0, removeCount);
            }
            if (seriesLight->count() > removeCount) {
                seriesLight->removePoints(0, removeCount);
            }
            pointCount = MAX_POINTS;
        }

        // Ajustar rango del eje X para mostrar últimos 60 segundos
        if (timeSeconds > 60) {
            axisX->setRange(timeSeconds - 60, timeSeconds);
        } else {
            axisX->setRange(0, 60);
        }

        // Ajustar rango del eje Y dinámicamente según variables seleccionadas
        double maxVal = 0;
        double minVal = 0;
        bool hasValidData = false;
        
        if (validTemp1 && ui->checkBoxTemp1->isChecked()) {
            maxVal = qMax(maxVal, currentTemperature1);
            minVal = minVal == 0 ? currentTemperature1 : qMin(minVal, currentTemperature1);
            hasValidData = true;
        }
        if (validTemp2 && ui->checkBoxTemp2->isChecked()) {
            maxVal = qMax(maxVal, currentTemperature2);
            minVal = minVal == 0 ? currentTemperature2 : qMin(minVal, currentTemperature2);
            hasValidData = true;
        }
        if (validTempAvg && ui->checkBoxTempAvg->isChecked()) {
            maxVal = qMax(maxVal, currentTemperatureAvg);
            minVal = minVal == 0 ? currentTemperatureAvg : qMin(minVal, currentTemperatureAvg);
            hasValidData = true;
        }
        if (validHum1 && ui->checkBoxHum1->isChecked()) {
            maxVal = qMax(maxVal, currentHumidity1);
            minVal = minVal == 0 ? currentHumidity1 : qMin(minVal, currentHumidity1);
            hasValidData = true;
        }
        if (validHum2 && ui->checkBoxHum2->isChecked()) {
            maxVal = qMax(maxVal, currentHumidity2);
            minVal = minVal == 0 ? currentHumidity2 : qMin(minVal, currentHumidity2);
            hasValidData = true;
        }
        if (validHumAvg && ui->checkBoxHumAvg->isChecked()) {
            maxVal = qMax(maxVal, currentHumidityAvg);
            minVal = minVal == 0 ? currentHumidityAvg : qMin(minVal, currentHumidityAvg);
            hasValidData = true;
        }
        if (validLight && ui->checkBoxLight->isChecked()) {
            maxVal = qMax(maxVal, currentLight);
            minVal = minVal == 0 ? currentLight : qMin(minVal, currentLight);
            hasValidData = true;
        }
        
        if (hasValidData) {
            // Asegurar un rango mínimo razonable
            if (maxVal < 1 && minVal < 1) {
                // Si ambos valores son muy pequeños, usar rango por defecto
                axisY->setRange(0, 100);
            } else {
                // Ajustar rango con márgenes
                double range = maxVal - minVal;
                if (range < 10) range = 10; // Mínimo 10 unidades de rango
                axisY->setRange(qMax(0.0, minVal - range * 0.1), maxVal + range * 0.1);
            }
        }
        
        // Forzar actualización visual del gráfico
        if (chartView) {
            chartView->update();
        }
    }
}

void MainWindow::sendCommand(const QString &command)
{
    if (serialPort && serialPort->isOpen()) {
        // Limpiar el comando de espacios y caracteres especiales
        QString cleanCommand = command.trimmed();
        
        // Asegurar que el comando termine con \n
        QByteArray data = (cleanCommand + "\n").toUtf8();
        serialPort->write(data);
        serialPort->flush();
        
        // Mostrar comando enviado en la consola
        appendToConsole(QString("TX: [%1]").arg(cleanCommand), "TX");
    } else {
        QString errorMsg = "No hay conexión serial activa.";
        QMessageBox::warning(this, "Advertencia", errorMsg);
        appendToConsole(errorMsg, "ERROR");
    }
}

void MainWindow::onMotorSliderChanged(int motor, int value)
{
    // Construir comando de forma explícita para evitar problemas
    QString command = QString("SET_MOTOR%1:%2").arg(motor).arg(value);
    // Verificar que el comando se construyó correctamente
    if (!command.startsWith("SET_MOTOR")) {
        appendToConsole(QString("ERROR: Comando mal formado: %1").arg(command), "ERROR");
        return;
    }
    sendCommand(command);
    ui->statusbar->showMessage(QString("Motor %1 establecido a %2").arg(motor).arg(value), 1000);
}

void MainWindow::onMotorSpinBoxChanged(int motor, int value)
{
    // Construir comando de forma explícita para evitar problemas
    QString command = QString("SET_MOTOR%1:%2").arg(motor).arg(value);
    // Verificar que el comando se construyó correctamente
    if (!command.startsWith("SET_MOTOR")) {
        appendToConsole(QString("ERROR: Comando mal formado: %1").arg(command), "ERROR");
        return;
    }
    sendCommand(command);
    ui->statusbar->showMessage(QString("Motor %1 establecido a %2").arg(motor).arg(value), 1000);
}

void MainWindow::appendToConsole(const QString &message, const QString &type)
{
    if (!ui->consoleTextEdit) return;
    
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString prefix;
    QString color;
    
    if (type == "TX") {
        prefix = "[TX]";
        color = "#0066CC"; // Azul para transmisión
    } else if (type == "RX") {
        prefix = "[RX]";
        color = "#00AA00"; // Verde para recepción
    } else if (type == "ERROR") {
        prefix = "[ERROR]";
        color = "#CC0000"; // Rojo para errores
    } else {
        prefix = "[INFO]";
        color = "#666666"; // Gris para información
    }
    
    QString formattedMessage = QString("<span style='color: %1;'>[%2] %3</span> %4")
                               .arg(color, prefix, timestamp, message.toHtmlEscaped());
    
    ui->consoleTextEdit->appendHtml(formattedMessage);
    
    // Auto-scroll si está habilitado
    if (ui->checkBoxAutoScroll->isChecked()) {
        QTextCursor cursor = ui->consoleTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->consoleTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::onClearConsole()
{
    if (ui->consoleTextEdit) {
        ui->consoleTextEdit->clear();
        appendToConsole("Consola limpiada", "INFO");
    }
}

void MainWindow::updateSensorMetrics()
{
    // Actualizar etiquetas de sensores en la pestaña de Control
    ui->labelTemp1Value->setText(QString("%1 °C").arg(currentTemperature1, 0, 'f', 1));
    ui->labelTemp2Value->setText(QString("%1 °C").arg(currentTemperature2, 0, 'f', 1));
    ui->labelTempAvgValue->setText(QString("%1 °C").arg(currentTemperatureAvg, 0, 'f', 1));
    ui->labelHum1Value->setText(QString("%1 %").arg(currentHumidity1, 0, 'f', 1));
    ui->labelHum2Value->setText(QString("%1 %").arg(currentHumidity2, 0, 'f', 1));
    ui->labelHumAvgValue->setText(QString("%1 %").arg(currentHumidityAvg, 0, 'f', 1));
    ui->labelLightValue->setText(QString("%1").arg(currentLight, 0, 'f', 0));
}

void MainWindow::onSetSetpoint()
{
    double setpoint = ui->spinBoxSetpoint->value();
    QString command = QString("SET_SETPOINT:%1").arg(setpoint, 0, 'f', 1);
    sendCommand(command);
    appendToConsole(QString("Setpoint establecido a %1°C").arg(setpoint, 0, 'f', 1), "INFO");
}

void MainWindow::onSetKP()
{
    double kp = ui->spinBoxKP->value();
    QString command = QString("SET_KP:%1").arg(kp, 0, 'f', 2);
    sendCommand(command);
    appendToConsole(QString("Kp establecido a %1").arg(kp, 0, 'f', 2), "INFO");
}

void MainWindow::onSetKI()
{
    double ki = ui->spinBoxKI->value();
    QString command = QString("SET_KI:%1").arg(ki, 0, 'f', 2);
    sendCommand(command);
    appendToConsole(QString("Ki establecido a %1").arg(ki, 0, 'f', 2), "INFO");
}

void MainWindow::onSetKD()
{
    double kd = ui->spinBoxKD->value();
    QString command = QString("SET_KD:%1").arg(kd, 0, 'f', 2);
    sendCommand(command);
    appendToConsole(QString("Kd establecido a %1").arg(kd, 0, 'f', 2), "INFO");
}

void MainWindow::onEnablePID()
{
    sendCommand("ENABLE_PID");
    ui->labelPIDStatus->setText("Estado del PID: Activado");
    appendToConsole("PID activado", "INFO");
}

void MainWindow::onDisablePID()
{
    sendCommand("DISABLE_PID");
    ui->labelPIDStatus->setText("Estado del PID: Desactivado");
    ui->labelPIDOutput->setText("Salida PID: --");
    appendToConsole("PID desactivado", "INFO");
}

void MainWindow::onVariableCheckboxChanged()
{
    if (!seriesTemperature1 || !seriesTemperature2 || !seriesTemperatureAvg || 
        !seriesHumidity1 || !seriesHumidity2 || !seriesHumidityAvg || !seriesLight) return;
    
    // Mostrar/ocultar series según checkboxes seleccionados
    seriesTemperature1->setVisible(ui->checkBoxTemp1->isChecked());
    seriesTemperature2->setVisible(ui->checkBoxTemp2->isChecked());
    seriesTemperatureAvg->setVisible(ui->checkBoxTempAvg->isChecked());
    seriesHumidity1->setVisible(ui->checkBoxHum1->isChecked());
    seriesHumidity2->setVisible(ui->checkBoxHum2->isChecked());
    seriesHumidityAvg->setVisible(ui->checkBoxHumAvg->isChecked());
    seriesLight->setVisible(ui->checkBoxLight->isChecked());
    
    // Actualizar gráfico visualmente
    if (chartView) {
        chartView->update();
    }
}

void MainWindow::onExportCSV()
{
    if (graphData.isEmpty()) {
        QMessageBox::information(this, "Exportar CSV", "No hay datos para exportar.");
        return;
    }
    
    // Verificar que al menos una variable esté seleccionada
    if (!ui->checkBoxTemp1->isChecked() && !ui->checkBoxTemp2->isChecked() && 
        !ui->checkBoxTempAvg->isChecked() && !ui->checkBoxHum1->isChecked() && 
        !ui->checkBoxHum2->isChecked() && !ui->checkBoxHumAvg->isChecked() && 
        !ui->checkBoxLight->isChecked()) {
        QMessageBox::warning(this, "Exportar CSV", "Por favor seleccione al menos una variable para exportar.");
        return;
    }
    
    // Obtener nombre de archivo
    QString fileName = QFileDialog::getSaveFileName(this,
        "Exportar datos a CSV", "",
        "CSV Files (*.csv);;All Files (*)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    // Asegurar extensión .csv
    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo crear el archivo CSV.");
        return;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    // Escribir encabezado según variables seleccionadas
    QStringList headers;
    headers << "Tiempo (s)";
    
    if (ui->checkBoxTemp1->isChecked()) {
        headers << "Temperatura DHT22 #1 (°C)";
    }
    if (ui->checkBoxTemp2->isChecked()) {
        headers << "Temperatura DHT22 #2 (°C)";
    }
    if (ui->checkBoxTempAvg->isChecked()) {
        headers << "Temperatura Promedio (°C)";
    }
    if (ui->checkBoxHum1->isChecked()) {
        headers << "Humedad DHT22 #1 (%)";
    }
    if (ui->checkBoxHum2->isChecked()) {
        headers << "Humedad DHT22 #2 (%)";
    }
    if (ui->checkBoxHumAvg->isChecked()) {
        headers << "Humedad Promedio (%)";
    }
    if (ui->checkBoxLight->isChecked()) {
        headers << "Luz";
    }
    
    out << headers.join(",") << "\n";
    
    // Escribir datos solo de las variables seleccionadas
    for (const GraphDataPoint &point : graphData) {
        QStringList row;
        row << QString::number(point.time, 'f', 2);
        
        if (ui->checkBoxTemp1->isChecked()) {
            row << QString::number(point.temperature1, 'f', 2);
        }
        if (ui->checkBoxTemp2->isChecked()) {
            row << QString::number(point.temperature2, 'f', 2);
        }
        if (ui->checkBoxTempAvg->isChecked()) {
            row << QString::number(point.temperatureAvg, 'f', 2);
        }
        if (ui->checkBoxHum1->isChecked()) {
            row << QString::number(point.humidity1, 'f', 2);
        }
        if (ui->checkBoxHum2->isChecked()) {
            row << QString::number(point.humidity2, 'f', 2);
        }
        if (ui->checkBoxHumAvg->isChecked()) {
            row << QString::number(point.humidityAvg, 'f', 2);
        }
        if (ui->checkBoxLight->isChecked()) {
            row << QString::number(point.light, 'f', 0);
        }
        
        out << row.join(",") << "\n";
    }
    
    file.close();
    
    QMessageBox::information(this, "Exportar CSV", 
        QString("Datos exportados exitosamente.\n%1 puntos guardados.").arg(graphData.size()));
    appendToConsole(QString("Datos exportados a: %1").arg(fileName), "INFO");
}

void MainWindow::setTabsEnabled(bool enabled)
{
    // Índices de las pestañas:
    // 0: Configuración (siempre habilitada)
    // 1: Control
    // 2: Control PID
    // 3: Graph
    // 4: Consola
    
    // La pestaña de Configuración (índice 0) siempre está habilitada
    // Solo habilitamos/deshabilitamos las demás pestañas
    ui->tabWidget->setTabEnabled(1, enabled); // Control
    ui->tabWidget->setTabEnabled(2, enabled); // Control PID
    ui->tabWidget->setTabEnabled(3, enabled); // Graph
    ui->tabWidget->setTabEnabled(4, enabled); // Consola
}
