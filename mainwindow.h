#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CirQueue.h"
#include "udp_recv.h"
#include "udp_send.h"
//#include "HEXtoDEC.h"
#include <QMainWindow>
#include <QThread>
#include <demodulation.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <fstream>
#include <sstream>
#include "Temp_distance_save.h"
#include <QtWebEngineWidgets>
#include <QtWebChannel>
//#include "webclass.h"
#include <QResizeEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
class Temp_distance_save;
class udp_recv;
class udp_send;
class HEXtoDEC;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
//    double* raw_data;
    demodulation* m_demodulation;
    Temp_distance_save* m_temp_distance_save;
    udp_recv* m_udp_recv;
    udp_send* m_udp_send;
    HEXtoDEC* m_hextodec;

    QString send_data;

    QWebEngineView* m_temp_distance_widget;
    QWebEngineView* m_max_temp_widget;

    bool isStartRecv = false;

    QTimer* Temp_Display_Timer;
    QTimer* Temp_save_Timer;
    QTimer* Alarm_Timer;

     QLabel *label;
         void paintEvent(QPaintEvent*) override;

    int alarm_count=0; //±¨¾¯¼ÆÊ±

    void init_widget_temp_distance();

    void init_widget_max_temp();

    void echarts_load_temp();

    void Open_Temp_Save_Thread();

    void start_alarm();

signals:
    void sendToRaw_wave_widget(double* _senddata);


private slots:
    void on_btn_demodulation_clicked();

    void on_btn_save_temp_clicked();

    void FinishUdp_recvThread();
//    void FinishHEXtoDECThread();
    void FinishDemodulationThread();
    void FinishTemp_saveThread();

    void onResizeEcharts5();
    void onResizeEcharts6();

    void on_btn_recv_clicked();

    void on_m_send_clicked();

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    bool isLoaded5 = false;
    bool isLoaded6 = false;

};
#endif // MAINWINDOW_H
