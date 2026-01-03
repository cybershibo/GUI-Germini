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
    void onButtonClicked();
    void onConnectClicked();
    void onDisconnectClicked();
    void onRefreshPorts();
    void onSerialDataReceived();
    void updateGraph();

private:
    void setupChart();
    void sendCommand(const QString &command);
    void refreshSerialPorts();
    void connectAllButtons();

    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *seriesTemperature;
    QLineSeries *seriesHumidity;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *graphTimer;
    QDateTime startTime;
    double currentTemperature;
    double currentHumidity;
    int pointCount;
    static const int MAX_POINTS = 10000000;
    
    // Buffer para datos seriales (pueden llegar fragmentados)
    QString serialBuffer;
    
    // Slots para control de motores
    void onMotorSliderChanged(int motor, int value);
    void onMotorSpinBoxChanged(int motor, int value);
    
    // Funciones para la consola
    void appendToConsole(const QString &message, const QString &type = "INFO");
    void onClearConsole();
};

#endif // MAINWINDOW_H
