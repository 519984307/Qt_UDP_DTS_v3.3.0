#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QObject>
#include <mainwindow.h>
//#include <qwt3d_surfaceplot.h>
#include <algorithm>

//using namespace Qwt3D;

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
    int** all_wavelength_data;
    int single_wave_data_1[128]={'\0'};
    int single_wave_data_2[128]={'\0'};
    int single_wave_data_3[128]={'\0'};
    int single_wave_data_4[128]={'\0'};
    int single_wave_data_5[128]={'\0'};
    int single_wave_data_6[128]={'\0'};
    int single_wave_data_7[128]={'\0'};
    int single_wave_data_8[128]={'\0'};
    int single_wave_data_9[128]={'\0'};
    int single_wave_data_10[128]={'\0'};
    int single_wave_data_11[128]={'\0'};
    int single_wave_data_12[128]={'\0'};
    int single_wave_data_13[128]={'\0'};
    int single_wave_data_14[128]={'\0'};
    int single_wave_data_15[128]={'\0'};
    int single_wave_data_16[128]={'\0'};
    int single_wave_data_17[128]={'\0'};
    int single_wave_data_18[128]={'\0'};
    int single_wave_data_19[128]={'\0'};
    int single_wave_data_20[128]={'\0'};
    int single_wave_data_21[128]={'\0'};
    int single_wave_data_22[128]={'\0'};
    int single_wave_data_23[128]={'\0'};
    int single_wave_data_24[128]={'\0'};
    int single_wave_data_25[128]={'\0'};
    int single_wave_data_26[128]={'\0'};
    int single_wave_data_27[128]={'\0'};
    int single_wave_data_28[128]={'\0'};
    int single_wave_data_29[128]={'\0'};
    int single_wave_data_30[128]={'\0'};
    int single_wave_data_31[128]={'\0'};
    int single_wave_data_32[128]={'\0'};
    int single_wave_data_33[128]={'\0'};
    int single_wave_data_34[128]={'\0'};
    int single_wave_data_35[128]={'\0'};
    int single_wave_data_36[128]={'\0'};
    int single_wave_data_37[128]={'\0'};
    int single_wave_data_38[128]={'\0'};
    int single_wave_data_39[128]={'\0'};
    int single_wave_data_40[128]={'\0'};
    int single_wave_data_41[128]={'\0'};
    int single_wave_data_42[128]={'\0'};
    int single_wave_data_43[128]={'\0'};
    int single_wave_data_44[128]={'\0'};
    int single_wave_data_45[128]={'\0'};
    int single_wave_data_46[128]={'\0'};
    int single_wave_data_47[128]={'\0'};
    int single_wave_data_48[128]={'\0'};
    int single_wave_data_49[128]={'\0'};
    int single_wave_data_50[128]={'\0'};
    int single_wave_data_51[128]={'\0'};
    int single_wave_data_52[128]={'\0'};
    int single_wave_data_53[128]={'\0'};
    int single_wave_data_54[128]={'\0'};
    int single_wave_data_55[128]={'\0'};
    int single_wave_data_56[128]={'\0'};
    int single_wave_data_57[128]={'\0'};
    int single_wave_data_58[128]={'\0'};
    int single_wave_data_59[128]={'\0'};
    int single_wave_data_60[128]={'\0'};
    int single_wave_data_61[128]={'\0'};
    int single_wave_data_62[128]={'\0'};
    int single_wave_data_63[128]={'\0'};
    int single_wave_data_64[128]={'\0'};
    int add_wave_data[128]={'\0'};
//    double ** wavelength_distance_array;
    int wavelength_MaxApproach[128]={'\0'};
    int wavelength_CentroidApproach[128]={'\0'};
    int Temp[128]={'\0'};
    int MAX_Temp = 0.0; //定义最大温度值

    add_wave_widget* m_add_wave_widget;
//    SurfacePlot spectrum_wava;

    int s1,s2;
    double w1,w2;

    void run();

signals:
    void sendToAdd_wave_widget();
    void sendToMaxValue_widget();
    void sendToCentroid_widget();
    void sendToTempDistance_widget();
};

#endif // DEMODULATION_H
