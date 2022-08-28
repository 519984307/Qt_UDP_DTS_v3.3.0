#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <demodulation.h>
#include <qcustomplot.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
//#include "matrix.h"
#include <fstream>
#include <sstream>
#include "raw_wave_widget.h"
#include "add_wave_widget.h"
#include "MaxValue_wavelength_widget.h"
#include "Centroid_wavelength_widget.h"
#include "Temp_distance_widget.h"
#include "raw_data_save.h"
#include "Temp_distance_save.h"
#include <QtWebEngineWidgets>
<<<<<<< HEAD
=======
#include <QtWebChannel>
#include "webclass.h"
#include <QResizeEvent>
>>>>>>> efa8b19 (第六次提交)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
class QCustomPlot;
class raw_wave_widget;
class raw_data_save;
class add_wave_widget;
class MaxValue_wavelength_widget;
class Centroid_wavelength_widget;
class Temp_distance_widget;
class Temp_distance_save;
class WebClass;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    double* raw_data;
    raw_wave_widget* m_raw_wave_widget;
    demodulation* m_demodulation;
    add_wave_widget* m_add_wave_widget;
    MaxValue_wavelength_widget* m_maxValue_wavelength_widget;
    Centroid_wavelength_widget* m_centroid_wavelength_widget;
    Temp_distance_widget* m_tempDistance_widget;
    raw_data_save* m_raw_data_save;
    Temp_distance_save* m_temp_distance_save;

<<<<<<< HEAD
    QCustomPlot* m_raw_data_widget;
    QCustomPlot* m_add_wave_data_widget;
    QCustomPlot* m_max_approach_widget;
    QCustomPlot* m_centroid_approach_widget;
    QCustomPlot* m_temp_distance_widget;
=======
    QWebEngineView* m_raw_data_widget;
    QWebEngineView* m_add_wave_data_widget;
    QWebEngineView* m_max_approach_widget;
    QWebEngineView* m_centroid_approach_widget;
    QWebEngineView* m_temp_distance_widget;
>>>>>>> efa8b19 (第六次提交)

    void init_widget_raw_data();
    void init_widget_add_wave();
    void init_widget_max_approach();
    void init_widget_centroid_approach();
    void init_widget_temp_distance();

<<<<<<< HEAD
=======
    void echarts_load_raw_data();
    void echarts_load_add_wave();
    void echarts_load_max_approach();
    void echarts_load_centroid_approach();
    void echarts_load_temp();

    WebClass* webobj;

    void test();

>>>>>>> efa8b19 (第六次提交)
signals:
    void sendToRaw_wave_widget(double* _senddata);
//    void sendToAdd_wave_widget(double* _senddata);

private slots:
    void on_btn_readfls_clicked();

//    void on_btn_dspwave_clicked();

    void on_btn_demodulation_clicked();

    void on_btn_maxValue_clicked();

    void on_btn_centroid_clicked();

    void on_btn_temp_clicked();

    void on_btn_reset_wave_clicked();

    void on_btn_save_temp_clicked();

<<<<<<< HEAD
=======
    void onResizeEcharts1();
    void onResizeEcharts2();
    void onResizeEcharts3();
    void onResizeEcharts4();
    void onResizeEcharts5();

>>>>>>> efa8b19 (第六次提交)
public slots:
    void save_raw_data();
//    void save_temp_distance_data();
    void save_filename();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    bool isLoaded1 = false;
    bool isLoaded2 = false;
    bool isLoaded3 = false;
    bool isLoaded4 = false;
    bool isLoaded5 = false;

};
#endif // MAINWINDOW_H
