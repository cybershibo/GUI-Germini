#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onDisconnectClicked();
    void onRefreshPorts();
    void onSerialDataReceived();
    void updateGraph();
    void onStartAllActuators();
    void onStopAllActuators();

private:
    void setupChart();
    void sendCommand(const QString &command);
    void refreshSerialPorts();
    void connectAllButtons();
    void setTabsEnabled(bool enabled); // Habilitar/deshabilitar pestañas según conexión

    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *seriesTemperature1;
    QLineSeries *seriesTemperature2;
    QLineSeries *seriesTemperatureAvg;
    QLineSeries *seriesHumidity1;
    QLineSeries *seriesHumidity2;
    QLineSeries *seriesHumidityAvg;
    QLineSeries *seriesLight;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *graphTimer;
    QDateTime startTime;
    double currentTemperature1;
    double currentTemperature2;
    double currentTemperatureAvg;
    double currentHumidity1;
    double currentHumidity2;
    double currentHumidityAvg;
    double currentLight;
    int pointCount;
    static const int MAX_POINTS = 100000000;
    
    // Buffer para datos seriales (pueden llegar fragmentados)
    QString serialBuffer;
    
    // Slots para control de motores
    void onMotorSliderChanged(int motor, int value);
    void onMotorSpinBoxChanged(int motor, int value);
    void updatePWMLabels();
    
    // Slots para control del servo
    void onServoSliderChanged(int value);
    void onServoSpinBoxChanged(int value);
    void onSendServoAngle();
    void updateServoAngleLabel();
    
    // Funciones para la consola
    void appendToConsole(const QString &message, const QString &type = "INFO");
    void onClearConsole();
    
    // Funciones para PID
    void onSetSetpoint();
    void onSetKP();
    void onSetKI();
    void onSetKD();
    void onEnablePID();
    void onDisablePID();
    
    // Función para actualizar métricas de sensores
    void updateSensorMetrics();
    
    // Funciones para el gráfico
    void onVariableCheckboxChanged();
    void onExportCSV();
    
    // Estructura para almacenar datos del gráfico
    struct GraphDataPoint {
        double time;
        double temperature1;
        double temperature2;
        double temperatureAvg;
        double humidity1;
        double humidity2;
        double humidityAvg;
        double light;
    };
    QList<GraphDataPoint> graphData;
    
    // Valores PWM actuales de los motores
    int currentPWM1;
    int currentPWM2;
    int currentPWM3;
    
    // Valor actual del ángulo del servo
    int currentServoAngle;
    
    // Estado del PID (para bloquear control manual)
    bool pidActive;
};

#endif // MAINWINDOW_H
