#include "demodulation.h"

demodulation::demodulation(MainWindow* _mainWindow):
    m_mainwindow(_mainWindow),
//    raw_data(_mainWindow->raw_data),
    all_wavelength_data(new int*[64])
//    spectrum_wava(new SurfacePlot()),
//    wavelength_MaxApproach(new double[128]),
//    wavelength_CentroidApproach(new double[128])
//    Temp(new double[128])
{
    //step1: 按光源扫描波长整理数据，即将每一个波长的信号分开
    //step2: 将这些波长信号累加
    //step3: 画光谱
    //step4: 最大值法确定中心波长/质点法确定中心波长
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
    all_wavelength_data[50]=single_wave_data_51;
    all_wavelength_data[51]=single_wave_data_52;
    all_wavelength_data[52]=single_wave_data_53;
    all_wavelength_data[53]=single_wave_data_54;
    all_wavelength_data[54]=single_wave_data_55;
    all_wavelength_data[55]=single_wave_data_56;
    all_wavelength_data[56]=single_wave_data_57;
    all_wavelength_data[57]=single_wave_data_58;
    all_wavelength_data[58]=single_wave_data_59;
    all_wavelength_data[59]=single_wave_data_60;
    all_wavelength_data[60]=single_wave_data_61;
    all_wavelength_data[61]=single_wave_data_62;
    all_wavelength_data[62]=single_wave_data_63;
    all_wavelength_data[63]=single_wave_data_64;

}

demodulation::~demodulation()
{

}


void demodulation::run()
{

    while(1){
        /*---step1: 按光源扫描波长整理数据，即将每一个波长的信号分开
        raw_data中波长顺序:  λ32、λ33 ... λ50、λ1、λ2 ... λ31
        实际UDP通信解调数据时按λ1、λ2 ... λ50的顺序来---*/
        for(int i=0;i<64;i++){
            for(int j=0;j<128;j++){

                //当队列不为空时，pop()，否则一直循环等待
//                while (!m_mainwindow->m_udp_recv->CHdata2->isEmpty()) {
//                    all_wavelength_data[i][j]=m_mainwindow->m_udp_recv->CHdata2->pop();
//                }
//                do{
//                    QThread::msleep(1);
//                }
                while(m_mainwindow->m_udp_recv->CHdata2->isEmpty()){
                    QThread::msleep(1);
                }

                all_wavelength_data[i][j]=m_mainwindow->m_udp_recv->CHdata2->pop();
            }
        }

        qDebug()<<"scan wavelength finished ! "<<endl;

        /*---step2: 将这些波长信号累加 弃用---*/
//        for(int k=0;k<25002;k++){

//            double sum = 0;

//            for(int p=0;p<50;p++)
//                sum = sum+all_wavelength_data[p][k];

//            add_wave_data[k] = 100*sum; //强度扩大100倍
//        }

    //    emit sendToAdd_wave_widget();

//        qDebug()<<"add wavelength finished ! "<<endl;

        /*---step3: 画光谱 弃用---*/
    //     s1 = 500,  s2= 800; //取all_wavelength_data中距离轴的范围是s1~s2
    //    w1=1550.5, w2=1553.44; //波长值的范围是w1~w2

    //    wavelength_distance_array = allocateData(50, 50);

    //    //给一条曲线赋值
    //    for(int n = 0; n < 50; n++)
    //    {
    //        for(int l = 0; l <50; l++)
    //        {
    //            wavelength_distance_array[n][l] = all_wavelength_data[l][s1];
    //        }
    //    }

//        /*---step4: 最大值法确定中心波长---*/
//        for(int p=0;p<128;p++){

//            int max_value = all_wavelength_data[0][p];

//            int max_index = 0;

//            for(int q=0;q<64;q++){
//                if(all_wavelength_data[q][p]>max_value){
//                    max_index = q;
//                    max_value = all_wavelength_data[q][p];
//                }
//            }
//            //符合阈值条件的波长序号存入，不符合的序号设为0
//            if(max_value>1320500) wavelength_MaxApproach[p]=max_index;
//    //        else wavelength_MaxApproach[p] = 0;
//        }

    //    emit sendToMaxValue_widget();

//        qDebug()<<"MaxValue Wavelength finished ! "<<endl;

//        /*---step4: 质心法确定中心波长---*/
//        for(int p=0;p<128;p++){

//            int max_value = all_wavelength_data[0][p];

//    //        int max_index = 0;

//            for(int q=0;q<64;q++){
//                if(all_wavelength_data[q][p]>max_value){
//    //                max_index = q;
//                    max_value = all_wavelength_data[q][p];
//                }
//            }

//            //符合阈值条件的波长序号存入，不符合的序号设为0
//            if(max_value>3) {
//                int fenzi=0,fenmu=0;

//                for(int m=0;m<50;m++){
//                    fenzi = fenzi + (all_wavelength_data[m][p]+50)*m;
//                    fenmu = fenmu + (all_wavelength_data[m][p]+50);
//                }

//                wavelength_CentroidApproach[p] = fenzi/fenmu;
//            }
//    //        else wavelength_CentroidApproach[p] = 0;
//        }

//    //    emit sendToCentroid_widget();

//        qDebug()<<"Centroid Wavelength finished ! "<<endl;

        /*--step5: 温度判断算法--*/

        //Temp置零
        memset(Temp,0,sizeof(Temp));
        //定义阈值mean
        int mean = 0;

        //第一个距离的波长值取平均后加3000
        for(int m=0; m<64; m++)
            mean += all_wavelength_data[1][m];
        mean = mean/64+3000;

        MAX_Temp = 0;

        for(int a=0;a<128;a++){
            for(int b=0; b<64; b++){

                // if(all_wavelength_data[b][a]>1320500 && wavelength_MaxApproach[a]!='\0')
                if(all_wavelength_data[b][a]>mean )
                    Temp[a] = (1549.5+0.06*b-1550.5)/0.01; //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp[a]>MAX_Temp) MAX_Temp = Temp[a];

            //if(Temp[a] == '\0') Temp[a]='0';
        }

        //    emit sendToTempDistance_widget();

        qDebug()<<"Temp Distance finished ! "<<endl;
    }

}

