#include "demodulation.h"

demodulation::demodulation(MainWindow* _mainWindow):
    m_mainwindow(_mainWindow),
    raw_data(_mainWindow->raw_data),
    all_wavelength_data(new double*[50])
{
    //step1: 按光源扫描波长整理数据，即将每一个波长的信号分开
    //step2: 将这些波长信号累加
    //step3: 画光谱
    //step4: 最大值法确定波长 取x值，从yoz平面看
    //step5: 温度判断算法

    all_wavelength_data[0]=single_wave_data_1;
    all_wavelength_data[1]=single_wave_data_2;
    all_wavelength_data[2]=single_wave_data_3;
    all_wavelength_data[3]=single_wave_data_4;
    all_wavelength_data[4]=single_wave_data_5;
    all_wavelength_data[5]=single_wave_data_6;
    all_wavelength_data[6]=single_wave_data_7;
    all_wavelength_data[7]=single_wave_data_8;
    all_wavelength_data[8]=single_wave_data_9;
    all_wavelength_data[9]=single_wave_data_10;
    all_wavelength_data[10]=single_wave_data_11;
    all_wavelength_data[11]=single_wave_data_12;
    all_wavelength_data[12]=single_wave_data_13;
    all_wavelength_data[13]=single_wave_data_14;
    all_wavelength_data[14]=single_wave_data_15;
    all_wavelength_data[15]=single_wave_data_16;
    all_wavelength_data[16]=single_wave_data_17;
    all_wavelength_data[17]=single_wave_data_18;
    all_wavelength_data[18]=single_wave_data_19;
    all_wavelength_data[19]=single_wave_data_20;
    all_wavelength_data[20]=single_wave_data_21;
    all_wavelength_data[21]=single_wave_data_22;
    all_wavelength_data[22]=single_wave_data_23;
    all_wavelength_data[23]=single_wave_data_24;
    all_wavelength_data[24]=single_wave_data_25;
    all_wavelength_data[25]=single_wave_data_26;
    all_wavelength_data[26]=single_wave_data_27;
    all_wavelength_data[27]=single_wave_data_28;
    all_wavelength_data[28]=single_wave_data_29;
    all_wavelength_data[29]=single_wave_data_30;
    all_wavelength_data[30]=single_wave_data_31;
    all_wavelength_data[31]=single_wave_data_32;
    all_wavelength_data[32]=single_wave_data_33;
    all_wavelength_data[33]=single_wave_data_34;
    all_wavelength_data[34]=single_wave_data_35;
    all_wavelength_data[35]=single_wave_data_36;
    all_wavelength_data[36]=single_wave_data_37;
    all_wavelength_data[37]=single_wave_data_38;
    all_wavelength_data[38]=single_wave_data_39;
    all_wavelength_data[39]=single_wave_data_40;
    all_wavelength_data[40]=single_wave_data_41;
    all_wavelength_data[41]=single_wave_data_42;
    all_wavelength_data[42]=single_wave_data_43;
    all_wavelength_data[43]=single_wave_data_44;
    all_wavelength_data[44]=single_wave_data_45;
    all_wavelength_data[45]=single_wave_data_46;
    all_wavelength_data[46]=single_wave_data_47;
    all_wavelength_data[47]=single_wave_data_48;
    all_wavelength_data[48]=single_wave_data_49;
    all_wavelength_data[49]=single_wave_data_50;

}

demodulation::~demodulation()
{

}


void demodulation::run()
{
    /*---step1: 按光源扫描波长整理数据，即将每一个波长的信号分开
    raw_data中波长顺序:  λ32、λ33 ... λ50、λ1、λ2 ... λ31---*/
   int p = 0;

   //先暂时维持λ1、λ2 ... λ50的顺序
    for(int i=0;i<50;i++){

        for(int j=0;j<25002;j++){

             all_wavelength_data[i][j]=m_mainwindow->raw_data[p];

            p++;
        }
    }

    qDebug()<<"scan wavelength finished ! "<<endl;

    /*---step2: 将这些波长信号累加---*/
    for(int k=0;k<25002;k++){

        double sum = 0;

        for(int p=0;p<50;p++)
            sum = sum+all_wavelength_data[p][k];

        add_wave_data[k] = 100*sum; //强度扩大100倍
    }

    emit sendToAdd_wave_widget();

    qDebug()<<"add wavelength finished ! "<<endl;
}
