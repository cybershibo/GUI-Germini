#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialPort(nullptr)
    , chart(nullptr)
    , series(nullptr)
    , axisX(nullptr)
    , axisY(nullptr)
    , graphTimer(nullptr)
    , currentValue(0.0)
    , pointCount(0)
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

    // Actualizar puertos disponibles
    refreshSerialPorts();

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
    series = new QLineSeries();
    series->setName("Datos del ESP32");

    chart->addSeries(series);
    chart->setTitle("Gráfico de Datos en Tiempo Real");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX = new QValueAxis();
    axisX->setTitleText("Tiempo (segundos)");
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Valor");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

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

    // Tab 4
    connect(ui->btn4_1, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn4_2, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn4_3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(ui->btn4_4, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
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
    QString dataString = QString::fromUtf8(data).trimmed();

    // Procesar datos recibidos
    // Formato esperado: "DATA:123.45" o simplemente un número
    bool ok;
    double value = dataString.toDouble(&ok);
    
    if (ok) {
        currentValue = value;
    } else if (dataString.startsWith("DATA:")) {
        value = dataString.mid(5).toDouble(&ok);
        if (ok) {
            currentValue = value;
        }
    }

    // Mostrar en la barra de estado
    ui->statusbar->showMessage("Datos recibidos: " + dataString, 1000);
}

void MainWindow::updateGraph()
{
    if (series) {
        // Calcular tiempo transcurrido en segundos
        qint64 elapsed = startTime.msecsTo(QDateTime::currentDateTime());
        double timeSeconds = elapsed / 1000.0;

        // Agregar punto al gráfico
        series->append(timeSeconds, currentValue);
        pointCount++;

        // Limitar número de puntos para mejor rendimiento
        if (pointCount > MAX_POINTS) {
            series->removePoints(0, pointCount - MAX_POINTS);
            pointCount = MAX_POINTS;
        }

        // Ajustar rango del eje X para mostrar últimos 60 segundos
        if (timeSeconds > 60) {
            axisX->setRange(timeSeconds - 60, timeSeconds);
        }

        // Ajustar rango del eje Y dinámicamente
        if (currentValue > axisY->max()) {
            axisY->setMax(currentValue * 1.1);
        } else if (currentValue < axisY->min()) {
            axisY->setMin(currentValue * 1.1);
        }
    }
}

void MainWindow::sendCommand(const QString &command)
{
    if (serialPort && serialPort->isOpen()) {
        QByteArray data = (command + "\n").toUtf8();
        serialPort->write(data);
        serialPort->flush();
    } else {
        QMessageBox::warning(this, "Advertencia", "No hay conexión serial activa.");
    }
}
