#ifndef MAXVALUE_WAVELENGTH_WIDGET_H
#define MAXVALUE_WAVELENGTH_WIDGET_H

#include <QWidget>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class MaxValue_wavelength_widget;
}

class MainWindow;
class demodulation;

class MaxValue_wavelength_widget : public QWidget
{
    Q_OBJECT
public:
    MaxValue_wavelength_widget(demodulation* _demodulation);

    Ui::MaxValue_wavelength_widget *ui;
    MainWindow* m_mainwindow;
    demodulation* m_demodulation;

    double* show_data;
    QCustomPlot* m_customPlot;

    void init_widget();
    void display_wave();

public slots:


signals:

private slots:
    void on_btn_reset_clicked();

};

#endif // RAW_WAVE_WIDGET_H
