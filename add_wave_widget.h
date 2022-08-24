#ifndef ADD_WAVE_WIDGET_H
#define ADD_WAVE_WIDGET_H

#include <QWidget>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class add_wave_widget;
}

class MainWindow;
class demodulation;

class add_wave_widget : public QWidget
{
    Q_OBJECT
public:
    add_wave_widget(demodulation* _demodulation);

    Ui::add_wave_widget *ui;
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

    void on_btn_save_clicked();
};

#endif // RAW_WAVE_WIDGET_H
