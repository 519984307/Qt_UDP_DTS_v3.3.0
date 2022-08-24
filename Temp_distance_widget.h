#ifndef TEMP_DISTANCE_WIDGET_H
#define TEMP_DISTANCE_WIDGET_H

#include <QWidget>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class Temp_distance_widget;
}

class MainWindow;
class demodulation;

class Temp_distance_widget : public QWidget
{
    Q_OBJECT
public:
    Temp_distance_widget(demodulation* _demodulation);

    Ui::Temp_distance_widget *ui;
    MainWindow* m_mainwindow;
    demodulation* m_demodulation;

    double* show_data;
    QCustomPlot* m_customPlot;

    void init_widget();
    void display_wave();

public slots:

signals:
    void sendToMainwindow_save();

private slots:
    void on_btn_reset_clicked();

    void on_btn_save_clicked();
};

#endif // RAW_WAVE_WIDGET_H
