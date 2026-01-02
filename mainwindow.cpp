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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialPort(nullptr)
    , chart(nullptr)
    , seriesTemperature(nullptr)
    , seriesHumidity(nullptr)
    , axisX(nullptr)
    , axisY(nullptr)
    , graphTimer(nullptr)
    , currentTemperature(0.0)
    , currentHumidity(0.0)
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

    // Actualizar puertos disponibles
    refreshSerialPorts();
    
    // Mensaje inicial en la consola
    appendToConsole("Sistema iniciado. Esperando conexión...", "INFO");

    // Inicializar estado de desconexión
    ui->btnDisconnect->setEnabled(false);
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
    
    // Crear series para temperatura y humedad
    seriesTemperature = new QLineSeries();
    seriesTemperature->setName("Temperatura (°C)");
    seriesTemperature->setColor(Qt::red);
    
    seriesHumidity = new QLineSeries();
    seriesHumidity->setName("Humedad (%)");
    seriesHumidity->setColor(Qt::blue);

    chart->addSeries(seriesTemperature);
    chart->addSeries(seriesHumidity);
    chart->setTitle("DHT22 - Temperatura y Humedad en Tiempo Real");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX = new QValueAxis();
    axisX->setTitleText("Tiempo (segundos)");
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesTemperature->attachAxis(axisX);
    seriesHumidity->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Valor");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesTemperature->attachAxis(axisY);
    seriesHumidity->attachAxis(axisY);

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
}

void MainWindow::connectAllButtons()
{
    // Tab 1
    connect(ui->btn1_1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn1_4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Tab 2
    connect(ui->btn2_1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn2_2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn2_3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn2_4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Tab 3
    connect(ui->btn3_1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn3_2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn3_3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn3_4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
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

    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        ui->btnConnect->setEnabled(false);
        ui->btnDisconnect->setEnabled(true);
        ui->comboBoxPort->setEnabled(false);
        ui->statusbar->showMessage("Conectado a " + portName, 2000);
        graphTimer->start(100); // Actualizar gráfico cada 100ms
        appendToConsole(QString("Conectado a %1").arg(portName), "INFO");
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
        ui->statusbar->showMessage("Desconectado", 2000);
        graphTimer->stop();
        appendToConsole("Desconectado del puerto serial", "INFO");
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
        
        // Procesar datos recibidos del DHT22
        // Formato esperado: "DATA:TEMP:XX.XX:HUM:XX.XX"
        if (dataString.startsWith("DATA:TEMP:")) {
            int tempStart = 10; // "DATA:TEMP:" tiene 10 caracteres
            int tempEnd = dataString.indexOf(":HUM:");
            if (tempEnd > tempStart) {
                QString tempStr = dataString.mid(tempStart, tempEnd - tempStart);
                bool ok;
                double temp = tempStr.toDouble(&ok);
                if (ok && temp > -50 && temp < 100) { // Validar rango razonable
                    currentTemperature = temp;
                }
                
                // Extraer humedad
                int humStart = tempEnd + 5; // ":HUM:" tiene 5 caracteres
                QString humStr = dataString.mid(humStart);
                double hum = humStr.toDouble(&ok);
                if (ok && hum >= 0 && hum <= 100) { // Validar rango razonable
                    currentHumidity = hum;
                }
                
                ui->statusbar->showMessage(QString("Temp: %1°C, Hum: %2%").arg(currentTemperature, 0, 'f', 1).arg(currentHumidity, 0, 'f', 1), 1000);
            }
        }
        // Formato legacy para compatibilidad
        else if (dataString.startsWith("DATA:")) {
            QString valueStr = dataString.mid(5);
            bool ok;
            double value = valueStr.toDouble(&ok);
            if (ok) {
                currentTemperature = value; // Usar como temperatura por defecto
            }
        }
    }
}

void MainWindow::updateGraph()
{
    if (seriesTemperature && seriesHumidity) {
        // Calcular tiempo transcurrido en segundos
        qint64 elapsed = startTime.msecsTo(QDateTime::currentDateTime());
        double timeSeconds = elapsed / 1000.0;

        // Solo agregar puntos si tenemos valores válidos (no cero o valores inválidos)
        // Verificar que los valores sean razonables antes de agregarlos
        bool validTemp = (currentTemperature > -50 && currentTemperature < 100);
        bool validHum = (currentHumidity >= 0 && currentHumidity <= 100);
        
        // Agregar puntos al gráfico solo si son válidos
        if (validTemp) {
            seriesTemperature->append(timeSeconds, currentTemperature);
        }
        if (validHum) {
            seriesHumidity->append(timeSeconds, currentHumidity);
        }
        
        // Solo incrementar contador si agregamos al menos un punto válido
        if (validTemp || validHum) {
            pointCount++;
        }

        // Limitar número de puntos para mejor rendimiento
        if (pointCount > MAX_POINTS) {
            int removeCount = pointCount - MAX_POINTS;
            seriesTemperature->removePoints(0, removeCount);
            seriesHumidity->removePoints(0, removeCount);
            pointCount = MAX_POINTS;
        }

        // Ajustar rango del eje X para mostrar últimos 60 segundos
        if (timeSeconds > 60) {
            axisX->setRange(timeSeconds - 60, timeSeconds);
        }

        // Ajustar rango del eje Y dinámicamente
        if (validTemp || validHum) {
            double maxVal = qMax(validTemp ? currentTemperature : 0, validHum ? currentHumidity : 0);
            double minVal = qMin(validTemp ? currentTemperature : 0, validHum ? currentHumidity : 0);
            
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
    }
}

void MainWindow::sendCommand(const QString &command)
{
    if (serialPort && serialPort->isOpen()) {
        QByteArray data = (command + "\n").toUtf8();
        serialPort->write(data);
        serialPort->flush();
        
        // Mostrar comando enviado en la consola
        appendToConsole(command, "TX");
    } else {
        QString errorMsg = "No hay conexión serial activa.";
        QMessageBox::warning(this, "Advertencia", errorMsg);
        appendToConsole(errorMsg, "ERROR");
    }
}

void MainWindow::onMotorSliderChanged(int motor, int value)
{
    QString command = QString("SET_MOTOR%1:%2").arg(motor).arg(value);
    sendCommand(command);
    ui->statusbar->showMessage(QString("Motor %1 establecido a %2").arg(motor).arg(value), 1000);
}

void MainWindow::onMotorSpinBoxChanged(int motor, int value)
{
    QString command = QString("SET_MOTOR%1:%2").arg(motor).arg(value);
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
