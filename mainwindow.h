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
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *graphTimer;
    QDateTime startTime;
    double currentValue;
    int pointCount;
    static const int MAX_POINTS = 1000000;
};

#endif // MAINWINDOW_H
