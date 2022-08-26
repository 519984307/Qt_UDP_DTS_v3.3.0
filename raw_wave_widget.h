#ifndef RAW_WAVE_WIDGET_H
#define RAW_WAVE_WIDGET_H

#include <QWidget>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class raw_wave_widget;
}

class MainWindow;
class QWebEngineView;

class raw_wave_widget : public QWidget
{
    Q_OBJECT
public:
    raw_wave_widget();

    Ui::raw_wave_widget *ui;
    MainWindow* m_mainwindow;

    double* show_data;
    QCustomPlot* m_customPlot;
    QWebEngineView* m_WebEngineView;

    void init_widget();

public slots:
    void display_wave(double* _displaydata);

signals:
    void sendToMainwindow_save();

private slots:
    void on_btn_reset_clicked();

//    void on_btn_save_clicked();
};

#endif // RAW_WAVE_WIDGET_H
