#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QObject>
#include <mainwindow.h>

class MainWindow;
class add_wave_widget;

class demodulation : public QThread
{
    Q_OBJECT
public:
    demodulation(MainWindow* _mainWindow);
    ~demodulation();

    MainWindow* m_mainwindow;

    double* raw_data;
    double** all_wavelength_data;
    double single_wave_data_1[25002]={'\0'};
    double single_wave_data_2[25002]={'\0'};
    double single_wave_data_3[25002]={'\0'};
    double single_wave_data_4[25002]={'\0'};
    double single_wave_data_5[25002]={'\0'};
    double single_wave_data_6[25002]={'\0'};
    double single_wave_data_7[25002]={'\0'};
    double single_wave_data_8[25002]={'\0'};
    double single_wave_data_9[25002]={'\0'};
    double single_wave_data_10[25002]={'\0'};
    double single_wave_data_11[25002]={'\0'};
    double single_wave_data_12[25002]={'\0'};
    double single_wave_data_13[25002]={'\0'};
    double single_wave_data_14[25002]={'\0'};
    double single_wave_data_15[25002]={'\0'};
    double single_wave_data_16[25002]={'\0'};
    double single_wave_data_17[25002]={'\0'};
    double single_wave_data_18[25002]={'\0'};
    double single_wave_data_19[25002]={'\0'};
    double single_wave_data_20[25002]={'\0'};
    double single_wave_data_21[25002]={'\0'};
    double single_wave_data_22[25002]={'\0'};
    double single_wave_data_23[25002]={'\0'};
    double single_wave_data_24[25002]={'\0'};
    double single_wave_data_25[25002]={'\0'};
    double single_wave_data_26[25002]={'\0'};
    double single_wave_data_27[25002]={'\0'};
    double single_wave_data_28[25002]={'\0'};
    double single_wave_data_29[25002]={'\0'};
    double single_wave_data_30[25002]={'\0'};
    double single_wave_data_31[25002]={'\0'};
    double single_wave_data_32[25002]={'\0'};
    double single_wave_data_33[25002]={'\0'};
    double single_wave_data_34[25002]={'\0'};
    double single_wave_data_35[25002]={'\0'};
    double single_wave_data_36[25002]={'\0'};
    double single_wave_data_37[25002]={'\0'};
    double single_wave_data_38[25002]={'\0'};
    double single_wave_data_39[25002]={'\0'};
    double single_wave_data_40[25002]={'\0'};
    double single_wave_data_41[25002]={'\0'};
    double single_wave_data_42[25002]={'\0'};
    double single_wave_data_43[25002]={'\0'};
    double single_wave_data_44[25002]={'\0'};
    double single_wave_data_45[25002]={'\0'};
    double single_wave_data_46[25002]={'\0'};
    double single_wave_data_47[25002]={'\0'};
    double single_wave_data_48[25002]={'\0'};
    double single_wave_data_49[25002]={'\0'};
    double single_wave_data_50[25002]={'\0'};
    double add_wave_data[25002]={'\0'};

    add_wave_widget* m_add_wave_widget;

    void run();

signals:
    void sendToAdd_wave_widget();
};

#endif // DEMODULATION_H
