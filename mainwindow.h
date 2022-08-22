#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <demodulation.h>
#include <qcustomplot.h>
#include <stdio.h>
#include <stdlib.h>
#include "mat.h"
#include "matrix.h"
#include <fstream>
#include <sstream>
#include "raw_wave_widget.h"
#include "add_wave_widget.h"
#include "MaxValue_wavelength_widget.h"
#include "Centroid_wavelength_widget.h"
#include "Temp_distance_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
class QCustomPlot;
class raw_wave_widget;
class add_wave_widget;
class MaxValue_wavelength_widget;
class Centroid_wavelength_widget;
class Temp_distance_widget;

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

signals:
    void sendToRaw_wave_widget(double* _senddata);
//    void sendToAdd_wave_widget(double* _senddata);

private slots:
    void on_btn_readfls_clicked();

    void on_btn_dspwave_clicked();

    void on_btn_demodulation_clicked();

    void on_btn_maxValue_clicked();

    void on_btn_centroid_clicked();

    void on_btn_temp_clicked();

private:

};
#endif // MAINWINDOW_H
