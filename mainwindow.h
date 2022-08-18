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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
class QCustomPlot;
class raw_wave_widget;
class add_wave_widget;

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



signals:
    void sendToRaw_wave_widget(double* _senddata);
//    void sendToAdd_wave_widget(double* _senddata);

private slots:
    void on_btn_readfls_clicked();

    void on_btn_dspwave_clicked();

    void on_btn_demodulation_clicked();

private:

};
#endif // MAINWINDOW_H
